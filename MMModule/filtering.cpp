#include "filtering.h"

Filtering::Filtering()
{
    nbPtTrack();
    temporal();
    spatial();
    boutonXY();

    // Création d'un widget qui servira de fenêtre
    setFixedSize(500, 400);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_nbPtTrack);
    mainLayout->addWidget(m_temp);
    mainLayout->addWidget(m_spat);
    mainLayout->addWidget(m_boutonXY);
    setLayout(mainLayout);
    setWindowTitle("Filtrage");
}

Filtering::~Filtering()
{
}

void Filtering::boutonXY()
{
    m_boutonXY = new QGroupBox("");

    m_cancel = new QPushButton("Cancel");
    m_launch = new QPushButton("Launch");
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_cancel);
    vbox->addWidget(m_launch);
    vbox->addStretch(1);
    m_boutonXY->setLayout(vbox);
}

void Filtering::temporal()
{
    m_temp = new QGroupBox("Filtrage temporel (en sec)");

    m_valueTemp = new QLCDNumber();
    m_valueTemp->setSegmentStyle(QLCDNumber::Flat);

    m_slidTemp = new QSlider(Qt::Horizontal);
    m_slidTemp->setRange(0, 90);

    QObject::connect(m_slidTemp, SIGNAL(valueChanged(int)), m_valueTemp, SLOT(display(int)));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueTemp);
    vbox->addWidget(m_slidTemp);

    m_temp->setLayout(vbox);
}

void Filtering::spatial()
{
    m_spat = new QGroupBox("Filtrage spatial (en mètre)");

    m_valueSpat = new QLCDNumber();
    m_valueSpat->setSegmentStyle(QLCDNumber::Flat);

    m_slidSpat = new QSlider(Qt::Horizontal);
    m_slidSpat->setRange(0, 10);

    QObject::connect(m_slidSpat, SIGNAL(valueChanged(int)), m_valueSpat, SLOT(display(int)));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueSpat);
    vbox->addWidget(m_slidSpat);

    m_spat->setLayout(vbox);
}

void Filtering::nbPtTrack()
{
    m_nbPtTrack = new QLabel();
    m_nbPtTrack->setText("Your track had 0 GPS points.");
}
