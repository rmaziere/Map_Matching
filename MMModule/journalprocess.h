#ifndef JOURNALPROCESS_H
#define JOURNALPROCESS_H
#include <QApplication>
#include <QObject>
#include <QScrollArea>
#include <QWidget>

class JournalProcess : public QScrollArea {
    Q_OBJECT
public:
    JournalProcess();
    ~JournalProcess();

public slots:

signals:

private:
};

#endif // JOURNALPROCESS_H
