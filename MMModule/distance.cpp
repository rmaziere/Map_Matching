#include "distance.h"

//Utilisation du namespace std pour standard
using namespace std;

Distance::Distance()
{
}

double Distance::distance2pt(Point pt1,Point pt2)
{
    return sqrt(pow(pt2.m_x-pt1.m_x,2)+pow(pt2.m_y-pt1.m_y,2));
}

double Distance::distance2ptsegment(Point A,Point B, Point pt)
{
    if ((B.m_x == A.m_x) && (B.m_y == A.m_y))
    {
        return distance2pt(A,pt);
    }
    else
    {
        double num = (pt.m_x - A.m_x) * (B.m_x - A.m_x) + (pt.m_y - A.m_y) * (B.m_y - A.m_y);
        double tSol = num / pow(distance2pt(A,B),2);
        double t = std::max(0.0, std::min(1.0, tSol));
        Point proj(A.m_x + t * (B.m_x - A.m_x), A.m_y + t * (B.m_y - A.m_y));

        return distance2pt(pt, proj);
    }
}

/*void distance(int identifiantRoad, Point pt)
{
    double distMin = 1000000;
    // For each segment in road
    Point A;
    Point B;
    A = road->listOfPoint{0};
    for (int i = 1; i < listOfPoints.size(); i++)
    {
        B = road->listOfPoint{i}
        d = distance2ptsegment(A,B,pt);
        if (d < distMin)
        {
            distMin = d;
        }
        A = B;
    }
    if (d <= 200)
    {
        return true;
    }
}*/
