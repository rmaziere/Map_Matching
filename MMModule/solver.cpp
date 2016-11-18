#include "solver.h"
#define DEBUG_SOLVER false

Solver::Solver(QObject* parent)
    : QObject(parent)
{
}

void Solver::start()
{
    track.readFromCSV(m_trackFilename);
    m_trackPoints = track.getPointsAsPointer();
    emit signalMessage(QString::fromStdString(track.infos()));
    emit signalDimension(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    emit signalAllPoints(m_trackPoints);

    grid.readFromCSV(m_gridFilename);
    emit signalMessage(QString::fromStdString(grid.infos()));
    emit signalAllRoads(&grid.m_mapOfAllRoads, &(grid.m_vectorOfPoints));
    grid.buildMarkovMatrix();
    emit signalMessage("Markov Matrix built");
}

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

void Solver::readFiles(File file1, File file2)
{
    File fileTrack = file1;
    File fileGrid = file2;
    QString fileT = fileTrack.filePath.at(0) + fileTrack.fileName.at(0) + "." + fileTrack.fileExtension.at(0);
    QString fileG = fileGrid.filePath.at(0) + fileGrid.fileName.at(0) + "." + fileGrid.fileExtension.at(0);

    track.readFromCSV(fileT);
    emit signalMessage("Track - reading file : " + fileT);
    grid.setBoundingBox(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    grid.readFromCSV(fileG);
    emit signalMessage("Grid - reading file : " + fileG);
}
