QT += core
QT += gui

CONFIG += c++11

TARGET = sandbox
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../pointTrace.cpp \
    ../trace.cpp

HEADERS += \
    ../pointTrace.h \
    ../trace.h

