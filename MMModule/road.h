#ifndef ROAD_H
#define ROAD_H

#include <string>
#include <vector>
#include "point.h"

using namespace std;

class Road {
public:
    Road(string description){} // TODO

    bool addPoint(double x, double y){ return true;} // TODO
    bool addPoint(long id, double x, double y){ return true;} // TODO

    Point *findPoint(long id){return NULL;} // TODO

    double distanceTo(Point);

protected:
    long id;
    long fromNodeId;
    long toNodeId;
    bool twoWay;
    float avgSpeed;
    int noOfPoints;
    vector<Point *> listOfPoints{0};
};

#endif // ROAD_H
