#ifndef LOADING_H
#define LOADING_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QObject>

class Loading : public QWidget
{
    Q_OBJECT

public:
    Loading();
    ~Loading();

public slots:
    //void changerLargeur(int largeur);
    void loadFileTrack();
    void loadFileGrid();

signals:
    //void agrandissementMax();

private:
    QGridLayout *grille;
    void country();
    void track();
    void grid();
    void boutonXY();

    QGroupBox *m_country;
    QGroupBox *m_track;
    QGroupBox *m_grid;
    QGroupBox *m_boutonXY;

    QPushButton *m_csvTrack;
    QPushButton *m_shpTrack;
    QPushButton *m_csvGrid;
    QLabel *m_fileGPS;
    QLabel *m_fileGrid;

    QPushButton *m_cancel;
    QPushButton *m_launch;



};

#endif // LOADING_H
