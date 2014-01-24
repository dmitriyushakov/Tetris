#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>

class GameEngine;

class GameWidget : public QWidget
{
    Q_OBJECT
private:
    GameEngine *engine;
    QTimer hideTimer;
    bool _cursorVisible;
    void setCursorVisible(bool visible);
    void showCursor();
public:
    explicit GameWidget(QWidget *parent = 0);
    void setEngine(GameEngine *engine);
    void unsetEngine();
    GameEngine *getEngine();
protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void hideCursor();
    void stateUpdated();
};

#endif // GAMEWIDGET_H
