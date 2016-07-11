#ifndef LOADER_H
#define LOADER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QQueue>
#include <QString>
#include "World_of_Const.h"
#include "image.h"

class Loader
{
public:
    Loader();
    void add(QString dir,QString name);
    void add(QString dir,int number=-1,bool random=false);
    int size();
    Image take();
private:
    QQueue<QString> queue;
};

#endif // LOADER_H
