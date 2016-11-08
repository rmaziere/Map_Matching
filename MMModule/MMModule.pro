QT += core
QT += gui

CONFIG += c++11

TARGET = sandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sauvegarde.cpp \
    PointGPS.cpp \
    Track.cpp

HEADERS += \
    sauvegarde.h \
    ../exception.h \
    PointGPS.h \
    Track.h
