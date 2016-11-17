#include "controller.h"

Controller::Controller()
{
    m_qProcessViewer = new QProcessViewer;
}

void Controller::addSolver(Solver* solver)
{
    m_solver = solver;
}

void Controller::connectSignals()
{
    QObject::connect(m_solver, SIGNAL(signalMessage(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(m_qProcessViewer->startSolver, SIGNAL(clicked()), m_solver, SLOT(onSignalStart()));
}
