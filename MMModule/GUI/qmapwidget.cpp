#include "qmapwidget.h"

#define WIDGET_WIDTH 1000
QMapWidget::QMapWidget(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_scene = new QMapScene(this);
    m_view = new QGraphicsView(m_scene);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_layout->addWidget(m_view);
    buildControls();
    m_layout->addWidget(m_controlZone);
    setLayout(m_layout);
    setWindowTitle(tr("Map viewer"));

    connect(m_play, SIGNAL(clicked()), m_scene, SLOT(onSignalStart()));
    connect(m_zoom, SIGNAL(valueChanged(int)), this, SLOT(sceneScaleChanged(int)));
    connect(m_scene, SIGNAL(signalItemToShow(QGraphicsItem*)), this, SLOT(onSignalItemToShow(QGraphicsItem*)));
}

void QMapWidget::buildControls()
{
    m_controlZone = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout();
    m_play = new QPushButton("Play all", m_controlZone);
    m_next = new QPushButton("One step", m_controlZone);
    m_zoom = new QSlider(Qt::Horizontal, m_controlZone);
    m_zoom->setTickInterval(10);
    m_zoom->setMinimum(0);
    m_zoom->setMaximum(100);
    m_zoom->setValue(1);
    layout->addWidget(m_play);
    layout->addWidget(m_next);
    layout->addWidget(m_zoom);
    m_controlZone->setLayout(layout);
    m_controlZone->adjustSize();
}
void QMapWidget::onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid)
{
    m_scene->initialize(int(xMinGrid), int(yMinGrid), int(xMaxGrid), int(yMaxGrid));
    double ratio = (yMaxGrid - yMinGrid) / (xMaxGrid - xMinGrid);
    resize(WIDGET_WIDTH, (int)(WIDGET_WIDTH * ratio));
    m_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    m_view->scale(1, -1);
    show();
}

void QMapWidget::onSignalItemToShow(QGraphicsItem* item)
{
    m_view->centerOn(item);
}

void QMapWidget::sceneScaleChanged(int scaleTickValue)
{
    double newScale = scaleTickValue / 100.0;
    m_view->resetMatrix();
    m_view->scale(newScale, -newScale);
}
