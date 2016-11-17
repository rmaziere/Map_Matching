#ifndef FILTERING_H
#define FILTERING_H

#include <QApplication>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLCDNumber>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "track.h"
#include "file.h"

class Filtering : public QWidget {
    Q_OBJECT
public:
    Filtering();
    ~Filtering();

public slots:
    void launchFiltreSpat(int);
    void launchFiltreTemp(int);
    void getInfo(File fileT, File fileG);

signals:
    void ready();

private:
    void nbPtTrack();
    void spatial();
    void temporal();

    QGroupBox* m_spat;
    QGroupBox* m_temp;
    QGroupBox* m_boutonXY;

    QSlider* m_slidTemp;
    QLCDNumber* m_valueTemp;
    QSlider* m_slidSpat;
    QLCDNumber* m_valueSpat;
    QLabel* m_nbPtTrack;

    int m_ptTrack;

    int m_filtreSpat = 0;
    int m_filtreTemp = 0;
};

#endif // FILTERING_H
