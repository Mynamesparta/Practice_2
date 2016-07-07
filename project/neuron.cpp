#include "neuron.h"

Neuron::Neuron(QString dir,QString name,int w,int h):dir(dir),name(name.replace(".txt","")),weight(_w,_h),_w(w),_h(h)
{
    qDebug()<<name.replace(".txt","");
    QFile file(dir+name+".txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString line;
    QStringList stringlist;
    int i=0;
    do
    {
        line=in.readLine();
        if(line=="")
            continue;
        stringlist=line.split(" ");
        for(int j=0;j<stringlist.size();j++)
        {
            if(j==_w)
                break;
            if(stringlist[j]!="")
            {
                weight[i][j]=stringlist[j].toInt();
            }
        }
        i++;
        if(i==_h)
            break;

    }
    while(!line.isNull());

    QString text;
    for(int i=0;i<_h;i++)
    {
        text="";
        for(int j=0;j<_w;j++)
            text+=QString::number(weight[i][j])+" ";
        //qDebug()<<text;
    }
    file.close();
    qDebug()<<"---------------------------------";
    Save();

}

void Neuron::Save()
{
    QFile file(dir+name+".txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);

    for(int i=0;i<_h;i++)
    {
        for(int j=0;j<_w;j++)
        {
            out<<QString::number(weight[i][j])<<" ";
        }
        out<<"\n";
    }
    file.close();

}
