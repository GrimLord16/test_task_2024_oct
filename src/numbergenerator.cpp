#include "numbergenerator.h"

NumberGenerator::NumberGenerator(QObject *parent)
    :  QThread{parent}
{}
void NumberGenerator::startGenerating(){
    running = true;
    start();
}

void NumberGenerator::stopGenerating(){
    running = false;
}

void NumberGenerator::run(){
    while (running) {
        emit newNumberGenerated(number++);
        msleep(1000);
    }
}

int NumberGenerator::getNumber(){
    return number;
}
