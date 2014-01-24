#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include "gamewidget.h"
#include "gameengine.h"
#include "keypad.h"
#include "gamewindow.h"

#include "stdlib.h"
#include "time.h"

int main(int argc,char **argv){
    QApplication app(argc,argv);

    if(QLocale::system().language()==QLocale::Russian){
        QTranslator *tr=new QTranslator();
        tr->load(":/tetris_ru.qm");
        app.installTranslator(tr);
    }

    srand(clock());

    KeyPad *keypad=new KeyPad();

    GameEngine *engine=new GameEngine();
    QObject::connect(keypad,SIGNAL(keyPressed(Keys)),engine,SLOT(keyPressed(Keys)));

    GameWidget *widget=new GameWidget();
    widget->setEngine(engine);

    GameWindow *window=new GameWindow(widget);
    window->showMaximized();
    window->setKeypad(keypad);
    QObject::connect(engine,SIGNAL(gameOver(int,GameProperties)),window,SLOT(gameOver(int,GameProperties)));
    QObject::connect(window,SIGNAL(dropGame()),engine,SLOT(dropGame()));

    int result=app.exec();

    delete keypad;
    delete engine;
    delete widget;
    delete window;

    return result;
}
