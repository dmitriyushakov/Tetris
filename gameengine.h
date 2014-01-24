#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "keys.h"
#include "advancedtimer.h"
#include "gameproperties.h"

class Field;
class Figure;
class FigureCassete;

class GameEngine : public QObject
{
    Q_OBJECT
private:
    Field *_field;
    FigureCassete *_cassete;
    int _score;
    int interval;
    int startInterval;
    int filling;
    int figCount;
    int accelVar;
    bool gameDroped;
    bool complication;
    bool _shadowEnabled;
    AdvancedTimer timer;
    GameProperties startProperties;
    void addFigure();
    void togglePause();
    void setPaused(bool val);
    void fillField();
public:
    bool shadowEnabled();
    bool isGameOver();
    bool isRunned();
    bool isPaused();
    bool needToSaveRecord();
    void startGame(GameProperties &prop);
    void doDrop();
    int score();
    Field *field();
    FigureCassete *cassete();
    explicit GameEngine(QObject *parent = 0);
    ~GameEngine();
signals:
    void stateUpdated();
    void pauseTriggered(bool paused);
    void gameOver(int score,GameProperties prop);
private slots:
    void dropGame();
    void step();
    void clearedLines(int count);
public slots:
    void reset();
    void keyPressed(Keys key);
};

#endif // GAMEENGINE_H
