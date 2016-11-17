#include "qprocessviewer.h"

#include <QVBoxLayout>

QProcessViewer::QProcessViewer(QWidget* parent)
    : QWidget(parent)
{
    textEdit = new QTextEdit;
    textEdit->setReadOnly(true);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    startSolver = new QPushButton(tr("&Start Solver"));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(startSolver);
    layout->addWidget(closeButton);
    setLayout(layout);

    setWindowTitle(tr("Logs"));
}

void QProcessViewer::onSignalMessage(QString s)
{
    textEdit->append(s);
}
/*
void QProcessViewer::onSignalDrawPoint(QString s)
{
    textEdit->append(s);
}

void QProcessViewer::onSignalDrawRoad(QString s)
{
    textEdit->append(s);
}
*/
