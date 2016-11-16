#ifndef ROAD_H
#define ROAD_H

#include "pointroad.h"
#include "track.h"

#include <set>
#include <string>
#include <vector>

class Road {
public:
    Road() {}
    Road(long roadId)
        : m_edgeId(roadId)
    {
    }

    virtual ~Road();

    void addPoint(int pointId);
    void addNeighbor(long roadId);

    std::vector<Point*> getListOfPoints() const;
    long getm_edgeId();

    void outputInfos() const;

    // accessors
    long edgeId() const { return m_edgeId; }
    const std::vector<int>& vectorOfPointsId() const { return m_vectorOfPointsId; }
    int getNoOfNeighbors() const { return m_setOfNeighbors.size(); }
protected:
    long m_edgeId;
    std::vector<int> m_vectorOfPointsId;
    std::set<long> m_setOfNeighbors; /*< Set of all roadId connected to this one (including this one) */
};

#endif // ROAD_H
