#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include "record.h"

class RecordTable
{
private:
    int capacity;
    int size;
    Record **records;
    void addCapacity();
public:
    void remove(int index);
    void remove(int index,int width,int height);
    int count();
    int count(int width,int height);
    Record* get(int index);
    Record* get(int index,int width,int height);
    void add(Record record);
    static RecordTable *load(QString filename);
    void save(QString filename);
    static QString getTablePath();
    RecordTable();
    ~RecordTable();
};

#endif // RECORDTABLE_H
