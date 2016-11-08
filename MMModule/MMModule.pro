QT += core
QT += gui

CONFIG += c++11

TARGET = sandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    pointTrace.cpp \
    trace.cpp \
    sauvegarde.cpp \
    distance.cpp

HEADERS += \
    pointTrace.h \
    trace.h \
    sauvegarde.h \
    ../exception.h \
    distance.h
