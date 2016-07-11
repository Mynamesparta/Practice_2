#include "loader.h"

Loader::Loader()
{
}

void Loader::add(QString dir,QString name)
{
    queue.enqueue(dir+name);
}

void Loader::add(QString dir, int number, bool random)
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
    qDebug()<<"take oks";
    Image im(queue.dequeue());
    qDebug()<<"start resize";
    im.resize(w_of_inputImage,h_of_inputImage);
    qDebug()<<"mid red"<<im.red.mid();
    qDebug()<<"mid green"<<im.green.mid();
    qDebug()<<"mid blue"<<im.blue.mid();
    static int index=0;

    im.save(pathTestImage+QString::number(index++)+".jpg");

    return im;
}
