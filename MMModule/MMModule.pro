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
    track.cpp

HEADERS += \
    sauvegarde.h \
    exception.h \
    file.h \
    exception.h \
    track.h \
    pointGPS.h
