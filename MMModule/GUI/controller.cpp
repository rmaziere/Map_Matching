#include "controller.h"

Controller::Controller()
{

    m_qMapWidget = new QMapWidget;
    //m_qMapWidget->resize(1000,800);
    m_qProcessViewer = new QProcessViewer;

}

void Controller::addSolver(Solver* solver)
{
    m_solver = solver;
}

void Controller::connectSignals()
{
    QObject::connect(m_qProcessViewer->closeButton, SIGNAL(pressed()), m_qMapWidget, SLOT(close()));
    QObject::connect(m_solver, SIGNAL(signalMessage(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(&(m_solver->track), SIGNAL(signalMessage(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(&(m_solver->grid), SIGNAL(signalMessage(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    QObject::connect(m_qProcessViewer->startSolver, SIGNAL(clicked()), m_solver, SLOT(onSignalStart()));

    QObject::connect(m_solver, SIGNAL(signalDimension(double, double, double, double)), m_qMapWidget, SLOT(onSignalDimension(double, double, double, double)));
    QObject::connect(m_solver, SIGNAL(signalAllPoints(std::vector<PointGPS*>*)), m_qMapWidget->m_scene, SLOT(onSignalAllPoints(std::vector<PointGPS*>*)));
    QObject::connect(m_solver, SIGNAL(signalAllRoads(std::unordered_map<long, Road>*, std::vector<PointRoad>*)), m_qMapWidget->m_scene, SLOT(signalAllRoads(std::unordered_map<long, Road>*, std::vector<PointRoad>*)));

    /*QObject::connect(m_qMapWidget->m_qMapViewer, SIGNAL(signalTrackCompleted(QString)), m_qMapWidget, SLOT(onSignalShow()));
    QObject::connect(m_qMapWidget->m_qMapViewer, SIGNAL(signalTrackCompleted(QString)), m_qProcessViewer, SLOT(onSignalMessage(QString)));
    */
}
