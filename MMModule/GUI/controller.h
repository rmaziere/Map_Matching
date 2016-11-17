#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "qprocessviewer.h"
#include "qmapviewer.h"
#include "qmapwidget.h"
#include "solver.h"
#include <QObject>

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller();

    void addSolver(Solver* solver);
    void connectSignals();

    Solver* m_solver;
    QProcessViewer* m_qProcessViewer;
    QMapWidget *m_qMapWidget;

signals:

public slots:
};

#endif // CONTROLLER_H
