#ifndef NUMBERCONSUMER_H
#define NUMBERCONSUMER_H

#include <QObject>
#include <QThread>
#include <QList>

class NumberConsumer : public QThread
{
    Q_OBJECT
public:
    explicit NumberConsumer(QObject *parent = nullptr);
    void run() override;

    void startConsuming();
    void stopConsuming();
    const QList<int> &getConsumerList() const;

signals:
    void requestDequeue();

public slots:
    void consumeNumber(int number);

private:
    bool running = false;
    QList<int> dequeuedNumbers;
};

#endif // NUMBERCONSUMER_H
