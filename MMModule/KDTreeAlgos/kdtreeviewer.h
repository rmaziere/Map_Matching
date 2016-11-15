#ifndef KDTREEVIEWER_H
#define KDTREEVIEWER_H

#include <QImage>

class KDTreeViewer
{
public:
    KDTreeViewer();

protected:
    QImage m_image;
    double m_xshift;

};

#endif // KDTREEVIEWER_H
