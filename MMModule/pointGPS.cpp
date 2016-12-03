#include "pointGPS.h"

#include <sstream>

void PointGPS::addEmissionProbability(long roadId, double distance)
{
    EmissionProbability e(roadId, distance);
    m_emissionProbability.push_back(std::move(e));
}

void PointGPS::updateProbability()
{
    double sum = 0.0;
    for (auto& e : m_emissionProbability)
        sum += e.distance();
    for (auto& e : m_emissionProbability)
        e.updateProbability(sum);
}

std::string PointGPS::infos() const
{
    std::stringstream ss;
    ss << Point::infos() << " with " << m_emissionProbability.size() << " emissions to roads < 200m";
    return ss.str();
}
