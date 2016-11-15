#ifndef SOLVER_H
#define SOLVER_H

#include "pointroad.h"
#include "pointGPS.h"
#include "road.h"

#include <vector>
#include <unordered_map>

typedef std::unordered_map<long, Road> AllRoadMap;
typedef std::vector<PointGPS*> AllPointVector;

class Solver {
public:
    Solver( AllRoadMap* gridRoad, std::vector<PointRoad> *roadPoints, AllPointVector* trackPoint)
        : m_roads(gridRoad)
        , m_roadPoints(roadPoints)
        , m_trackPoints(trackPoint)
    {
    }
    void initialize();
    void setDistance(PointGPS *p, Road &r);

protected:
    AllRoadMap *m_roads;
    std::vector<PointRoad> *m_roadPoints;
    AllPointVector *m_trackPoints;
};

#endif // SOLVER_H
