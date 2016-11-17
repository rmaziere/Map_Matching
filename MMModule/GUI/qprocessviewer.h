#ifndef QPROCESSVIEWER_H
#define QPROCESSVIEWER_H

#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class QProcessViewer : public QWidget {
    Q_OBJECT
public:
    explicit QProcessViewer(QWidget* parent = 0);

    QTextEdit* textEdit;
    QPushButton* startSolver;
    QPushButton* closeButton;

signals:
    void signalStartSolver();

public slots:
    void onSignalMessage(QString s);
    //void onSignalDrawPoint(QString);
    //void onSignalDrawRoad(QString);

private:
};

#endif // QPROCESSVIEWER_H
