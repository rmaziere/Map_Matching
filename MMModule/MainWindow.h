#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QWidget>

#include "SlidingStackedWidget.h"
#include "filtering.h"
#include "loading.h"

#include "GUI/controller.h"
#include "GUI/qprocessviewer.h"
#include "GUI/qmapwidget.h"
#include "grid.h"
#include "solver.h"
#include "track.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief readyToNext1 Pass informations
     * @param file1 File track
     * @param file2 File grid
     */
    void readyToNext1(File file1, File file2);
    /**
     * @brief readyToNext2 Pass informations
     * @param fSpat value of spatial filter
     * @param fTemp value of temporal filter
     */
    void readyToNext2(double fSpat, int fTemp);
    /**
     * @brief putNone Disable next button
     */
    void putNone();

protected:
    /**
     * @brief createGuiControlComponents
     */
    void createGuiControlComponents();
    /**
     * @brief createMainLayout
     */
    void createMainLayout();
    /**
     * @brief createSubSlidingWidgets
     */
    void createSubSlidingWidgets();
    /**
     * @brief createConnections
     */
    void createConnections();
    /**
     * @brief createSlidingStackedWidget
     */
    void createSlidingStackedWidget();
    QPushButton* buttonNext;
    QPushButton* buttonCancel;
    QThread* thread;
    Solver* solver;
    Controller* controller;

    SlidingStackedWidget* slidingStacked;
    QVBoxLayout* mainLayout;
    QHBoxLayout* affLayout;
    QGridLayout* controlPaneLayout;
    Loading* slideWidget1;
    Filtering* slideWidget2;
    QMapWidget* slideWidget3;

    QProcessViewer* process;

    /**
     * @brief Value of the first Slide
     */
    Track trace;
    Grid grille;
};

#endif // MAINWINDOW_H
