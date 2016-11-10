#ifndef SOLVER_H
#define SOLVER_H

#include "grid.h"
#include "track.h"

class solver {
public:
    solver(const grid& network, const Track& track)
        : m_network(network)
        , m_track(track)
    {
    }
    void initialize();

protected:
    grid m_network;
    Track m_track;
};

#endif // SOLVER_H
