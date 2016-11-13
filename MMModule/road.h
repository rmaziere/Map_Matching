#ifndef ROAD_H
#define ROAD_H

#include "pointroad.h"
#include "track.h"

#include <string>
#include <vector>

using namespace std;

class Road {
public:
    Road() {}
    Road(long roadId)
        : m_edgeId(roadId)
    {
    }

    virtual ~Road();

    void addPoint(int pointId);

    void outputInfos() const;

    // accessors
    long edgeId() const {return m_edgeId;}
    const vector<int> &vectorOfPointsId() const { return m_vectorOfPointsId;}
protected:
    long m_edgeId;
    vector<int> m_vectorOfPointsId;
};

#endif // ROAD_H
