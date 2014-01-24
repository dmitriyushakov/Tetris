#include "field.h"
#include "figure.h"
#include "figurecassete.h"
#include "gameengine.h"
#include "gameproperties.h"

GameEngine::GameEngine(QObject *parent) :
    QObject(parent)
{
    _score=0;
    _field=0;
    _cassete=0;
    interval=0;
    filling=0;
    startInterval=0;
    figCount=0;
    accelVar=0;
    gameDroped=false;
    complication=true;
    connect(&timer,SIGNAL(timeout()),this,SLOT(step()));
}

bool GameEngine::isRunned(){
    return _field!=0;
}

bool GameEngine::isPaused(){
    return (!timer.isActive())&&_field!=0;
}

bool GameEngine::needToSaveRecord(){
    return (!gameDroped)&&_field!=0;
}

void GameEngine::setPaused(bool val){
    if(val)timer.pause();
    else timer.resume();
    emit stateUpdated();
    emit pauseTriggered(val);
}

void GameEngine::addFigure(){
    Figure *figure=_cassete->pop();
    figure->setX(rand()%(_field->width()-figure->width()));
    _field->pushFigure(figure);
}

void GameEngine::togglePause(){
    if(timer.isActive()){
        timer.pause();
        emit pauseTriggered(true);
    }else{
        timer.resume();
        emit pauseTriggered(false);
    }
}

void GameEngine::fillField(){
    int height=_field->height();
    int width=_field->width();
    for(int y=height-1;y>height-1-filling;y--){
        int emptyPos=rand()%width;
        for(int x=0;x<width;x++){
            if(x!=emptyPos){
                CellType type=(CellType)(rand()%(ZCell+1));//So, lazy...
                if(rand()%4==0)type=NoneCell;
                _field->set(x,y,type);
            }else{
                _field->set(x,y,NoneCell);
            }
        }
    }
}

bool GameEngine::isGameOver(){
    return _field->isOverflow();
}

void GameEngine::startGame(GameProperties &prop){
    gameDroped=false;
    startProperties=prop;

    if(_field)delete _field;
    _field=new Field(prop.width(),prop.height());

    filling=prop.filling();
    figCount=0;
    fillField();
    int width=prop.width();

    int ymin=prop.height()-1-filling;
    for(int y=prop.height()-1;y>ymin;y--){
        int emptyPos=rand()%width;
        for(int x=0;x<width;x++){
            if(x!=emptyPos){
                CellType type=(CellType)(rand()%(ZCell+1));//So, lazy...
                if(rand()%4==0)type=NoneCell;
                _field->set(x,y,type);
            }else{
                _field->set(x,y,NoneCell);
            }
        }
    }

    accelVar=prop.accelirationVar();
    _score=0;
    complication=prop.complication();
    connect(_field,SIGNAL(cleared(int)),this,SLOT(clearedLines(int)));
    if(_cassete==0)_cassete=new FigureCassete();
    addFigure();

    interval=prop.interval();
    startInterval=interval;
    timer.setInterval(interval);
    timer.start();

    emit stateUpdated();
}

void GameEngine::doDrop(){
    int targetInterval=interval/10;
    if(timer.interval()!=targetInterval)
        timer.setInterval(targetInterval);
}

int GameEngine::score(){
    return _score;
}

Field *GameEngine::field(){
    return _field;
}

FigureCassete *GameEngine::cassete(){
    return _cassete;
}

void GameEngine::step(){
    if(!_field->toDown()){
        addFigure();
    }
    if(_field->isOverflow()){
        timer.stop();
        dropGame();
    }
    emit stateUpdated();
}

void GameEngine::clearedLines(int count){
    if(count!=0){
        int addScore=1;
        for(int i=1;i<=count;i++)addScore*=i;
        _score+=addScore;
    }
    if(complication){
        figCount++;
        interval=(startInterval*accelVar)/(accelVar+figCount);
    }
    timer.setInterval(interval);
}

void GameEngine::dropGame(){
    if(!gameDroped){
        gameDroped=true;
        emit gameOver(_score,startProperties);
    }
}

void GameEngine::reset(){
    _field->clean();
    fillField();
    setPaused(false);
    _cassete->reset();
    _field->pushFigure(_cassete->pop());
    _score=0;
    gameDroped=false;
    figCount=0;
    interval=startInterval;
    timer.setInterval(interval);
    emit stateUpdated();
}

void GameEngine::keyPressed(Keys key){
    if(!_field||_field->isOverflow())return;
    if(key==KeyPause){
        togglePause();
        emit stateUpdated();
    }
    if(!timer.isActive())return;
    switch(key){
        case KeyUp:_field->rotateToLeft();break;
        case KeyDown:_field->rotateToRight();break;
        case KeyLeft:_field->toLeft();break;
        case KeyRight:_field->toRight();break;
        case KeyDrop:doDrop();break;
    }
    emit stateUpdated();
    if(_field->figure()==0)addFigure();
}

GameEngine::~GameEngine(){
    delete _field;
    delete _cassete;
}
