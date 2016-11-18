#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../solver.h"
#include "qmapwidget.h"
#include "qprocessviewer.h"
#include <QObject>

class Controller : public QObject {
    Q_OBJECT
public:
    explicit Controller();

    void addSolver(Solver* solver);
    void connectSignals();

    Solver* m_solver;
    QProcessViewer* m_qProcessViewer;
    QMapWidget* m_qMapWidget;

signals:

public slots:
};

#endif // CONTROLLER_H
