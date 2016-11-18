QT += core
QT += gui

TEMPLATE = app
CONFIG += c++11
CONFIG -= console app_bundle
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lgtest -lpthread

SOURCES += main.cpp \
    ../MMModule/grid.cpp \
    ../MMModule/point.cpp \
    ../MMModule/pointroad.cpp \
    ../MMModule/pointGPS.cpp \
    ../MMModule/road.cpp \
    ../MMModule/sauvegarde.cpp \
    ../MMModule/track.cpp \
    ../MMModule/emissionprobability.cpp \
    ../MMModule/file.cpp \
    ../MMModule/filtering.cpp \
    ../MMModule/loading.cpp \
    ../MMModule/main.cpp \
    ../MMModule/MainWindow.cpp \
    ../MMModule/SlidingStackedWidget.cpp \
    ../MMModule/solver.cpp

HEADERS += \
    ../MMModule/myexception.h \
    ../MMModule/grid.h \
    ../MMModule/point.h \
    ../MMModule/pointroad.h \
    ../MMModule/pointGPS.h \
    ../MMModule/road.h \
    ../MMModule/sauvegarde.h \
    ../MMModule/track.h \
    pointtest.h \
    tracktest.h \
    pointgpstest.h \
    roadtest.h \
    gridtest.h \
    ../MMModule/emissionprobability.h \
    ../MMModule/file.h \
    ../MMModule/filtering.h \
    ../MMModule/loading.h \
    ../MMModule/MainWindow.h \
    ../MMModule/SlidingStackedWidget.h \
    ../MMModule/solver.h
