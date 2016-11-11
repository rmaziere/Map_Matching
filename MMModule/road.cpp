#include "road.h"

Road::Road(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId)
    : m_edgeId(edgeId)
    , m_fromNodeId(fromNodeId)
    , m_toNodeId(toNodeId)
{
    for (size_t i = 0; i < listOfCoordinates.size(); ++i) {
        addPoint(listOfCoordinates[i][0], listOfCoordinates[i][1]);
    }
}

Road::Road(vector<Point> listOfPoints)
{
    for (size_t i = 0; i < listOfPoints.size(); ++i) {
        addPoint(listOfPoints[i]);
    }
}

Road::~Road()
{
    for (size_t i = 0; i < listOfPoints.size(); ++i) {
        delete[] listOfPoints[i];
    }
    listOfPoints.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}

bool Road::addPoint(double x, double y)
{

    listOfPoints.push_back(new Point(x, y));
    return true;
}

double Road::distanceTo(Point pt)
{
    double distMin = 1000000; // TODO !!!
    // For each segment in road
    for (int i = 1; i < this->noOfPoints; i++) {
        double d = pt.distanceToSegment(*this->listOfPoints[i - 1], *this->listOfPoints[i]);
        if (d < distMin) {
            distMin = d;
        }
    }
    return distMin;
}

vector<Point*> Road::getListOfPoints() const
{
    return listOfPoints;
}
