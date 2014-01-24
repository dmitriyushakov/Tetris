#ifndef FIGUREPROTOTYPE_H
#define FIGUREPROTOTYPE_H

#include "figuretype.h"

#include <QColor>

class FigurePrototype
{
private:
    bool *vals;
    int _width;
    int _height;
    void initMatrix(int w,int h);
    inline int getAddres(int x,int y){
        return y*_width+x;
    }
    FigureType _type;
    //QColor color;
    void set(int x,int y,bool val=true);
public:
    bool get(int x,int y);
    bool isNull();
    int width();
    int height();
    FigureType type();
    FigurePrototype();
    FigurePrototype(FigureType type);
    ~FigurePrototype();
};

#endif // FIGUREPROTOTYPE_H
