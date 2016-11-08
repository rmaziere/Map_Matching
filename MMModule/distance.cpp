#include "distance.h"

//Utilisation du namespace std pour standard
using namespace std;

Distance::Distance()
{
}

double Distance::distance2pt(std::vector<double> pt1,std::vector<double> pt2)
{
    return sqrt(pow(pt2[0]-pt1[0],2)+pow(pt2[1]-pt1[1],2));
}

double Distance::distance2ptsegment(std::vector<double> A,std::vector<double> B, std::vector<double> pt)
{
    if ((B[0] == A[0]) && (B[1] == A[1]))
    {
        return distance2pt(A,pt);
    }
    else
    {
        double num = (pt[0] - A[0]) * (B[0] - A[0]) + (pt[1] - A[1]) * (B[1] - A[1]);
        double tSol = num / pow(distance2pt(A,B),2);
        double t = std::max(0.0, std::min(1.0, tSol));
        std::vector<double> proj(2);
        proj[0] = A[0] + t * (B[0] - A[0]);
        proj[1] = A[1] + t * (B[1] - A[1]);
        return distance2pt(pt, proj);
    }
}
