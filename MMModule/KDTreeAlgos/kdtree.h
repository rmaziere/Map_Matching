#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

#include "../point.h"
#include "boxnode.h"


class KDTree
{
public:
    static const double BIG;
    KDTree(std::vector<Point> &points);
    ~KDTree();

    int partition(const int k, int *index, int n, double *arr);

    double distance(int idxOfPoint1, int idxOfPoint2);
    int locate(const Point &p);

protected:
    int m_noOfBoxes;
    std::vector<Point> m_vectorOfPoints;
    int m_noOfPoints;
    BoxNode *m_arrayOfBoxes;            //
    std::vector<int> m_vectorOfPointIndexes, m_vectorOfReversedPointIndexes;
    double *m_arrayOfCoordinates;

};

#endif // KDTREE_H
