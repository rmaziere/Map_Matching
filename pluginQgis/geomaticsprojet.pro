TEMPLATE = lib
TEMPLATE = app

CONFIG = qt
CONFIG += c++11
CONFIG -= console app_bundle

QT += xml widgets
QT += core
QT += gui

LIBS += -L/usr/lib -lqgis_core -lqgis_gui
LIBS += -lgtest -lpthread

INCLUDEPATH += /usr/include/qgis/

SOURCES += geomaticsprojet.cpp \
    ../MMModule/emissionprobability.cpp \
    ../MMModule/file.cpp \
    ../MMModule/grid.cpp \
    ../MMModule/loading.cpp \
    ../MMModule/sauvegarde.cpp \
    ../MMModule/solver.cpp \
    ../MMModule/track.cpp \
    ../MMModule/point.cpp \
    ../MMModule/pointGPS.cpp \
    ../MMModule/pointroad.cpp \
    ../MMModule/road.cpp \
    ../MMModule/KDTreeAlgos/box.cpp \
    ../MMModule/KDTreeAlgos/boxnode.cpp \
    ../MMModule/KDTreeAlgos/kdtree.cpp \
    ../MMModule/KDTreeAlgos/kdtreeviewer.cpp \
    main.cpp

HEADERS += geomaticsprojet.h \
    ../MMModule/emissionprobability.h \
    ../MMModule/file.h \
    ../MMModule/grid.h \
    ../MMModule/loading.h \
    ../MMModule/road.h \
    ../MMModule/sauvegarde.h \
    ../MMModule/solver.h \
    ../MMModule/track.h \
    ../MMModule/myexception.h \
    ../MMModule/point.h \
    ../MMModule/pointGPS.h \
    ../MMModule/pointroad.h \
    ../MMModule/KDTreeAlgos/kdtreeviewer.h \
    ../MMModule/KDTreeAlgos/box.h \
    ../MMModule/KDTreeAlgos/boxnode.h \
    ../MMModule/KDTreeAlgos/kdtree.h

DEST = libgeomaticsprojet.so

DEFINES += GUI_EXPORT= CORE_EXPORT=

DISTFILES +=

SUBDIRS += \
    ../MMModule/MMModule.pro

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = build
OBJECTS_DIR = build/.o
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui

#QMAKE_POST_LINK += $$quote(cp build/libgeomaticsprojet.so.1.0.0 /usr/lib/qgis/plugins/libgeomaticsprojet.so)
