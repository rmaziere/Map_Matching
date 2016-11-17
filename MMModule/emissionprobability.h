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

    void updateProbability(float p) { m_probability = p; }

protected:
    long m_roadId;
    double m_distance;
    float m_probability;
};

#endif // EMISSIONPROBABILITY_H
