#include "road.h"
#include <iostream>

Road::~Road()
{
    m_vectorOfPointsId.clear();
}

void Road::addPoint(int pointId)
{
    m_vectorOfPointsId.push_back(pointId);
}

void Road::addNeighbor(long roadId)
{
    m_setOfNeighbors.insert(roadId);
}

void Road::outputInfos() const
{
    std::cout << "Route " << m_edgeId << " contains " << m_vectorOfPointsId.size() << " points" << std::endl;
    std::cout << "\t and has " << m_setOfNeighbors.size() << " neighbors (including itself)" << std::endl;
}

long Road::getm_edgeId()
{

    return m_edgeId;
}



