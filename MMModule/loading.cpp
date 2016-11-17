#include "loading.h"

Loading::Loading()
    : QWidget()
{
    country();
    track();
    grid();
    nextOk = 0;

    // Création d'un widget qui servira de fenêtre
    setFixedSize(500, 400);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_country);
    mainLayout->addWidget(m_track);
    mainLayout->addWidget(m_grid);
    setLayout(mainLayout);
}

Loading::~Loading()
{
}

void Loading::country()
{
    m_country = new QGroupBox("Country");

    m_fr = new QRadioButton("France");
    m_usa = new QRadioButton("USA");

    QObject::connect(m_fr, SIGNAL(clicked()), this, SLOT(getCountry()));
    QObject::connect(m_usa, SIGNAL(clicked()), this, SLOT(getCountry()));

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(m_fr);
    vbox->addWidget(m_usa);
    vbox->addStretch(1);
    m_country->setLayout(vbox);
}

void Loading::grid()
{
    m_grid = new QGroupBox("Grid");
    m_fileGrid = new QLabel(this);

    m_csvGrid = new QPushButton("SHP");
    m_csvGrid->setCheckable(true);

    QObject::connect(m_csvGrid, SIGNAL(clicked()), this, SLOT(loadFileGrid()));

    QVBoxLayout* vbox = new QVBoxLayout;
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
    m_csvTrack->setCheckable(true);
    m_shpTrack->setCheckable(true);
    m_fileGPS = new QLabel(this);

    QObject::connect(m_csvTrack, SIGNAL(clicked()), this, SLOT(loadFileCSVTrack()));
    QObject::connect(m_shpTrack, SIGNAL(clicked()), this, SLOT(loadFileSHPTrack()));

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(m_csvTrack);
    vbox->addWidget(m_shpTrack);
    vbox->addWidget(m_fileGPS);
    vbox->addStretch(1);
    m_track->setLayout(vbox);
}

void Loading::loadFileCSVTrack()
{
    int result = fileCSVTrack.selectFilesToOpen("csv");
    if (result == 1) {
        m_fileGPS->setText("1 file loaded");
        m_csvTrack->setEnabled(false);
        m_shpTrack->setEnabled(false);
        nextOk += 1;
        launchFiles();
    }
}

void Loading::loadFileSHPTrack()
{
    int result = fileSHPTrack.selectFilesToOpen("shp");
    if (result == 1) {
        int conv = fileSHPTrack.shp2csv("Point");
        if (conv == 1) {
            m_fileGPS->setText("1 file loaded");
            m_csvTrack->setEnabled(false);
            m_shpTrack->setEnabled(false);
            nextOk += 1;
            launchFiles();
        }
    }
}

void Loading::loadFileGrid()
{
    int result = fileSHPGrid.selectFilesToOpen("shp");
    if (result == 1) {
        int conv = fileSHPGrid.shp2csv("Polyline");
        if (conv == 1) {
            m_fileGrid->setText("1 file loaded");
            m_csvGrid->setEnabled(false);
            nextOk += 1;
            launchFiles();
        }
    }
}

void Loading::getCountry() //A modifier
{
    //if (m_fr->isChecked())
        //cout << "fr";
    //else
        //cout << "usa";
    launchFiles();
}

void Loading::launchFiles()
{
    if ((m_fr->isChecked() || m_usa->isChecked()) && (nextOk == 2))
    {
        if (fileSHPTrack.fileName.isEmpty())
        {
            emit ready(fileCSVTrack, fileSHPGrid);
        }
        else
        {
            emit ready(fileSHPTrack, fileSHPGrid);
        }
    }
}
