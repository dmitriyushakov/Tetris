#include "figureprototype.h"

FigurePrototype::FigurePrototype()
{
    vals=0;
    _width=0;
    _height=0;
}

FigurePrototype::FigurePrototype(FigureType type){
    _type=type;
    switch(type){

    case FigI:
        initMatrix(1,4);
        for(int i=0;i<4;i++)vals[i]=true;
        break;

    case FigJ:
        initMatrix(2,3);
        for(int i=0;i<3;i++)set(1,i);
        set(0,2);
        break;

    case FigL:
        initMatrix(2,3);
        for(int i=0;i<3;i++)set(0,i);
        set(1,2);
        break;

    case FigO:
        initMatrix(2,2);
        for(int i=0;i<4;i++)vals[i]=true;
        break;

    case FigS:
        initMatrix(3,2);
        set(0,1);
        set(1,1);
        set(1,0);
        set(2,0);
        break;

    case FigT:
        initMatrix(3,2);
        for(int i=0;i<3;i++)set(i,0);
        set(1,1);
        break;

    case FigZ:
        initMatrix(3,2);
        set(0,0);
        set(1,0);
        set(1,1);
        set(2,1);
        break;

    default:
        _width=0;
        _height=0;
        vals=0;
        break;
    }
}

void FigurePrototype::initMatrix(int w, int h){
    int size=w*h;
    vals=new bool[size];
    for(int i=0;i<size;i++)vals[i]=false;
    _width=w;
    _height=h;
}

void FigurePrototype::set(int x, int y, bool val){
    vals[getAddres(x,y)]=val;
}

bool FigurePrototype::get(int x,int y){
    return vals[getAddres(x,y)];
}

bool FigurePrototype::isNull(){
    return this==0||vals==0;
}

int FigurePrototype::width(){
    return _width;
}

int FigurePrototype::height(){
    return _height;
}

FigureType FigurePrototype::type(){
    return _type;
}

FigurePrototype::~FigurePrototype(){
    delete vals;
}
