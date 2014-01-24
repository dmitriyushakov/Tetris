#ifndef FIGURECASSETE_H
#define FIGURECASSETE_H

class Figure;
class FigurePrototype;

class FigureCassete
{
private:
    Figure *figure;
    FigurePrototype **prototypes;
    Figure *makeFigure();
public:
    Figure *preview();
    Figure *pop();
    void reset();
    FigureCassete();
    ~FigureCassete();
};

#endif // FIGURECASSETE_H
