#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "numberconsumer.h"
#include "numbergenerator.h"
#include "queuemanager.h"

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    NumberGenerator* generator;
    NumberConsumer* consumer;
    QueueManager* queueManager;

private:
    void toggleGenerator();
    void toggleConsumer();
    void refreshLists();
};
#endif // MAINWINDOW_H
