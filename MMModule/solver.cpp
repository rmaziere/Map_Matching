#include "solver.h"
#define DEBUG_SOLVER true

Solver::Solver(QObject* parent)
    : QObject(parent)
{
}

void Solver::start()
{
    track.readFromCSV(m_trackFilename);
    track.temporalFilter(2);
    track.spaceFilter(15);
    m_trackPoints = track.getPointsAsPointer();
    emit signalMessage(QString::fromStdString(track.infos()));
    grid.readFromCSV(m_gridFilename);
    m_roadPoints= &(grid.m_vectorOfPoints);

    emit signalMessage(QString::fromStdString(grid.infos()));

    emit signalDimension(grid.xMinGrid(), grid.xMaxGrid(), grid.yMinGrid(), grid.yMaxGrid());
    emit signalAllPoints(m_trackPoints);
    emit signalAllRoads(&grid.m_mapOfAllRoads, &(grid.m_vectorOfPoints));

    grid.buildMarkovMatrix();
    emit signalMessage("Markov Matrix built");

    // temp
    viterbiSetup();
}

void Solver::viterbiSetup()
{
    int noOfStates = grid.getNoOfRoads();
    int noOfObs = track.getNoOfPoints();
    // initialize T1, T2 with 0
    for (int i = 0; i < noOfStates; i++) {
        T1.push_back(std::vector<float>(noOfObs));
        T2.push_back(std::vector<float>(noOfObs));
    }
    // build bidirectionnal mapping between roadId and index
    int index= 0;
    for (auto x : grid.m_mapOfAllRoads) {
        m_fromIndexToRoadId.push_back(x.first);
        m_fromRoadIdToIndex[x.first]= index;
        ++index;
    }

    m_currentStep = -1;
}

void Solver::setDistance(PointGPS* p, Road* r)
{
    const std::vector<int>& listOfPointId = r->vectorOfPointsId();
    double d, bestDistance = std::numeric_limits<double>::max();

    for (uint i = 1; i < listOfPointId.size(); i++) {
        d = p->distanceToSegment(m_roadPoints->at(listOfPointId[i - 1]), m_roadPoints->at(listOfPointId[i]));
        if (d < bestDistance) {
            bestDistance = d;
        }
    }

    if (bestDistance < DISTANCE_THRESHOLD)
        p->addEmissionProbability(r->edgeId(), bestDistance);

    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
    }
}

void Solver::buildRoadPath()
{
    unsigned int i;
    std::vector<long> *roadPath= new std::vector<long>(0);
    int roadIndex, prevrI=-1;
    float bestProbaSoFar= 0.0;
    for (i=0; i<m_fromIndexToRoadId.size(); i++) {
        if (T1[i][m_currentStep]>bestProbaSoFar) {
            bestProbaSoFar= T1[i][m_currentStep];
            roadIndex= i;
        }
    }
    roadPath->push_back(m_fromIndexToRoadId[roadIndex]);
    prevrI= roadIndex;
    for (int i= m_currentStep-1; i>0; i--) {
        int roadIndex= T2[prevrI][i];
        if (roadIndex!=prevrI) roadPath->push_back(m_fromIndexToRoadId[roadIndex]);
        prevrI= roadIndex;
    }
    emit signalRoadPath(roadPath);
}

void Solver::onSignalSetGrid(QString s)
{
    m_gridFilename = s;
}

void Solver::onSignalSetTrack(QString s)
{
    m_trackFilename = s;
}

void Solver::onSignalStart()
{
    emit signalMessage("Solver started");
    start();
}

void Solver::onSignalNextStep()
{
    m_currentStep++;
    if (m_currentStep < m_trackPoints->size())
        emit signalCurrentPoint(m_currentStep);
}

