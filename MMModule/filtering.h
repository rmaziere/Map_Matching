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

#include "file.h"
#include "track.h"

class Filtering : public QWidget {
    Q_OBJECT
public:
    Filtering();
    ~Filtering();

public slots:
    void getInfo(File fileT);
    void launchFiltre();

signals:
    void ready(double m_filtreSpat, int m_filtreTemp);

private:
    void nbPtTrack();
    void spatial();
    void temporal();

    QGroupBox* m_spat;
    QGroupBox* m_temp;

    QPushButton* m_boutonTemp;
    QPushButton* m_boutonSpat;

    QSlider* m_slidTemp;
    QLCDNumber* m_valueTemp;
    QSlider* m_slidSpat;
    QLCDNumber* m_valueSpat;
    QLabel* m_nbPtTrack;

    int m_ptTrack;

    double m_filtreSpat;
    int m_filtreTemp;

    int nextOk;
};

#endif // FILTERING_H
