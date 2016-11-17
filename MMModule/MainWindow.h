#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QThread>
#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui>

#include "SlidingStackedWidget.h"
#include "filtering.h"
#include "loading.h"

#include "GUI/controller.h"
#include "GUI/qprocessviewer.h"
#include "grid.h"
#include "solver.h"
#include "track.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void readyToNext1(File file1, File file2);
    void readyToNext2(double fSpat, int fTemp);
    void putNone();

protected:
    void createGuiControlComponents();
    void createMainLayout();
    void createSubSlidingWidgets();
    void createConnections();
    void createSlidingStackedWidget();
    QPushButton* buttonNext;
    QPushButton* buttonCancel;
    QThread* thread;
    Solver* solver;
    Controller* controller;

    SlidingStackedWidget* slidingStacked;
    QVBoxLayout* mainLayout;
    QGridLayout* controlPaneLayout;
    //QWidget* centralWidget;
    Loading* slideWidget1;
    Filtering* slideWidget2;
    QWidget* slideWidget3;
    QProcessViewer* process;

    /**
     * @brief Value of the first Slide
     */
    Track trace;
    Grid grille;
};

#endif // MAINWINDOW_H
