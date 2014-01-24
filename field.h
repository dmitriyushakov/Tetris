#ifndef FIELD_H
#define FIELD_H

#include "celltype.h"
#include <QObject>

class Figure;

class Field:public QObject
{
    Q_OBJECT
private:
    int _width;
    int _height;
    bool overflow;
    CellType *field;
    Figure *_figure;
    inline int getAddres(int x,int y){
        return y*_width+x;
    }
    bool inBounds(int x,int y);
    bool inFigureBounds(int x,int y);
    bool getExist(int x,int y);
    void dropFigure();
    bool isIntersect();
    void cleanLines();
public:
    bool isOverflow();
    CellType getReal(int x,int y);
    CellType get(int x,int y);
    void set(int x,int y,CellType type);

    // Move actions
    bool toLeft();
    bool toRight();
    bool toDown();
    bool rotateToLeft();
    bool rotateToRight();

    void pushFigure(Figure *fig);
    int width();
    int height();
    Figure *figure();
    bool hasFigure();
    void clean();
    Field(int width,int height);
    ~Field();
signals:
    void cleared(int count);
};

#endif // FIELD_H
