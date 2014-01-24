#ifndef ADVANCEDTIMER_H
#define ADVANCEDTIMER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class AdvancedTimer : public QObject
{
    Q_OBJECT
private:
    QTimer timer;
    QTime time;
    int tonext;
    int _interval;
public:
    explicit AdvancedTimer(QObject *parent = 0);
    bool isActive();
    void start();
    void stop();
    void setInterval(int ms);
    int interval();
    void pause();
    void resume();
signals:
    void timeout();
private slots:
    void onTimeout();
};

#endif // ADVANCEDTIMER_H
