#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QByteArray>
#include <QDir>

#include "recordtable.h"

RecordTable::RecordTable()
{
    size=0;
    capacity=10;
    records=(Record**)malloc(sizeof(Record*)*capacity);
}

void RecordTable::addCapacity(){
    capacity*=2;
    records=(Record**)realloc(records,capacity);
}

void RecordTable::remove(int index){
    if(index>=size||index<0)return;
    delete records[index];
    for(int i=index;i<size;i++)records[i]=records[i+1];
    size--;
}

void RecordTable::remove(int index, int width, int height){
    int cindex=0;
    for(int i=0;i<size;i++){
        Record *rec=records[i];
        if(rec->width()==width&&rec->height()==height){
            cindex++;
            if(cindex==index){
                delete records[i];
                for(int j=i;j<size;j++)records[j]=records[j+1];
                size--;
                return;
            }
        }
    }
}

int RecordTable::count(){
    return size;
}

int RecordTable::count(int width, int height){
    int count=0;
    for(int i=0;i<size;i++){
        Record *rec=records[i];
        if(rec->width()==width&&rec->height()==height)count++;
    }
    return count;
}

Record* RecordTable::get(int index){
    if(index>=size||index<0)return NULL;
    return records[index];
}

Record* RecordTable::get(int index, int width, int height){
    int cindex=0;
    for(int i=0;i<size;i++){
        Record *rec=records[i];
        if(rec->width()==width&&rec->height()==height){
            if(cindex==index)return records[i];
            cindex++;
        }
    };
    return NULL;
}

void RecordTable::add(Record record){
    int width=record.width();
    int height=record.height();
    int count=this->count(width,height);
    if(size>=capacity)addCapacity();
    if(count<10)records[size++]=new Record(record);
    else{
        while(count>=10){
            int smallest=get(0,width,height)->score();
            int pos=0;
            for(int i=1;i<count;i++){
                Record *other=get(i,width,height);
                if(other->score()<smallest){
                    smallest=other->score();
                    pos=i;
                }
            }
            if(record.score()<smallest)return;
            else{
                remove(pos,width,height);
                count--;
            }
        }
        records[size++]=new Record(record);
    }
}

RecordTable* RecordTable::load(QString filename){
    RecordTable *table=new RecordTable();

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))return table;
    QByteArray arr=file.readAll();
    file.close();

    QJsonDocument doc=QJsonDocument::fromJson(arr);
    if(!doc.isArray())return table;

    QJsonArray jsarr=doc.array();
    int count=jsarr.count();
    for(int i=0;i<count;i++){
        QJsonValue val=jsarr[i];
        if(!val.isObject())continue;

        QJsonObject object=val.toObject();
        if(     !object.contains("player")||
                !object.contains("score")||
                !object.contains("width")||
                !object.contains("height"))continue;
        QString player=object.value("player").toString();
        int score=object.value("score").toDouble();
        int width=object.value("width").toDouble();
        int height=object.value("height").toDouble();

        table->records[table->size++]=new Record(player,score,width,height);
    }
    return table;
}

void RecordTable::save(QString filename){
    QJsonArray arr;
    for(int i=0;i<size;i++){
        QJsonObject object;
        Record *record=records[i];
        object.insert("player",record->player());
        object.insert("score",record->score());
        object.insert("width",record->width());
        object.insert("height",record->height());
        arr.append(QJsonValue(object));
    }

    QJsonDocument doc(arr);
    QByteArray bytearr=doc.toJson();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate));
    file.write(bytearr);
    file.close();
}

QString RecordTable::getTablePath(){
    return QDir::homePath().append("/.tetris_records.json");
}

RecordTable::~RecordTable(){
    for(int i=0;i<size;i++)delete records[i];
    records;
}
