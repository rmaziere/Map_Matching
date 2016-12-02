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

int Road::getIntersectionIDWith(Road *r) const
{
    for (int id1:r->vectorOfPointsId()) {
        for (int id0: m_vectorOfPointsId) {
            if (id1==id0) return id0;
        }
    }
    return -1; // should never happen
}

void Road::outputInfos() const
{
    std::cout << "Route " << m_edgeId << " contains " << m_vectorOfPointsId.size() << " points" << std::endl;
    std::cout << "\t and has " << m_setOfNeighbors.size() << " neighbors (including itself)" << std::endl;
}



