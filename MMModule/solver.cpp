#include "solver.h"

#define DEBUG true

void Solver::initialize()
{
    if (DEBUG) std::cout << m_roads->size() << " roads and " << m_trackPoints->size() << " points." << std::endl;
    // construction of the emissionMatrix
    for (PointGPS *p: *m_trackPoints) {
        for (auto &it : *m_roads) {
           setDistance(p,it.second);
        }
    }
}

void Solver::setDistance(PointGPS *p, Road &r)
{
    if (DEBUG) {
        std::cout << p->infos() << std::endl;
        r.outputInfos();
    }
/*    const vector<int> &listOfPointId= r.vectorOfPointsId();
    double d, bestDistance= std::numeric_limits<double>::max();
    for (uint i=1; i<listOfPointId.size(); i++) {
        d= p->distanceToSegment(*m_roadPoints[listOfPointId[i-1]], *m_roadPoints[listOfPointId[i]]);
        if (d<bestDistance) bestDistance= d;
    }
    p->addEmissionProbability(r.edgeId(), bestDistance);

    if (DEBUG) {
        //std::cout << p->infos() << std::endl;
    }*/
}