void Solver::onSignalNeighbours(std::vector<long>* roadsId)
{
    std::unordered_map<long, Road>::iterator idToRoad; // find road from its id
    Road *r;
    std::cout << "Neighbour roads " << roadsId->size() << std::endl;
    // compute distance current point -> roads then probabilities (emission matrix)
    PointGPS* p = m_trackPoints->at(m_currentStep);
    if (p->m_emissionProbability.size()>0) return;
    for (const auto id : *roadsId) {
        idToRoad = grid.m_mapOfAllRoads.find(id);
        // Road *r= ...
        r= &idToRoad->second;
        std::cout << p->x() << " distance " << r->edgeId() << std::endl;
        setDistance(p, r);
    }
    p->updateProbability();
/*
    // compute straight distance over road distance then probabilities (transition matrix)
    double v;
    if (m_currentStep>0) {
        for (const auto prevId: *prevRoadIds) {
            for (const auto id: *roadsId) {
                v= grid.computeDistanceFraction(prevPoint, p, prevId, id);
            }
        }
    }
*/


    // update T1, T2
    int roadIndex;
    int neighIndex;
    std::unordered_map<long, int>::iterator idToIdx;    // find index of road from its id
    if (m_currentStep==0) {
        // for all neighbouring roads of the first point, apply the emission probability (here PI=1 for any couple (state,obs) (ie (road, point))
        for (const auto ep : p->m_emissionProbability) {
            idToIdx= m_fromRoadIdToIndex.find(ep.roadId());
            roadIndex= idToIdx->second;
            T1[roadIndex][m_currentStep]= ep.probability();
        }
    } else {
        for (const auto ep : p->m_emissionProbability) {
            idToIdx= m_fromRoadIdToIndex.find(ep.roadId());
            roadIndex= idToIdx->second;
            // find all connexions to this road
            idToRoad = grid.m_mapOfAllRoads.find(ep.roadId());
            r= &idToRoad->second;
            float maxT1= 0.0; // used to build T2
            int maxT1roadId=0;
            for (auto neigh : r->m_setOfNeighbors) {
                neighIndex= getIndexFromRoadId(neigh);
                T1[roadIndex][m_currentStep]= std::max(T1[roadIndex][m_currentStep],
                    T1[neighIndex][m_currentStep-1] * 1 *  ep.probability());
                if (maxT1<T1[neighIndex][m_currentStep-1] * 1) {
                    maxT1= T1[neighIndex][m_currentStep-1] * 1;
                    maxT1roadId= neighIndex;
                }
            }
            T2[roadIndex][m_currentStep]= maxT1roadId;
        }
    }
    buildRoadPath();
}

void Solver::readFiles(File file1, File file2)
{
    File fileTrack = file1;
    File fileGrid = file2;
    QString fileT = fileTrack.filePath.at(0) + fileTrack.fileName.at(0) + "." + fileTrack.fileExtension.at(0);
    QString fileG = fileGrid.filePath.at(0) + fileGrid.fileName.at(0) + "." + fileGrid.fileExtension.at(0);

    track.readFromCSV(fileT);
    emit signalMessage(QString::fromStdString(track.infos()));

    grid.setTrackBoundingBox(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    grid.readFromCSV(fileG);
    emit signalMessage(QString::fromStdString(grid.infos()));
    emit signalAllRoads(&grid.m_mapOfAllRoads, &(grid.m_vectorOfPoints));
}

void Solver::filterSpace(double val)
{
    track.spaceFilter(val);
    m_trackPoints = track.getPointsAsPointer();
    emit signalDimension(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    emit signalAllPoints(m_trackPoints);
}

void Solver::filterTemp(int val)
{
    track.temporalFilter(val);
    m_trackPoints = track.getPointsAsPointer();
    emit signalDimension(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    emit signalAllPoints(m_trackPoints);
}

int Solver::getIndexFromRoadId(long id)
{
    std::unordered_map<long, int>::iterator idToIdx= m_fromRoadIdToIndex.find(id);
    return idToIdx->second;
}
