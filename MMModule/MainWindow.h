#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QtGui/QMainWindow>
#include <QtGui>
#include <QPushButton>
#include <QCheckBox>
#include <QListWidget>
#include <QSlider>

#include "SlidingStackedWidget.h"
#include "filtering.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void createGuiControlComponents();
    void createMainLayout();
    void createSubSlidingWidgets();
    void createConnections();
    void createSlidingStackedWidget();
    QPushButton *buttonNext;
    QPushButton *buttonCancel;

    SlidingStackedWidget *slidingStacked;
    QVBoxLayout *mainLayout;
    QGridLayout *controlPaneLayout;
    QWidget *centralWidget;
    QWidget *slideWidget1;
    QWidget *slideWidget2;
    QWidget *slideWidget3;
    Filtering *slideWidget4;
};

#endif // MAINWINDOW_H
