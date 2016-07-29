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
            //qDebug()<<r<<list.size();
            queue.enqueue(dir+"/"+list[r]);
            qDebug()<<"Load Time"<<dir+"/"+list[r];
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
            qDebug()<<"Load Time"<<dir+"/"+list[j];
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
            //qDebug()<<r<<list.size();
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
            //qDebug()<<"name"<<d.path()+"/"+name;
        }
        else
        {
            //qDebug()<<"dir"<<d.path()+"/"+name;
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

Image* Loader::takepointer()
{
    if(queue.size()==0)
    {
        qDebug()<<"Queue empty.";
        return new Image();
    }
    Image* im=new Image(queue.dequeue());
    im->resize(w_of_inputImage,h_of_inputImage);
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

void Loader::Save_Queue(QString name_of_file,int number)
{
    QFile file(pathLoader+ name_of_file);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<QString::number(number)<<"\n";
    for(int i=0;i<queue.size();i++)
    {
        if(!queue[i].isEmpty())
            out<<queue[i]<<"\n";
    }
    file.close();
    queue.clear();
}

int Loader::Load_Queue(QString name_of_file)
{
    QFile file(pathLoader+name_of_file);
    if(!file.exists())
        return 0;
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString text;
    bool isOk=false;
    int number;
    if(!file.atEnd())
    {
        text=file.readLine();
        number=text.toInt();
    }
    while(!file.atEnd())
    {
        text=file.readLine();
        if(!text.isEmpty()||text.contains(QRegExp(" ")))
        {
            queue.enqueue(text);
        }
    }
    file.close();
    file.remove();
    return number;
}


