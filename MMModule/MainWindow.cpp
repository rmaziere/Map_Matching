#include "MainWindow.h"

// The Constructor calls the subfunctions for creation of the sample application

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
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
    //centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout();
    //centralWidget->setLayout(mainLayout);
    this->setLayout(mainLayout);
    controlPaneLayout = new QGridLayout();
    mainLayout->addWidget(slidingStacked);
    mainLayout->addLayout(controlPaneLayout);

    controlPaneLayout->addWidget(buttonCancel, 1, 1, 1, 1);
    controlPaneLayout->addWidget(buttonNext, 1, 2, 1, 1);

    process = new QProcessViewer(this);
    mainLayout->addWidget(process);
}

void MainWindow::createSubSlidingWidgets()
{
    slideWidget1 = new Loading();
    slideWidget2 = new Filtering();
    slideWidget3 = new QWidget();

    QVBoxLayout* slideWidget3layout = new QVBoxLayout();
    slideWidget3->setLayout(slideWidget3layout);

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
}

void MainWindow::createConnections()
{
    thread = new QThread();
    solver = new Solver();
    solver->moveToThread(thread);
    controller = new Controller();
    controller->m_qProcessViewer = process;
    controller->addSolver(solver);
    controller->connectSignals();

    QObject::connect(slideWidget1, SIGNAL(ready(File, File)), this, SLOT(readyToNext1(File, File)));
    QObject::connect(slideWidget1, SIGNAL(readyNext(File)), slideWidget2, SLOT(getInfo(File)));
    QObject::connect(slideWidget2, SIGNAL(ready(double, int)), this, SLOT(readyToNext2(double, int)));
    QObject::connect(buttonNext, SIGNAL(clicked()), slidingStacked, SLOT(slideInNext()));
    QObject::connect(buttonNext, SIGNAL(clicked()), this, SLOT(putNone()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::putNone()
{
    buttonNext->setEnabled(false);
}

void MainWindow::readyToNext1(File file1, File file2)
{
    solver->readFiles(file1, file2);
    if (!solver->grid.trackInGrid()) {
        QMessageBox::warning(this, "Erreur de fichiers", "Attention, l'emprise des données de correspond pas !");
    } else {
        buttonNext->setEnabled(true);
    }
}

void MainWindow::readyToNext2(double fSpat, int fTemp)
{
    if (fSpat != 0.00) {
        solver->filterSpace(fSpat);
    }
    if (fTemp != 0.00) {
        solver->filterTemp(fTemp);
    }
    buttonNext->setEnabled(true);
}
