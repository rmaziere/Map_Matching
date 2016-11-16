#include "controller.h"


Controller::Controller() {}

void Controller::addSolver(Solver *solver)
{
    m_solver= solver;
}

void Controller::connectSignals()
{
    m_qMapViewer= new QMapViewer;

    QObject::connect(m_solver, SIGNAL(signalMessage(QString)), m_qMapViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(m_qMapViewer->startSolver, SIGNAL(clicked()), m_solver, SLOT(onSignalStart()));


}
