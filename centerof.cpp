#include <QWidget>
#include "centerof.h"

void centerOf(QWidget *wgt1, QWidget *wgt2){
    int xpos=(wgt1->width()-wgt2->width())/2+wgt1->x();
    int ypos=(wgt1->height()-wgt2->height())/2+wgt1->y();
    wgt2->move(xpos,ypos);
}
