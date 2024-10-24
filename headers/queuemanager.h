#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QQueue>
class QueueManager : public QThread
{
    Q_OBJECT
public:
    explicit QueueManager(QObject *parent = nullptr);
    void run() override;
    const QQueue<int>& getQueue() const;
public slots:
    void enqueueNumber(int number);

    void dequeueNumber();

signals:
    void numberDequeued(int number);
private:
    mutable QMutex mutex;
    QQueue<int> queue;
};

#endif // QUEUEMANAGER_H
