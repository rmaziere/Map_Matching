#ifndef SOLVER_H
#define SOLVER_H

#include "grid.h"
#include "track.h"

class solver {
public:
    solver(const Grid& network, const Track& track)
        : m_network(network)
        , m_track(track)
    {
    }
    void initialize();

protected:
    Grid m_network;
    Track m_track;
};

#endif // SOLVER_H
