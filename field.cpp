#include "field.h"
#include "figure.h"

bool Field::inBounds(int x, int y){
    return x>=0 && y>=0 && y<_height && x<_width;
}

bool Field::inFigureBounds(int x,int y){
    if(_figure==0)return false;

    x-=_figure->x();
    y-=_figure->y();
    int width=_figure->width();
    int height=_figure->height();

    return x>=0 && y>=0 && y<height && x<width;
}

bool Field::getExist(int x, int y){
    if(!inBounds(x,y))return false;
    return field[getAddres(x,y)]!=NoneCell;
}

void Field::dropFigure(){
    if(_figure!=0){
        int xpos=_figure->x();
        int ypos=_figure->y();
        int fwidth=_figure->width();
        int fheight=_figure->height();
        CellType type=_figure->cellType();

        for(int y=0;y<fheight;y++){
            for(int x=0;x<fwidth;x++){
                if(_figure->get(x,y))set(x+xpos,y+ypos,type);
            }
        }
        delete _figure;
        _figure=0;

        if(ypos<=0)overflow=true;
        if(overflow)return;

        cleanLines();
    }
}

bool Field::isIntersect(){
    int xpos=_figure->x();
    int ypos=_figure->y();
    int width=_figure->width();
    int height=_figure->height();
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            if(getExist(xpos+x,ypos+y)&&_figure->get(x,y))return true;
        }
    }
    return false;
}

void Field::cleanLines(){
    int clearedCount=0;
    for(int y=_height-1;y>=0;y--){
        bool fully=true;
        for(int x=0;x<_width;x++){
            if(getReal(x,y)==NoneCell){
                fully=false;
                break;
            }
        }
        if(fully){
            for(int cy=y-1;cy>=0;cy--){
                for(int x=0;x<_width;x++){
                    set(x,cy+1,getReal(x,cy));
                }
            }
            for(int x=0;x<_width;x++){
                set(x,0,NoneCell);
            }
            y++;
            clearedCount++;
        }
    }
    emit cleared(clearedCount);
}

bool Field::isOverflow(){
    return overflow;
}

CellType Field::getReal(int x, int y){
    if(!inBounds(x,y))return NoneCell;
    return field[getAddres(x,y)];
}

CellType Field::get(int x, int y){
    if(!inBounds(x,y))return NoneCell;
    if(inFigureBounds(x,y)){
        int fx=x-_figure->x();
        int fy=y-_figure->y();
        if(_figure->get(fx,fy)){
            return _figure->cellType();
        }
    }
    return field[getAddres(x,y)];
}

void Field::set(int x, int y, CellType type){
    if(!inBounds(x,y))return;
    field[getAddres(x,y)]=type;
}

bool Field::toLeft(){
    if(_figure==0)return false;
    _figure->moveToLeft();
    if(     _figure->x()<0||
            isIntersect()){
        _figure->moveToRight();
        return false;
    }
    return true;
}

bool Field::toRight(){
    if(_figure==0)return false;
    _figure->moveToRight();
    if(     _figure->x()+_figure->width()>_width||
            isIntersect()){
        _figure->moveToLeft();
        return false;
    }
    return true;
}

bool Field::toDown(){
    if(_figure==0)return false;
    _figure->moveToDown();
    if(_figure->y()+_figure->height()>_height||
            isIntersect()){
        _figure->moveToUp();
        dropFigure();
        return false;
    }
    return true;
}

bool Field::rotateToLeft(){
    if(_figure==0)return false;
    _figure->rotateToLeft();
    if(     _figure->x()<0||
            _figure->x()+_figure->width()>_width||
            isIntersect()){
        _figure->rotateToRight();
        return false;
    }
    return true;
}

bool Field::rotateToRight(){
    if(_figure==0)return false;
    _figure->rotateToRight();
    if(     _figure->x()<0||
            _figure->x()+_figure->width()>_width||
            isIntersect()){
        _figure->rotateToLeft();
        return false;
    }
    return true;
}

void Field::pushFigure(Figure *fig){
    delete _figure;
    _figure=fig;
}

int Field::width(){
    return _width;
}

int Field::height(){
    return _height;
}

Figure* Field::figure(){
    return _figure;
}

bool Field::hasFigure(){
    return _figure!=0;
}

void Field::clean(){
    delete _figure;
    _figure=0;
    int size=_width*_height;
    for(int i=0;i<size;i++)field[i]=NoneCell;
    overflow=false;
}

Field::Field(int width, int height):QObject(){
    _width=width;
    _height=height;
    int size=width*height;
    field=new CellType[size];
    for(int i=0;i<size;i++)field[i]=NoneCell;
    _figure=0;
    overflow=false;
}

Field::~Field(){
    delete _figure;
    delete field;
}
