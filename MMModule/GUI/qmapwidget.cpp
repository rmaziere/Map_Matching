#include "qmapwidget.h"

#include <QScrollArea>
#include <QVBoxLayout>

QMapWidget::QMapWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_scene= new QMapScene(this);
    m_view = new QGraphicsView(m_scene);
    m_layout->addWidget(m_view);
    setLayout(m_layout);
    setWindowTitle(tr("Map viewer"));
}

void QMapWidget::onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid)
{
    m_scene->initialize(int(xMinGrid), int(yMinGrid), int(xMaxGrid), int(yMaxGrid));
    sceneScaleChanged();
    show();
}

void QMapWidget::sceneScaleChanged()
{
    double newScale = 0.1;
    QMatrix oldMatrix = m_view->matrix();
    m_view->resetMatrix();
    m_view->translate(oldMatrix.dx(), oldMatrix.dy());
    m_view->scale(newScale, newScale);
}


void QMapWidget::onSignalShow()
{
    /*
    QPixmap pixmap;
    pixmap.convertFromImage(m_qMapViewer->m_map);
    m_label->setPixmap(pixmap);
    //m_label->set
    m_label->update();
    this->show();
*/
}
