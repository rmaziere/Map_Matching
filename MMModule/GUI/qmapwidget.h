#ifndef QMAPWIDGET_H
#define QMAPWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "qmapscene.h"
#include "qmapviewer.h"
class QMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMapWidget(QWidget* parent = 0);

    QMapScene *m_scene;
signals:

private slots:
    void sceneScaleChanged();

public slots:
    void onSignalShow();
    void onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid);
protected:
    QGraphicsView *m_view;
    QVBoxLayout* m_layout;
};

#endif // QMAPWIDGET_H
