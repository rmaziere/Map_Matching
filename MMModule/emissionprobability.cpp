#include "emissionprobability.h"

void EmissionProbability::updateProbability(double distanceAll)
{
    m_probability= (float) (m_distance/distanceAll);
}
