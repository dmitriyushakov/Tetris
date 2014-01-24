#include <QKeyEvent>

#include "keypad.h"

KeyPad::KeyPad(QObject *parent) :
    QObject(parent)
{
    pausePressed=false;
}

Keys KeyPad::getKey(QKeyEvent *event){
    int key=event->key();
    switch(key){
        case Qt::Key_Up:return KeyUp;
        case Qt::Key_Left:return KeyLeft;
        case Qt::Key_Down:return KeyDown;
        case Qt::Key_Right:return KeyRight;
        case Qt::Key_Enter:return KeyDrop;
        case Qt::Key_Return:return KeyDrop;
        case Qt::Key_Space:return KeyPause;
    }
    return KeyNone;
}

void KeyPad::keyPress(QKeyEvent *event){
    Keys key=getKey(event);
    if(key==KeyDrop&&event->isAutoRepeat())return;
    emit keyPressed(key);
}

void KeyPad::keyRelease(QKeyEvent *event){
    Keys key=getKey(event);
    if(key==KeyDrop&&event->isAutoRepeat())return;
    if(key==KeyPause&&!event->isAutoRepeat())pausePressed=false;
    else return;
    emit keyReleased(key);
}

void KeyPad::keyPress(Keys key){
    if(key==KeyPause&&!pausePressed){
        pausePressed=true;
    }else if(key==KeyPause){
        return;
    }
    emit keyPressed(key);
}

void KeyPad::keyRelease(Keys key){
    emit keyReleased(key);
}
