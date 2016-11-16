#ifndef QMAPVIEWER_H
#define QMAPVIEWER_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

class QMapViewer : public QWidget {
    Q_OBJECT
public:
    explicit QMapViewer(QWidget *parent = 0);

    QTextEdit *textEdit;
    QPushButton *startSolver;
    QPushButton *closeButton;

signals:
    void signalStartSolver();

public slots:
    void onSignalMessage(QString s);
    void onSignalDrawPoint(QString);
    void onSignalDrawRoad(QString);

private:

};

#endif // QMAPVIEWER_H
