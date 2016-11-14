#include "road.h"

#include <limits.h>

Road::~Road()
{
    m_vectorOfPointsId.clear();
}

void Road::addPoint(int pointId)
{
    m_vectorOfPointsId.push_back(pointId);
}

void Road::outputInfos() const
{
    std::cout << "Route " << m_edgeId << " contains " << m_vectorOfPointsId.size() << std::endl;
}

long Road::getm_edgeId()
{

    return m_edgeId;
}



