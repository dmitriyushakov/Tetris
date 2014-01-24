#include <QPainter>
#include <QPixmap>

#include "gamewidget.h"
#include "gameengine.h"
#include "field.h"
#include "figure.h"
#include "figurecassete.h"
#include "pallete.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent)
{
    engine=0;
    _cursorVisible=true;
    setCursorVisible(false);
    setMouseTracking(true);
    hideTimer.setSingleShot(true);
    connect(&hideTimer,SIGNAL(timeout()),this,SLOT(hideCursor()));
}

void GameWidget::setCursorVisible(bool visible){
    if(_cursorVisible==visible)return;
    _cursorVisible=visible;
    if(visible){
        setCursor(QCursor(Qt::ArrowCursor));
    }else{
        QPixmap pixmap(1,1);
        pixmap.fill(QColor(0,0,0,0));
        setCursor(QCursor(pixmap));
    }
}

void GameWidget::showCursor(){
    hideTimer.start(2000);
    setCursorVisible(true);
}

void GameWidget::hideCursor(){
    setCursorVisible(false);
}

void GameWidget::setEngine(GameEngine *engine){
    if(engine!=0){
        disconnect(engine,SIGNAL(stateUpdated()),this,SLOT(stateUpdated()));
    }
    this->engine=engine;
    connect(engine,SIGNAL(stateUpdated()),this,SLOT(stateUpdated()));
    update();
}

void GameWidget::unsetEngine(){
    if(engine!=0){
        disconnect(engine,SIGNAL(stateUpdated()),this,SLOT(stateUpdated()));
        this->engine=0;
        update();
    }
}

GameEngine *GameWidget::getEngine(){
    return engine;
}

void GameWidget::paintEvent(QPaintEvent *){
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing);

    p.fillRect(0,0,width(),height(),QColor(0,0,0));
    if(!engine->isRunned())return;

    float cellSize=(float)height()/engine->field()->height();
    float cellWidth=(float)width()/(engine->field()->width()+4);
    if(cellWidth<cellSize)cellSize=cellWidth;

    float fieldWidth=cellSize*engine->field()->width();
    float fieldHeight=cellSize*engine->field()->height();

    Field *field=engine->field();
    float dispShift=cellSize*(field->width()+1);
    float dispShiftY=height()/2-cellSize*2;
    float casseteSize=cellSize*4;

    float displayWidth=dispShift+casseteSize;
    float allShift=(width()-displayWidth)/2;
    p.translate(allShift,0);

    p.setPen(QColor(127,127,127));
    p.drawRect(0,0,fieldWidth,fieldHeight);

    Pallete *pallete=Pallete::getInstance();

    p.save();
    p.setPen(Qt::NoPen);

    for(int y=0;y<field->height();y++){
        for(int x=0;x<field->width();x++){
            CellType type=field->get(x,y);
            if(type!=NoneCell){
                QColor color=pallete->get(type);
                QRectF rect(cellSize*x+1,cellSize*y+1,cellSize-2,cellSize-2);
                p.setBrush(QBrush(color));
                p.drawRoundedRect(rect,cellSize*0.2,cellSize*0.2);
            }
        }
    }
    p.restore();

    p.drawRect(dispShift,dispShiftY,casseteSize,casseteSize);

    Figure *figure=engine->cassete()->preview();

    CellType fctype=figure->cellType();
    QColor color=pallete->get(fctype);

    p.save();
    p.setBrush(QBrush(color));
    p.setPen(Qt::NoPen);
    for(int y=0;y<figure->height();y++){
        for(int x=0;x<figure->width();x++){
            if(figure->get(x,y)){
                QRectF rect(dispShift+cellSize*x+1,dispShiftY+cellSize*y+1,cellSize-2,cellSize-2);
                p.drawRoundedRect(rect,cellSize*0.2,cellSize*0.2);
            }
        }
    }
    p.restore();

    int lblsPosY=dispShiftY+casseteSize+20;
    p.drawText(dispShift,lblsPosY,tr("Score: ").append(QString::number(engine->score())));

    p.setPen(QColor(255,255,255));
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    p.setFont(font);
    if(engine->isGameOver()){
        p.drawText(-allShift,0,width(),height(),Qt::AlignCenter,tr("Game Over"));
    }else if(engine->isPaused()){
        p.drawText(-allShift,0,width(),height(),Qt::AlignCenter,tr("Pause"));
    }
}

void GameWidget::mousePressEvent(QMouseEvent *){
    showCursor();
}

void GameWidget::mouseMoveEvent(QMouseEvent *){
    showCursor();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *){
    showCursor();
}

void GameWidget::stateUpdated(){
    update();
}
