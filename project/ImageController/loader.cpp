#include "loader.h"

Loader::Loader()
{
}

void Loader::addFile(QString path)
{
    queue.enqueue(path);
}

void Loader::addFiles(QString dir, int number, bool random)
{
    QDir d(dir);
    QStringList filters;
    filters<<"[a-z,A-Z,0-9]*.jpg";
    d.setNameFilters(filters);


    QStringList list=d.entryList();
    qDebug()<<"size of list="<<list.size();
    int r;
    int i=0;

    if(random)
    {
        while(list.size()>0)
        {
            r=randInt(0,list.size()-1);
            qDebug()<<r<<list.size();
            queue.enqueue(dir+"/"+list[r]);
            list.removeAt(r);
            if(number!=-1)
            {
                i++;
                if(i==number)
                    break;
            }
        }
    }
    else
    {
        for(int j=0;j<list.size();j++)
        {
            queue.enqueue(dir+"/"+list[j]);
            if(number>=1)
            {
                i++;
                if(i==number)
                    break;
            }
        }
    }

}

void Loader::addFiles(QStringList list, int number, bool random)
{
    int r,i=0;
    if(random)
    {
        while(list.size()>0)
        {
            r=randInt(0,list.size()-1);
            qDebug()<<r<<list.size();
            queue.enqueue(list[r]);
            list.removeAt(r);
            if(number!=-1)
            {
                i++;
                if(i==number)
                    break;
            }
        }
    }
    else
    {
        for(int j=0;j<list.size();j++)
        {
            queue.enqueue(list[j]);
            if(number>=1)
            {
                i++;
                if(i==number)
                    break;
            }
        }
    }
    qDebug()<<queue;
}

QStringList Loader::getAllFiles(QString dir)
{
    QDir d(dir);
    QStringList res;
    QStringList files=d.entryList();
    static const QRegExp qre("\\.");
    static const QRegExp qre2("^\\.+$");


    foreach(QString name,files)
    {
        if(name.contains(qre2))
            continue;
        if(name.contains(qre))
        {
            res<<d.path()+"/"+name;
            qDebug()<<"name"<<d.path()+"/"+name;
        }
        else
        {
            qDebug()<<"dir"<<d.path()+"/"+name;
            res<<getAllFiles(d.path()+"/"+name);
        }
    }
    return res;

}

QVector<QStringList> Loader::getAllClassesFiles(QString dir)
{
    QDir d(dir);
    QVector<QStringList> res;
    QStringList filter;
    filter<<"[a-z,A-Z,0-9]*";
    d.setNameFilters(filter);
    QStringList files=d.entryList();
    res.resize(files.size());
    for(int i=0;i<files.size();i++)
    {
        res[i]<<getAllFiles(d.path()+"/"+files[i]);
    }

    return res;
}

int Loader::size()
{
    return queue.size();
}

Image Loader::take()
{
    if(queue.size()==0)
    {
        qDebug()<<"Queue empty.";
        return Image();
    }
    Image im(queue.dequeue());
    im.resize(w_of_inputImage,h_of_inputImage);
    static int index=0;

    //im.save(pathTestImage+QString::number(index++)+".jpg");

    return im;
}

QQueue<QString> Loader::getQueue()
{
    return queue;
}

void Loader::Clear()
{
    queue.clear();
}
