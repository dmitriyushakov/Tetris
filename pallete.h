#ifndef PALLETE_H
#define PALLETE_H

#include <QMap>
#include <QColor>

#include "celltype.h"

class Pallete
{
private:
    QMap<CellType,QColor> map;
    static Pallete *pallete;
    Pallete();
public:
    static Pallete *getInstance();
    static void removeInstance();
    QColor get(CellType type);
};

#endif // PALLETE_H
