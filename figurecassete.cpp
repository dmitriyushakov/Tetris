#include "figurecassete.h"
#include "figure.h"

FigureCassete::FigureCassete()
{
    prototypes=(FigurePrototype**)malloc(sizeof(FigurePrototype*)*7);

    prototypes[0]=new FigurePrototype(FigI);
    prototypes[1]=new FigurePrototype(FigJ);
    prototypes[2]=new FigurePrototype(FigL);
    prototypes[3]=new FigurePrototype(FigO);
    prototypes[4]=new FigurePrototype(FigS);
    prototypes[5]=new FigurePrototype(FigT);
    prototypes[6]=new FigurePrototype(FigZ);

    figure=makeFigure();
}

Figure* FigureCassete::makeFigure(){
    Rotations rotation;
    switch(rand()%4){
        case 0:rotation=Rot0;break;
        case 1:rotation=Rot90;break;
        case 2:rotation=Rot180;break;
        case 3:rotation=Rot270;break;
    }

    return new Figure(prototypes[rand()%7],rotation);
}

Figure* FigureCassete::preview(){
    return figure;
}

Figure* FigureCassete::pop(){
    Figure *prev=figure;
    figure=makeFigure();
    return prev;
}

void FigureCassete::reset(){
    delete figure;
    figure=makeFigure();
}

FigureCassete::~FigureCassete(){
    for(int i=0;i<7;i++){
        delete prototypes[i];
    }
    free(prototypes);
}
