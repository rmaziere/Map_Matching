#include "kdtree.h"

#include <algorithm>
#include <limits>

#define MAX_DOUBLE std::numeric_limits<double>::max()

const double KDTree::BIG(1.0e99);

KDTree::KDTree(std::vector<Point>& points)
    : m_vectorOfPoints(points)
    , m_noOfPoints(points.size())
    , m_vectorOfPointIndexes(m_noOfPoints)
    , m_vectorOfReversedPointIndexes(m_noOfPoints)
{
    int ntmp, m, k, kk, j, nowtask, jbox, np, tmom, tdim, ptlo, pthi;
    int* hp;
    double* cp;
    int taskmom[50], taskdim[50];
    for (k = 0; k < m_noOfPoints; k++)
        m_vectorOfPointIndexes[k] = k; // initialize index of points

    // calculate the number of boxes and allocate memory
    m = 1;
    for (ntmp = m_noOfPoints; ntmp; ntmp >>= 1)
        m <<= 1; // at each depth, the numlber of boxes is doubled
    m_noOfBoxes = 2 * m_noOfPoints - (m >> 1);
    if (m < m_noOfBoxes)
        m_noOfBoxes = m;
    m_noOfBoxes--; // account for mother box
    m_arrayOfBoxes = new BoxNode[m_noOfBoxes];

    // copy the points coordinates into a contiguous array
    m_arrayOfCoordinates = new double[2 * m_noOfPoints];
    for (j = 0, kk = 0; j < 2; j++, kk += m_noOfPoints) { // j allows access to x and y (point in 2 dimensions)
        for (k = 0; k < m_noOfPoints; k++)
            m_arrayOfCoordinates[kk + k] = m_vectorOfPoints[k].x(j);
    }

    // initialize the root box and put it on the task list for subdivision
    Point low(0.0, 0.0), high(MAX_DOUBLE, MAX_DOUBLE);
    m_arrayOfBoxes[0] = BoxNode(low, high, 0, 0, 0, 0, m_noOfPoints - 1);
    jbox = 0;
    taskmom[1] = 0;
    taskdim[1] = 0;
    nowtask = 1;

    while (nowtask) { // main loop over pending task
        tmom = taskmom[nowtask];
        tdim = taskdim[nowtask];
        --nowtask;
        ptlo = m_arrayOfBoxes[tmom].m_indexOfLowerPoint;
        pthi = m_arrayOfBoxes[tmom].m_indexOfUpperPoint;
        hp = &m_vectorOfPointIndexes[ptlo]; // points to left end of subdivision
        cp = &m_arrayOfCoordinates[tdim * m_noOfPoints]; // points to coordinate list for current dimension
        np = pthi - ptlo + 1; // number of points in the subdivision
        kk = (np - 1) / 2; // index of the last point on left (boundary point)

        (void)partition(kk, hp, np, cp);
        high = m_arrayOfBoxes[tmom].m_high;
        low = m_arrayOfBoxes[tmom].m_low;
        high.setx(tdim, m_arrayOfCoordinates[tdim * m_noOfPoints + hp[kk]]);
        low.setx(tdim, m_arrayOfCoordinates[tdim * m_noOfPoints + hp[kk]]);
        m_arrayOfBoxes[++jbox] = BoxNode(m_arrayOfBoxes[tmom].m_low, high, tmom, 0, 0, ptlo, ptlo + kk);
        m_arrayOfBoxes[++jbox] = BoxNode(low, m_arrayOfBoxes[tmom].m_high, tmom, 0, 0, ptlo + kk + 1, pthi);
        m_arrayOfBoxes[tmom].m_daughterBox1 = jbox - 1;
        m_arrayOfBoxes[tmom].m_daughterBox2 = jbox;

        if (kk > 1) {
            taskmom[++nowtask] = jbox - 1;
            taskdim[nowtask] = (tdim + 1) % 2;
        }
        if (np - kk > 3) {
            taskmom[++nowtask] = jbox;
            taskdim[nowtask] = (tdim + 1) % 2;
        }
        //nowtask= 0;
    }
    for (j = 0; j < m_noOfPoints; j++)
        m_vectorOfReversedPointIndexes[m_vectorOfPointIndexes[j]] = j;
    delete[] m_arrayOfCoordinates;
}

KDTree::~KDTree()
{
    delete[] m_arrayOfBoxes; // TODO check if it works
    delete[] m_arrayOfCoordinates;
}

int KDTree::partition(const int k, int* idx, int n, double* arr)
{
    int i, ia, ir, j, l, mid;
    double a;

    l = 0;
    ir = n - 1;
    for (;;) {
        if (ir <= l + 1) {
            if (ir == l + 1 && arr[idx[ir]] < arr[idx[l]]) {
                std::swap(idx[l], idx[ir]);
            }
            return idx[k];
        } else {
            mid = (l + ir) >> 1;
            std::swap(idx[mid], idx[l + 1]);
            if (arr[idx[l]] > arr[idx[ir]])
                std::swap(idx[l], idx[ir]);
            if (arr[idx[l + 1]] > arr[idx[ir]])
                std::swap(idx[l + 1], idx[ir]);
            if (arr[idx[l]] > arr[idx[l + 1]])
                std::swap(idx[l], idx[l + 1]);
            i = l + 1;
            j = ir;
            ia = idx[l + 1];
            a = arr[ia];
            for (;;) {
                do
                    i++;
                while (arr[idx[i]] < a);
                do
                    j--;
                while (arr[idx[j]] > a);
                if (j < i)
                    break;
                std::swap(idx[i], idx[j]);
            }
            idx[l + 1] = idx[j];
            idx[j] = ia;
            if (j >= k)
                ir = j - 1;
            if (j <= k)
                l = i;
        }
    }
}

double KDTree::distance(int idxOfPoint1, int idxOfPoint2)
{
    if (idxOfPoint1 == idxOfPoint2)
        return BIG;
    else
        return m_vectorOfPoints[idxOfPoint1].distanceToPoint(m_vectorOfPoints[idxOfPoint2]);
}

int KDTree::locate(const Point& p)
{
    int nb, d1, jdim;
    nb = jdim = 0; // start with the root box
    while (m_arrayOfBoxes[nb].m_daughterBox1) { // as far as possible down the tree
        d1 = m_arrayOfBoxes[nb].m_daughterBox1;
        if (p.x(jdim) <= m_arrayOfBoxes[d1].m_high.x(jdim))
            nb = d1;
        else
            nb = m_arrayOfBoxes[nb].m_daughterBox2;
        jdim = (++jdim) % 2; // increment dimension cyclically
    }
    return nb;
}
