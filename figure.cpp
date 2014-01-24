#include "figure.h"

void Figure::rotateToLeft(){
    switch(rotation){
        case Rot0:rotation=Rot270;break;
        case Rot270:rotation=Rot180;break;
        case Rot180:rotation=Rot90;break;
        case Rot90:rotation=Rot0;break;
    }
}

void Figure::rotateToRight(){
    switch(rotation){
        case Rot0:rotation=Rot90;break;
        case Rot90:rotation=Rot180;break;
        case Rot180:rotation=Rot270;break;
        case Rot270:rotation=Rot0;break;
    }
}

void Figure::moveToLeft(){
    xpos--;
}

void Figure::moveToRight(){
    xpos++;
}

void Figure::moveToDown(){
    ypos++;
}

void Figure::moveToUp(){
    ypos--;
}

void Figure::setX(int x){
    xpos=x;
}

int Figure::width(){
    if(rotation==Rot0||rotation==Rot180){
        return prototype->width();
    }else{
        return prototype->height();
    }
}

int Figure::height(){
    if(rotation==Rot0||rotation==Rot180){
        return prototype->height();
    }else{
        return prototype->width();
    }
}

int Figure::x(){
    return xpos;
}

int Figure::y(){
    return ypos;
}

CellType Figure::cellType(){
    return (CellType)prototype->type();
}

bool Figure::get(int x, int y){
    int ax,ay;
    switch(rotation){

    case Rot0:
        ax=x;
        ay=y;
        break;

    case Rot90:
        ax=prototype->width()-1-y;
        ay=x;
        break;

    case Rot180:
        ax=prototype->width()-1-x;
        ay=prototype->height()-1-y;
        break;

    case Rot270:
        ax=y;
        ay=prototype->height()-1-x;
        break;

    default:
        return false;
    }
    if( ax>=0 && ax<prototype->width() && ay>=0 && ay<prototype->height() ){
        return prototype->get(ax,ay);
    }else return false;
}

Figure::Figure(FigurePrototype *proto, Rotations rotation){
    this->rotation=rotation;
    prototype=proto;
    xpos=0;
    ypos=-height();
}
