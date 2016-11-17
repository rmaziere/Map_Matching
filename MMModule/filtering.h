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

class Filtering : public QWidget {
    Q_OBJECT
public:
    Filtering();
    ~Filtering();

public slots:
    void launchFiltre(int);

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
};

#endif // FILTERING_H
