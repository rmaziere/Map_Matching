#ifndef QMAPVIEWER_H
#define QMAPVIEWER_H

#include <QWidget>

class QMapViewer : public QWidget
{
    Q_OBJECT
public:
    explicit QMapViewer(QWidget *parent = 0);

signals:
    void onSignalMessage(QString);

public slots:
};

#endif // QMAPVIEWER_H
