#ifndef QMAPWIDGET_H
#define QMAPWIDGET_H

#include "qmapscene.h"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

class QMapWidget : public QWidget {
    Q_OBJECT
public:
    explicit QMapWidget(QWidget* parent = 0);

    void buildControls();
    //void startSimulation();

    QMapScene* m_scene;
    QPushButton* m_next;
signals:

private slots:
    void sceneScaleChanged(int scaleTickValue);

public slots:
    void onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid);
    void onSignalItemToShow(QGraphicsItem* item);

protected:
    QGraphicsView* m_view;
    QVBoxLayout* m_layout;
    QWidget* m_controlZone;
    QPushButton* m_play;

    QSlider* m_zoom;
    bool m_startSimulation;
};

#endif // QMAPWIDGET_H
