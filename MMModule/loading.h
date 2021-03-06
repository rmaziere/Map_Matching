#ifndef LOADING_H
#define LOADING_H

#include <QApplication>
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
    /**
     * @brief loadFileCSVTrack Get File of SHP track
     */
    void loadFileCSVTrack();
    /**
     * @brief loadFileSHPTrack Get File of CSV track
     */
    void loadFileSHPTrack();
    /**
     * @brief loadFileGrid Get File of grid
     */
    void loadFileGrid();
    /**
     * @brief getCountry Choose country
     */
    void getCountry();

signals:
    /**
     * @brief ready Emit files informations
     */
    void ready(File, File);
    /**
     * @brief readyNext track file informations
     */
    void readyNext(File);

private:
    /**
     * @brief country
     */
    void country();
    /**
     * @brief track
     */
    void track();
    /**
     * @brief grid
     */
    void grid();
    /**
     * @brief launchFiles
     */
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
