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
    ../MMModule/track.cpp

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
    gridtest.h
