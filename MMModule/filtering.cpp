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

    nextOk = 0;
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

    m_boutonTemp = new QPushButton("Ok");
    m_boutonTemp->setCheckable(true);

    QObject::connect(m_slidTemp, SIGNAL(valueChanged(int)), m_valueTemp, SLOT(display(int)));
    //QObject::connect(m_slidTemp, SIGNAL(valueChanged(int)), this, SLOT(launchFiltreTemp(int)));
    QObject::connect(m_boutonTemp, SIGNAL(clicked()), this, SLOT(launchFiltre()));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueTemp);
    vbox->addWidget(m_slidTemp);
    vbox->addWidget(m_boutonTemp);
    m_temp->setLayout(vbox);
}

void Filtering::spatial()
{
    m_spat = new QGroupBox("Filtrage spatial (en centimetre)");

    m_valueSpat = new QLCDNumber();
    m_valueSpat->setSegmentStyle(QLCDNumber::Flat);

    m_slidSpat = new QSlider(Qt::Horizontal);
    m_slidSpat->setRange(0, 1000);

    m_boutonSpat = new QPushButton("Ok");
    m_boutonSpat->setCheckable(true);

    QObject::connect(m_slidSpat, SIGNAL(valueChanged(int)), m_valueSpat, SLOT(display(int)));
    //QObject::connect(m_slidSpat, SIGNAL(valueChanged(int)), this, SLOT(launchFiltreSpat(int)));
    QObject::connect(m_boutonSpat, SIGNAL(clicked()), this, SLOT(launchFiltre()));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_valueSpat);
    vbox->addWidget(m_slidSpat);
    vbox->addWidget(m_boutonSpat);
    m_spat->setLayout(vbox);
}

void Filtering::nbPtTrack()
{
    m_nbPtTrack = new QLabel();
}

void Filtering::getInfo(File fileT)
{
    QString file = fileT.filePath.at(0) + fileT.fileName.at(0) + "." + fileT.fileExtension.at(0);
    Track trace;
    trace.readFromCSV(file);
    m_ptTrack = trace.getPoints().size();

    m_nbPtTrack->setText((QString("Your track had ") + QString::number(m_ptTrack)) + " GPS points.");
}

void Filtering::launchFiltre()
{
    nextOk += 1;
    if (m_boutonSpat->isChecked()) {
        m_filtreSpat = m_slidSpat->value() / 100;
        m_slidSpat->setEnabled(false);
    }
    if (m_boutonTemp->isChecked()) {
        m_filtreTemp = m_slidTemp->value();
        m_slidTemp->setEnabled(false);
    }
    if (nextOk >= 2) {
        emit ready(m_filtreSpat, m_filtreTemp);
    }
}
