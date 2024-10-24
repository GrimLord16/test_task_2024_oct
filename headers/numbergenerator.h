#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <QObject>
#include <QThread>

class NumberGenerator : public QThread
{
    Q_OBJECT
public:
    explicit NumberGenerator(QObject *parent = nullptr);
    void run() override;
    void startGenerating();
    void stopGenerating();
    int getNumber();

signals:
    void newNumberGenerated(int number);

private:
    bool running = false;
    int number = 0;
};

#endif // NUMBERGENERATOR_H
