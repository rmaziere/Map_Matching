#include "emissionprobability.h"

void EmissionProbability::updateProbability(double distanceAll)
{
    //m_probability = (float)(m_distance*m_distance / distanceAll*distanceAll);
    if (distanceAll+0.01-m_distance<1) m_probability=0.99;
    else m_probability = (m_distance>1.0)? 1.0/m_distance:0.9;
    if (m_probability<0.01) m_probability= 0.01;
}
