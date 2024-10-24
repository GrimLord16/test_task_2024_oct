#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Timer to refresh the list widgets
    QTimer* refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &MainWindow::refreshLists);
    refreshTimer->start(200);

    // Initialize the threads
    generator = new NumberGenerator(this);
    consumer = new NumberConsumer(this);
    queueManager = new QueueManager(this);

    connect(generator, &NumberGenerator::newNumberGenerated, queueManager, &QueueManager::enqueueNumber);
    connect(consumer, &NumberConsumer::requestDequeue, queueManager, &QueueManager::dequeueNumber);
    connect(queueManager, &QueueManager::numberDequeued, consumer, &NumberConsumer::consumeNumber);

    connect(ui->generatorButton, &QPushButton::clicked, this, &MainWindow::toggleGenerator);
    connect(ui->consumerButton, &QPushButton::clicked, this, &MainWindow::toggleConsumer);

    queueManager->start();
}

void MainWindow::toggleGenerator(){
    if (generator->isRunning()) {
        generator->stopGenerating();
    } else {
        generator->startGenerating();
    }
}

void MainWindow::toggleConsumer(){

    if (consumer->isRunning()) {
        consumer->stopConsuming();
    } else {
        consumer->startConsuming();
    }
}

void MainWindow::refreshLists(){

    ui->queueListBox->clear();
    ui->consumerListBox->clear();
    ui->generatorListBox->clear();

    QStringList queueItems;
    for (int num : queueManager->getQueue()) {
        queueItems << QString::number(num);
    }

    ui->queueListBox->addItem(queueItems.join(" "));

    QStringList consumerItems;
    for (int num : consumer->getConsumerList()) {
        consumerItems << QString::number(num);
    }

    ui->consumerListBox->addItem(consumerItems.join(" "));


    ui->generatorListBox->addItem(QString::number(generator->getNumber()));
}


MainWindow::~MainWindow()
{
    generator->stopGenerating();
    generator->wait();

    consumer->stopConsuming();
    consumer->wait();

    queueManager->quit();
    queueManager->wait();
    delete ui;
}
