#include "gameproperties.h"

const int GameProperties::stdWidth=10;
const int GameProperties::stdHeight=20;
const int GameProperties::stdInterval=1000;
const int GameProperties::stdFilling=0;
const int GameProperties::stdAccelvar=150;
const bool GameProperties::stdComplication=true;

GameProperties::GameProperties()
{
    _width=stdWidth;
    _height=stdHeight;
    _interval=stdHeight;
    _filling=stdFilling;
    _accelvar=stdAccelvar;
    _complication=stdComplication;
}

GameProperties::GameProperties(int width, int height){
    _width=width;
    _height=height;
    _interval=stdInterval;
    _filling=stdFilling;
    _accelvar=stdAccelvar;
    _complication=stdComplication;
}

bool GameProperties::isStandart(){
    if(     _interval!=stdInterval ||
            _filling!=stdFilling ||
            _accelvar!=stdAccelvar ||
            _complication!=stdComplication)return false;
    if(_width==5&&_height==10)return true;
    if(_width==10&&_height==20)return true;
    if(_width==15&&_height==30)return true;
    if(_width==20&&_height==40)return true;
    return false;
}

int GameProperties::width(){
    return _width;
}

int GameProperties::height(){
    return _height;
}

int GameProperties::interval(){
    return _interval;
}

int GameProperties::filling(){
    return _filling;
}

bool GameProperties::complication(){
    return _complication;
}

int GameProperties::accelirationVar(){
    return _accelvar;
}

void GameProperties::setWidth(int width){
    _width=width;
}

void GameProperties::setHeignt(int height){
    _height=height;
}

void GameProperties::setSize(int width, int height){
    _width=width;
    _height=height;
}

void GameProperties::setInterval(int interval){
    _interval=interval;
}

void GameProperties::setFilling(int filling){
    _filling=filling;
}

void GameProperties::setComplication(bool complication){
    _complication=complication;
}

void GameProperties::setAccelerationVar(int val){
    _accelvar=val;
}
