#ifndef ROAD_H
#define ROAD_H

#include "point.h"
#include "track.h"

#include <string>
#include <vector>

using namespace std;

class Road {
public:
    //Road(string description) {} // TODO
    Road(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId);
    Road(vector<Point> listOfPoints);

    virtual ~Road();

    bool addPoint(double x, double y);
    //bool addPoint(long id, double x, double y) { return true; } // TODO
    bool addPoint(Point) { return true; } // TODO

    //Point* findPoint(long id) { return NULL; } // TODO

    /**
     * @brief distanceTo Calculate distance between a point and a road
     * @return Value
     */
    double distanceTo(Point);

    vector<Point*> getListOfPoints() const;

protected:
    long m_edgeId;
    long m_fromNodeId;
    long m_toNodeId;
    //bool twoWay;
    //float avgSpeed;
    int noOfPoints;
    vector<Point*> listOfPoints;
};

#endif // ROAD_H
