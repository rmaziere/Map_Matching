#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "track.h"
#include "qmapviewer.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0): QObject(parent) {}

signals:

public slots:
};

#endif // CONTROLLER_H
