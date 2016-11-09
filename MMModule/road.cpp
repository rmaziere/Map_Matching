#include "road.h"

double Road::distance(Point pt)
{
    double distMin = 1000000;
    // For each segment in road
    for (int i = 1; i < this->noOfPoints; i++)
    {
        double d = pt.distance2ptsegment(*this->listOfPoints[i-1],*this->listOfPoints[i]);
        if (d < distMin)
        {
            distMin = d;
        }
    }
    return distMin;
}
