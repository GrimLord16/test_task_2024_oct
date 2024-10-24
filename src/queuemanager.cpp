#include "queuemanager.h"

QueueManager::QueueManager(QObject *parent)
    :  QThread{parent}
{}

//Logic below can be done also without signals/slots by polling or condition variable

void QueueManager::enqueueNumber(int number){
    mutex.lock();
    if (queue.size() >= 20) {
        queue.dequeue();
    }
    queue.enqueue(number);
    mutex.unlock();
}

void QueueManager::dequeueNumber(){
    mutex.lock();
    if (!queue.isEmpty()) {
        int number = queue.dequeue();
        emit numberDequeued(number);
    }
    mutex.unlock();
}

void QueueManager::run(){
    exec();
}

const QQueue<int>& QueueManager::getQueue() const{
    QMutexLocker locker(&mutex);
    return queue;
}
