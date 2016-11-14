#include "loading.h"

Loading::Loading() : QWidget()
{
    country();
    track();
    grid();
    boutonXY();

    // Création d'un widget qui servira de fenêtre
    setFixedSize(500, 400);



     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(m_country);
     mainLayout->addWidget(m_track);
     mainLayout->addWidget(m_grid);
     mainLayout->addWidget(m_boutonXY);
     setLayout(mainLayout);
     setWindowTitle("Launch");

}

Loading::~Loading()
{
}

void Loading::boutonXY()
{
    m_boutonXY = new QGroupBox("");

    m_cancel = new QPushButton("Cancel");
    m_launch = new QPushButton("Launch");
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(m_cancel);
    vbox->addWidget(m_launch);
    vbox->addStretch(1);
    m_boutonXY->setLayout(vbox);

}

void Loading::country()
{
    m_country = new QGroupBox("Country");

    QRadioButton *radio1 = new QRadioButton("France");
    QRadioButton *radio2 = new QRadioButton("USA");
    radio1->setChecked(true);

    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    m_country->setLayout(vbox);
}

void Loading::grid()
{
    m_grid = new QGroupBox("Grid");
    m_fileGrid = new QLabel(this);

    m_csvGrid = new QPushButton("CSV");
    m_csvGrid->setGeometry(0, 2, 0, 3);

    QObject::connect(m_csvGrid, SIGNAL(clicked()), this, SLOT(loadFileGrid()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_csvGrid);
    vbox->addWidget(m_fileGrid);
    vbox->addStretch(1);
    m_grid->setLayout(vbox);
}

void Loading::track()
{
    m_track = new QGroupBox("GPS Track");

    m_csvTrack = new QPushButton("CSV");
    m_shpTrack = new QPushButton("SHP");
    m_fileGPS = new QLabel(this);

    QObject::connect(m_csvTrack, SIGNAL(clicked()), this, SLOT(loadFileTrack()));
    QObject::connect(m_shpTrack, SIGNAL(clicked()), this, SLOT(loadFileTrack()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_csvTrack);
    vbox->addWidget(m_shpTrack);
    vbox->addWidget(m_fileGPS);
    vbox->addStretch(1);
    m_track->setLayout(vbox);
}

void Loading::loadFileTrack()
{
    m_fileGPS->setText("1 file loaded");
    m_csvTrack->setEnabled(false);
    m_shpTrack->setEnabled(false);
}

void Loading::loadFileGrid()
{
    m_fileGrid->setText("1 file loaded");
    m_csvGrid->setEnabled(false);
}
