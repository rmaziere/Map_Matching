#ifndef EMISSIONPROBABILITY_H
#define EMISSIONPROBABILITY_H

class EmissionProbability {
public:
    EmissionProbability(long roadId, double distance)
        : m_roadId(roadId)
        , m_distance(distance)
        , m_probability(0.0)
    {
    }

    void updateProbability(double distanceAll);

    long roadId() const { return m_roadId; }
    double distance() const { return m_distance; }
    float probability() const { return m_probability; }
protected:
    long m_roadId;
    double m_distance;
    float m_probability;
};

#endif // EMISSIONPROBABILITY_H
