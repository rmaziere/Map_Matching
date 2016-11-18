#ifndef GEOMATICSPROJET_H
#define GEOMATICSPROJET_H

#include <QObject>
#include <iostream>
#include "qgisplugin.h" // Plugin interface

#include <math.h>
#include <vector>
#include <limits.h>
#include <QApplication>
#include <QFileDialog>
#include <math.h>
#include <vector>
#include <limits.h>

#include "../MMModule/file.h"
#include "../MMModule/grid.h"
#include "../MMModule/myexception.h"
#include "../MMModule/pointGPS.h"
#include "../MMModule/track.h"
#include "../MMModule/loading.h"

// Forward declarations
class QAction;
class QgisInterface;

// Declaration of the GeomaticsProjet class
class GeomaticsProjet: public QObject, public QgisPlugin
{
Q_OBJECT

public:
    // Constructor (interface is passed at construction)
    explicit GeomaticsProjet(QgisInterface * interface);

    // Called when the plugin is enabled
    void initGui() override;

    // Called when the plugin is disabled
    void unload() override;

    // Called class Track & Grid
    void dev_class();

    // Called thread and GUI
    //void dev_thread(); // Crash Qgis

public slots:
    // Slot called when the plugin is launched
    void run();

private:
    QgisInterface * m_GISInterface; // GIS interface
    QAction * m_action; // Action in the menu bar
};

#endif
