TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

LIBS += -lgtest -lpthread

SOURCES += main.cpp \
    ../MMModule/file.cpp \
    ../MMModule/network.cpp \
    ../MMModule/point.cpp \
    ../MMModule/pointGPS.cpp \
    ../MMModule/road.cpp \
    ../MMModule/sauvegarde.cpp \
    ../MMModule/track.cpp

HEADERS += \
    pointtest.h \
    ../MMModule/file.h \
    ../MMModule/myexception.h \
    ../MMModule/network.h \
    ../MMModule/point.h \
    ../MMModule/pointGPS.h \
    ../MMModule/road.h \
    ../MMModule/sauvegarde.h \
    ../MMModule/track.h \
    tracktest.h \
    pointgpstest.h
