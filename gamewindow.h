#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMenuBar>

#include "gameproperties.h"
#include "record.h"

class GameWidget;
class KeyPad;
class GameProperties;
class RecordTable;

class GameWindow:public QWidget
{
    Q_OBJECT
private:
    QMenuBar *mainmenu;
    GameWidget *widget;
    KeyPad *keypad;
    QAction *resetAct;
    QAction *pauseAct;
    RecordTable *records;
    bool askedToClose;
    void buildMenu();
    void gameStarted();
public:
    GameWindow(GameWidget* wgt);
    ~GameWindow();
    void setKeypad(KeyPad *keypad);
    void unsetKeypad();
protected:
    void closeEvent(QCloseEvent *ev);
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
signals:
    void dropGame();
public slots:
    void gameOver(int score,GameProperties prop);
private slots:
    void acceptRecord(Record record);
    void pauseTriggered(bool paused);
    void startGame5_10();
    void startGame10_20();
    void startGame15_30();
    void startGame20_40();
    void startCustomGame();
    void startGame(GameProperties& prop);
    void onPause();
    void onAbout();
    void showRecords();
};

#endif // GAMEWINDOW_H
