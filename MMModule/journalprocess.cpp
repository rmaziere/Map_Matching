#include "journalprocess.h"
#include <QTextEdit>
#include "qdebugstream.h"

JournalProcess::JournalProcess() : QScrollArea()
{
    setWindowTitle("JournalProcess");

   // setWidgetResizable();

}

JournalProcess::~JournalProcess()
{
}
