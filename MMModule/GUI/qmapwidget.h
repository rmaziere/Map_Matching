#ifndef QMAPWIDGET_H
#define QMAPWIDGET_H

#include "qmapscene.h"
#include "qmapviewer.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QSlider>

class QMapWidget : public QWidget {
    Q_OBJECT
public:
    explicit QMapWidget(QWidget* parent = 0);

    void buildControls();

    QMapScene* m_scene;
signals:

private slots:
    void sceneScaleChanged(int);

public slots:
    void onSignalShow();
    void onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid);

protected:
    QGraphicsView* m_view;
    QVBoxLayout* m_layout;
    QWidget* m_controlZone;
    QPushButton* m_start;
    QPushButton* m_next;
    QSlider *m_zoom;
};

#endif // QMAPWIDGET_H
