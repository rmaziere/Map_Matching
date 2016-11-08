#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>
#include <math.h>

class Distance
{
public:

    Distance();

    double distance2pt(std::vector<double> pt1,std::vector<double> pt2);

    double distance2ptsegment(std::vector<double> A,std::vector<double> B, std::vector<double> pt);

};

#endif // DISTANCE_H
