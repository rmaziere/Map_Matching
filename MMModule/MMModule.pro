QT += core
QT += gui
QT += widgets

#DEFINES += _GTEST

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

TARGET = sandbox
CONFIG -= console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    file.cpp \
    pointGPS.cpp \
    track.cpp \
    point.cpp \
    road.cpp \
    solver.cpp \
    grid.cpp \
    pointroad.cpp \
    loading.cpp \
    KDTreeAlgos/box.cpp \
    KDTreeAlgos/boxnode.cpp \
    KDTreeAlgos/kdtree.cpp \
    emissionprobability.cpp \
    KDTreeAlgos/kdtreeviewer.cpp \
    filtering.cpp \
    MainWindow.cpp \
    SlidingStackedWidget.cpp \
    GUI/controller.cpp \
    GUI/qprocessviewer.cpp \
    GUI/qmapwidget.cpp \
    GUI/qmapscene.cpp

HEADERS += \
    file.h \
    track.h \
    pointGPS.h \
    point.h \
    road.h \
    solver.h \
    grid.h \
    pointroad.h \
    loading.h \
    KDTreeAlgos/box.h \
    KDTreeAlgos/boxnode.h \
    KDTreeAlgos/kdtree.h \
    emissionprobability.h \
    KDTreeAlgos/kdtreeviewer.h \
    filtering.h \
    SlidingStackedWidget.h \
    MainWindow.h \
    GUI/controller.h \
    GUI/qprocessviewer.h \
    GUI/qmapwidget.h \
    GUI/qmapscene.h

