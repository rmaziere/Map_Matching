#ifndef AGILEPLUGIN_H
#define AGILEPLUGIN_H

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

public slots:
    // Slot called when the plugin is launched
    int run(int argc, char *argv[]);

private:
    QgisInterface * m_GISInterface; // GIS interface
    QAction * m_action; // Action in the menu bar
};

#endif
