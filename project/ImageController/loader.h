#ifndef LOADER_H
#define LOADER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QQueue>
#include <QVector>
#include <QString>
#include <QRegExp>
#include "World_of_Const.h"
#include "image.h"

class Loader
{
public:
    Loader();
    void addFile(QString path);
    void addFiles(QString dir,int number=-1,bool random=false);
    void addFiles(QStringList list,int number=-1,bool random=false);
    QStringList getAllFiles(QString dir);
    QVector<QStringList> getAllClassesFiles(QString dir);
    int size();
    Image take();
    Image* takepointer();
    QQueue<QString> getQueue();
    void Clear();
    void Save_Queue(QString name_of_file,int);
    int Load_Queue(QString name_of_file);
private:
    QQueue<QString> queue;
};

#endif // LOADER_H
