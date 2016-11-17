#include "filtering.h"

Filtering::Filtering()
{
    nbPtTrack();
    temporal();
    spatial();

    // Création d'un widget qui servira de fenêtre
    setFixedSize(500, 400);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_nbPtTrack);
    mainLayout->addWidget(m_temp);
    mainLayout->addWidget(m_spat);
    setLayout(mainLayout);
}

Filtering::~Filtering()
{
}

void Filtering::temporal()
{
    m_temp = new QGroupBox("Filtrage temporel (en sec)");

    m_valueTemp = new QLCDNumber();
    m_valueTemp->setSegmentStyle(QLCDNumber::Flat);

    m_slidTemp = new QSlider(Qt::Horizontal);
    m_slidTemp->setRange(0, 90);

    QObject::connect(m_slidTemp, SIGNAL(valueChanged(int)), m_valueTemp, SLOT(display(int)));
    QObject::connect(m_slidTemp, SIGNAL(valueChanged(int)), this, SLOT(launchFiltreTemp(int)));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueTemp);
    vbox->addWidget(m_slidTemp);
    m_temp->setLayout(vbox);
}

void Filtering::spatial()
{
    m_spat = new QGroupBox("Filtrage spatial (en metre)");

    m_valueSpat = new QLCDNumber();
    m_valueSpat->setSegmentStyle(QLCDNumber::Flat);

    m_slidSpat = new QSlider(Qt::Horizontal);
    m_slidSpat->setRange(0, 10);

    QObject::connect(m_slidSpat, SIGNAL(valueChanged(int)), m_valueSpat, SLOT(display(int)));
    QObject::connect(m_slidSpat, SIGNAL(valueChanged(int)), this, SLOT(launchFiltreSpat(int)));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueSpat);
    vbox->addWidget(m_slidSpat);
    m_spat->setLayout(vbox);
}

void Filtering::nbPtTrack()
{
    m_nbPtTrack = new QLabel();
    //m_nbPtTrack->setText((QString("Your track had ") + QString::number(m_ptTrack)) + " GPS points.");
}

void Filtering::launchFiltreSpat(int i)
{
    m_filtreSpat = i;
}

void Filtering::launchFiltreTemp(int i)
{
    m_filtreTemp = i;
}

void Filtering::getInfo(File fileT, File fileG)
{
    QString file = fileT.filePath.at(0) + fileT.fileName.at(0) + "." + fileT.fileExtension.at(0);
    Track trace;
    trace.readFromCSV(file);
    m_ptTrack = trace.getPoints().size();
    cout << m_ptTrack;

    m_nbPtTrack->setText((QString("Your track had ") + QString::number(m_ptTrack)) + " GPS points.");
}
