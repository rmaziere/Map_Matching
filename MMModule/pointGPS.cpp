#include "pointGPS.h"

void PointGPS::addEmissionProbability(long roadId, double distance)
{
    EmissionProbability e(roadId, distance);
    m_emissionProbability.push_back(std::move(e));
}
