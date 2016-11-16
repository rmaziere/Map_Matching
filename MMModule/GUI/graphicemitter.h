#ifndef GRAPHICEMITTER_H
#define GRAPHICEMITTER_H

#include <QObject>

class GraphicEmitter : public QObject
{
    Q_OBJECT
public:
    explicit GraphicEmitter(QObject *parent = 0);
    void testMessagePoint(QString);
signals:
    void signalDrawPoint(QString);
    void signalDrawRoad(QString);
public slots:
};

#endif // GRAPHICEMITTER_H
