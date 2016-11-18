#include "qmapwidget.h"

QMapWidget::QMapWidget(QWidget* parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_scene = new QMapScene(this);
    m_view = new QGraphicsView(m_scene);
    m_layout->addWidget(m_view);
    buildControls();
    m_layout->addWidget(m_controlZone);
    setLayout(m_layout);
    setWindowTitle(tr("Map viewer"));
}

void QMapWidget::buildControls() {
    m_controlZone= new QWidget(this);
    QHBoxLayout *layout= new QHBoxLayout();
    m_start= new QPushButton("start", m_controlZone);
    m_next= new QPushButton("Next", m_controlZone);
    m_zoom= new QSlider(Qt::Horizontal,m_controlZone);
    m_zoom->setTickInterval(10);
    m_zoom->setMinimum(1);
    m_zoom->setMaximum(100);
    m_zoom->setValue(50);
    layout->addWidget(m_start);
    layout->addWidget(m_next);
    layout->addWidget(m_zoom);
    m_controlZone->setLayout(layout);
    m_controlZone->adjustSize();
}
void QMapWidget::onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid)
{
    m_scene->initialize(int(xMinGrid), int(yMinGrid), int(xMaxGrid), int(yMaxGrid));
    sceneScaleChanged(250);
    //show();

    connect(m_zoom, SIGNAL(valueChanged(int)), this, SLOT(sceneScaleChanged(int)));
}

void QMapWidget::sceneScaleChanged(int i)
{
    double newScale = i/100.0;
    QMatrix oldMatrix = m_view->matrix();
    m_view->resetMatrix();
    //m_view->translate(oldMatrix.dx(), oldMatrix.dy());
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
