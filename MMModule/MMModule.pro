QT += core
QT += gui

CONFIG += c++11

TARGET = sandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sauvegarde.cpp \
    file.cpp \
    pointGPS.cpp \
    track.cpp \
    network.cpp \
    point.cpp \
    road.cpp

HEADERS += \
    sauvegarde.h \
    file.h \
    track.h \
    pointGPS.h \
    myexception.h \
    network.h \
    point.h \
    road.h
