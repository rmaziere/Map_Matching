#include "MainWindow.h"

// The Constructor calls the subfunctions for creation of the sample application

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    createGuiControlComponents();
    createSubSlidingWidgets();
    createSlidingStackedWidget();
    createMainLayout();
    createConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createGuiControlComponents()
{
    buttonNext = new QPushButton(tr("Next"));
    buttonNext->setEnabled(false);
    buttonCancel = new QPushButton(tr("Cancel"));
}

void MainWindow::createMainLayout()
{
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);
    controlPaneLayout = new QGridLayout();
    mainLayout->addWidget(slidingStacked);
    mainLayout->addLayout(controlPaneLayout);

    controlPaneLayout->addWidget(buttonCancel, 1, 1, 1, 1);
    controlPaneLayout->addWidget(buttonNext, 1, 2, 1, 1);

    this->setCentralWidget(centralWidget);
}

void MainWindow::createSubSlidingWidgets()
{
    slideWidget1 = new Loading();
    slideWidget2 = new Filtering();
    slideWidget3 = new QWidget();
    slideWidget4 = new QWidget();

    QVBoxLayout* slideWidget4layout = new QVBoxLayout();
    slideWidget4->setLayout(slideWidget4layout);
    QVBoxLayout* slideWidget3layout = new QVBoxLayout();
    slideWidget3->setLayout(slideWidget3layout);


    QPushButton* b41 = new QPushButton("Cool");
    slideWidget4layout->addWidget(b41);
    QPushButton* b42 = new QPushButton("is Qt !");
    slideWidget4layout->addWidget(b42);

    QPushButton* b31 = new QPushButton("Isn't");
    slideWidget3layout->addWidget(b31);
    QPushButton* b32 = new QPushButton("Qt cool ?");
    slideWidget3layout->addWidget(b32);
}

void MainWindow::createSlidingStackedWidget()
{
    slidingStacked = new SlidingStackedWidget(this);
    slidingStacked->addWidget(slideWidget1);
    slidingStacked->addWidget(slideWidget2);
    slidingStacked->addWidget(slideWidget3);
    slidingStacked->addWidget(slideWidget4);
}

void MainWindow::createConnections()
{
    QObject::connect(slideWidget1, SIGNAL(ready()), this, SLOT(readyToNext()));
    QObject::connect(buttonNext, SIGNAL(clicked()), slidingStacked, SLOT(slideInNext()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::readyToNext()
{
    buttonNext->setEnabled(true);
}
