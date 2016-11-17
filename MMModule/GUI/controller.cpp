#include "controller.h"

Controller::Controller() {}

void Controller::addSolver(Solver* solver)
{
    m_solver = solver;
}

void Controller::connectSignals()
{
    m_qProcessViewer = new QProcessViewer;

    QObject::connect(m_solver, SIGNAL(signalMessage(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(m_qProcessViewer->startSolver, SIGNAL(clicked()), m_solver, SLOT(onSignalStart()));
}
