#include "numberconsumer.h"

NumberConsumer::NumberConsumer(QObject *parent)
    :  QThread{parent}
{}

void NumberConsumer::startConsuming(){
    running = true;
    start();
}

void NumberConsumer::stopConsuming(){
    running = false;
}

void NumberConsumer::run(){
    while (running) {
        emit requestDequeue();
        msleep(1000);
    }
}

void NumberConsumer::consumeNumber(int number){
    dequeuedNumbers.append(number);
}

const QList<int>& NumberConsumer::getConsumerList() const{
    return dequeuedNumbers;
}
