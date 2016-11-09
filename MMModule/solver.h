#ifndef SOLVER_H
#define SOLVER_H

#include "network.h"
#include "track.h"

class solver {
public:
    solver(const Network &network, const Track &track):m_network(network), m_track(track) {}
    void initialize();

protected:
    Network m_network;
    Track m_track;

};

#endif // SOLVER_H
