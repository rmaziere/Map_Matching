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
    m_currentStep = -1;
}
/*
void Solver::setDistance(PointGPS* p, Road& r)
{
    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
        r.outputInfos();
    }
    const std::vector<int>& listOfPointId = r.vectorOfPointsId();
    double d, bestDistance = std::numeric_limits<double>::max();
    for (uint i = 1; i < listOfPointId.size(); i++) {
        //int j=listOfPointId[i-1];
        //Point p1= m_roadPoints->at(j);
        d = p->distanceToSegment(m_roadPoints->at(listOfPointId[i - 1]), m_roadPoints->at(listOfPointId[i]));
        if (d < bestDistance)
            bestDistance = d;
    }
    if (bestDistance < DISTANCE_THRESHOLD)
        p->addEmissionProbability(r.edgeId(), bestDistance);

    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
    }
}
*/
void Solver::setDistance(PointGPS* p, Road* r)
{
    std::cout << "DEBUG" << std::endl;

    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
        r->outputInfos();
    }

    const std::vector<int>& listOfPointId = r->vectorOfPointsId();
    double d, bestDistance = std::numeric_limits<double>::max();

    for (uint i = 1; i < listOfPointId.size(); i++) {
        //int j=listOfPointId[i-1];
        //Point p1= m_roadPoints->at(j);
        d = p->distanceToSegment(m_roadPoints->at(listOfPointId[i - 1]), m_roadPoints->at(listOfPointId[i]));
        if (d < bestDistance) {
            bestDistance = d;
            std::cout << "\t" << bestDistance << std::endl;

        }
    }
    /*
    if (bestDistance < DISTANCE_THRESHOLD)
        p->addEmissionProbability(r->edgeId(), bestDistance);

    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
    }*/
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
    std::cout << "Neighbour roads " << roadsId->size() << std::endl;
    // compute distance current point -> roads
    PointGPS* p = m_trackPoints->at(m_currentStep);
    for (const auto id : *roadsId) {
        std::unordered_map<long, Road>::iterator got = grid.m_mapOfAllRoads.find(id);
        Road *r= &got->second;
        std::cout << p->x() << " distance " << r->edgeId() << std::endl;
        setDistance(p, r);
        //setDistance(p, m_roads[id]);
    }
    // compute probability

    // update T1, T2

    // find best path so far
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
