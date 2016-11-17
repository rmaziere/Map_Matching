#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "qmapviewer.h"
#include "solver.h"
#include <QObject>

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller();

    void addSolver(Solver* solver);
    void connectSignals();

    Solver* m_solver;
    QMapViewer* m_qMapViewer;

signals:

public slots:
};

#endif // CONTROLLER_H
