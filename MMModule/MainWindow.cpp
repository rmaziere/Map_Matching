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
    slideWidget1 = new QWidget();
    slideWidget2 = new QWidget();
    slideWidget3 = new QWidget();
    slideWidget4 = new Filtering();

    QVBoxLayout* slideWidget1layout = new QVBoxLayout();
    slideWidget1->setLayout(slideWidget1layout);
    QVBoxLayout* slideWidget2layout = new QVBoxLayout();
    slideWidget2->setLayout(slideWidget2layout);
    QVBoxLayout* slideWidget3layout = new QVBoxLayout();
    slideWidget3->setLayout(slideWidget3layout);

    QPushButton* b11 = new QPushButton("Qt");
    slideWidget1layout->addWidget(b11);
    QPushButton* b12 = new QPushButton("is cool !");
    slideWidget1layout->addWidget(b12);

    QPushButton* b21 = new QPushButton("Cool");
    slideWidget2layout->addWidget(b21);
    QPushButton* b22 = new QPushButton("is Qt !");
    slideWidget2layout->addWidget(b22);

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
    QObject::connect(buttonNext, SIGNAL(pressed()), slidingStacked, SLOT(slideInNext()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), qApp, SLOT(quit()));
}
