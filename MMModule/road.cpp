#include "road.h"

Road::Road(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId):
    m_edgeId(edgeId),
    m_fromNodeId(fromNodeId),
    m_toNodeId(toNodeId)
{
    for (size_t i=0; i<listOfCoordinates.size();++i){
        addPoint(listOfCoordinates[i][0], listOfCoordinates[i][1]);
    }
}

Road::Road(vector<Point> listOfPoints)
{
    for (size_t i=0; i<listOfPoints.size();++i){
        addPoint(listOfPoints[i]);
    }
}

Road::~Road()
{
    for (size_t i=0 ; i < listOfPoints.size(); ++i)
    {
        delete[] listOfPoints[i];
    }
    listOfPoints.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}
