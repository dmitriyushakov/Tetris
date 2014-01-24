#include "record.h"

Record::Record(Record &other){
    _player=other._player;
    _score=other._score;
    _width=other._width;
    _height=other._height;
}

Record::Record(QString player,int score,int width,int height){
    _player=player;
    _score=score;
    _width=width;
    _height=height;
}

QString& Record::player(){
    return _player;
}

int Record::score(){
    return _score;
}

int Record::width(){
    return _width;
}

int Record::height(){
    return _height;
}
