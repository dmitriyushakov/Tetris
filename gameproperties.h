#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H

class GameProperties
{
private:
    int _width;
    int _height;
    int _interval;
    int _filling;
    bool _complication;
    int _accelvar;
    bool _shadowEnabled;
    static const int stdWidth;
    static const int stdHeight;
    static const int stdInterval;
    static const int stdFilling;
    static const bool stdComplication;
    static const int stdAccelvar;
    static const bool stdShadowEnabled;
public:
    bool isStandart();
    int width();
    int height();
    int interval();
    int filling();
    int accelirationVar();
    bool complication();
    bool shadowEnabled();
    void setWidth(int width);
    void setHeignt(int height);
    void setSize(int width,int height);
    void setInterval(int interval);
    void setFilling(int filling);
    void setComplication(bool complication);
    void setShadowEnabled(bool enabled);
    void setAccelerationVar(int val);
    GameProperties();
    GameProperties(int width,int height);
};

#endif // GAMEPROPERTIES_H
