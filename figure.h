#ifndef FIGURE_H
#define FIGURE_H

#include "figureprototype.h"
#include "rotations.h"
#include "celltype.h"

class Figure
{
private:
    FigurePrototype* prototype;
    Rotations rotation;
    int xpos;
    int ypos;
public:
    void rotateToLeft();
    void rotateToRight();
    void moveToLeft();
    void moveToRight();
    void moveToDown();
    void moveToUp();
    void setX(int x);
    int width();
    int height();
    int x();
    int y();
    CellType cellType();
    bool get(int x,int y);
    Figure(FigurePrototype *proto,Rotations rotation);
};

#endif // FIGURE_H
