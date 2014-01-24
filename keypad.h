#ifndef KEYPAD_H
#define KEYPAD_H

#include <QObject>

#include "keys.h"

class QKeyEvent;

class KeyPad : public QObject
{
    Q_OBJECT
private:
    Keys getKey(QKeyEvent *event);
    bool pausePressed;
public:
    explicit KeyPad(QObject *parent = 0);
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    void keyPress(Keys key);
    void keyRelease(Keys key);
signals:
    void keyPressed(Keys key);
    void keyReleased(Keys key);
};

#endif // KEYPAD_H
