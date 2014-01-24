#include "advancedtimer.h"

AdvancedTimer::AdvancedTimer(QObject *parent) :
    QObject(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    _interval=timer.interval();
    tonext=_interval;
}

bool AdvancedTimer::isActive(){
    return timer.isActive();
}

void AdvancedTimer::start(){
    time=QTime::currentTime();
    timer.start();
}

void AdvancedTimer::stop(){
    timer.stop();
    tonext=_interval;
}

void AdvancedTimer::setInterval(int ms){
    _interval=ms;
    timer.setInterval(ms);
    tonext=_interval;
}

int AdvancedTimer::interval(){
    return _interval;
}

void AdvancedTimer::pause(){
    if(!timer.isActive())return;
    QTime now=QTime::currentTime();
    tonext=_interval-time.msecsTo(now);
    timer.stop();
}

void AdvancedTimer::resume(){
    if(timer.isActive())return;
    time=QTime::currentTime().addMSecs(tonext-_interval);
    timer.setInterval(tonext);
    timer.start();
}

void AdvancedTimer::onTimeout(){
    time=QTime::currentTime();
    if(timer.interval()!=_interval)timer.setInterval(_interval);
    emit timeout();
}
