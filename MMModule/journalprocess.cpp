#include "journalprocess.h"
#include "qdebugstream.h"
#include <QTextEdit>

JournalProcess::JournalProcess()
    : QScrollArea()
{
    setWindowTitle("JournalProcess");

    // setWidgetResizable();
}

JournalProcess::~JournalProcess()
{
}
