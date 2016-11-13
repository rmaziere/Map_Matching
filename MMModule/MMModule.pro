QT += core
QT += gui

CONFIG += c++11

TARGET = sandbox
CONFIG -= console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sauvegarde.cpp \
    file.cpp \
    pointGPS.cpp \
    track.cpp \
    point.cpp \
    road.cpp \
    solver.cpp \
    grid.cpp \
    pointroad.cpp \
    KDTreeAlgos/box.cpp \
    KDTreeAlgos/boxnode.cpp \
    KDTreeAlgos/kdtree.cpp \
    emissionprobability.cpp


HEADERS += \
    sauvegarde.h \
    file.h \
    track.h \
    pointGPS.h \
    myexception.h \
    point.h \
    road.h \
    myexception.h \
    solver.h \
    grid.h \
    pointroad.h \
    KDTreeAlgos/box.h \
    KDTreeAlgos/boxnode.h \
    KDTreeAlgos/kdtree.h \
    emissionprobability.h

