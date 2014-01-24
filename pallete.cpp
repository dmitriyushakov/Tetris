#include "pallete.h"

Pallete* Pallete::pallete=0;

Pallete::Pallete()
{
    map.insert(ICell,QColor(51,153,255));
    map.insert(JCell,QColor(51,0,255));
    map.insert(LCell,QColor(255,153,0));
    map.insert(OCell,QColor(255,255,51));
    map.insert(SCell,QColor(0,204,0));
    map.insert(TCell,QColor(204,51,204));
    map.insert(ZCell,QColor(255,0,0));
    map.insert(ShadowCell,QColor(50,50,50));
    map.insert(NoneCell,QColor(0,0,0,0));
}

Pallete* Pallete::getInstance(){
    if(pallete==0){
        pallete=new Pallete();
    }
    return pallete;
}

void Pallete::removeInstance(){
    delete pallete;
    pallete=0;
}

QColor Pallete::get(CellType type){
    return map.value(type);
}
