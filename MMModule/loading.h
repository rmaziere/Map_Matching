#ifndef LOADING_H
#define LOADING_H

#include <QApplication>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

#include "file.h"

class Loading : public QWidget {
    Q_OBJECT

public:
    Loading();
    ~Loading();

    File fileSHPGrid;
    File fileSHPTrack;
    File fileCSVTrack;

public slots:
    void loadFileCSVTrack();
    void loadFileSHPTrack();
    void loadFileGrid();
    void getCountry();


signals:
    void ready(File, File);

private:
    void country();
    void track();
    void grid();

    void launchFiles();

    QGroupBox* m_country;
    QGroupBox* m_track;
    QGroupBox* m_grid;
    QGroupBox* m_boutonXY;

    QRadioButton* m_fr;
    QRadioButton* m_usa;

    QPushButton* m_csvTrack;
    QPushButton* m_shpTrack;
    QPushButton* m_csvGrid;
    QLabel* m_fileGPS;
    QLabel* m_fileGrid;

    int nextOk;
};

#endif // LOADING_H
