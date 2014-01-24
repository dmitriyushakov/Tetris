#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{
private:
    QString _player;
    int _score;
    int _width;
    int _height;
public:
    QString& player();
    int score();
    int width();
    int height();
    Record(Record& other);
    Record(QString player,int score,int width,int height);
};

#endif // RECORD_H
