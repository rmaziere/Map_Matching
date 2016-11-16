#include "graphicemitter.h"

GraphicEmitter::GraphicEmitter(QObject *parent) : QObject(parent)
{

}

void GraphicEmitter::testMessagePoint(QString s)
{
    emit signalDrawPoint(s);
}
