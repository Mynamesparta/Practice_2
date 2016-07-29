#include "neuronm.h"

NeuronM::NeuronM(QString dir,QString name,int w,int h):dir(dir),name(name.replace(".txt","")),weight(w,h)
{
    qDebug()<<dir;
    qDebug()<<name.replace(".txt","");
    QFile file(dir);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!file.exists())
    {
        qDebug()<<"Something wrong in Neuron::Neuron: file doesnt exists";
        //return;
    }
    QTextStream in(&file);
    QString line;
    QStringList stringlist;
    int i=0;
    line=in.readLine();
    weight.b=(line.isNull()?0:line.toDouble());
    line=in.readLine();
    while(!line.isNull())
    {
        if(line=="")
        {
            line=in.readLine();
            continue;
        }
        stringlist=line.split(" ");
        for(int j=0;j<stringlist.size();j++)
        {
            if(j==w)
                break;
            if(stringlist[j]!="")
            {
                weight[i][j]=stringlist[j].toDouble();
            }
        }
        i++;
        if(i==h)
            break;
        line=in.readLine();

    }

    QString text;
    for(int i=0;i<h;i++)
    {
        text="";
        for(int j=0;j<w;j++)
            text+=QString::number(weight[i][j])+" ";
        //qDebug()<<text;
    }
    file.close();
    qDebug()<<"---------------------------------";
    Save();

}

NeuronM::NeuronM()
{

}
NeuronM::~NeuronM()
{
}

void NeuronM::Initialization(QString _dir, QString _name, int w, int h)
{
    dir=_dir;
    name=_name.replace(".txt","");
    weight.Initialization(w,h);

    qDebug()<<name.replace(".txt","");
    QFile file(dir);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!file.exists())
    {
        qDebug()<<"Something wrong: file doesnt exists";
        return;
    }
    QTextStream in(&file);
    QString line;
    QStringList stringlist;
    int i=0;
    line=in.readLine();
    weight.b=(line.isNull()?0:line.toDouble());
    line=in.readLine();
    while(!line.isNull())
    {
        if(line=="")
        {
            line=in.readLine();
            continue;
        }
        stringlist=line.split(" ");
        for(int j=0;j<stringlist.size();j++)
        {
            if(j==w)
                break;
            if(stringlist[j]!="")
            {
                weight[i][j]=stringlist[j].toDouble();
            }
        }
        i++;
        if(i==h)
            break;
        line=in.readLine();

    }

    QString text;
    for(int i=0;i<h;i++)
    {
        text="";
        for(int j=0;j<w;j++)
            text+=QString::number(weight[i][j])+" ";
        //qDebug()<<text;
    }
    file.close();
    qDebug()<<"---------------------------------";
    Save();

}

void NeuronM::Save()
{
    QFile file(dir);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    //qDebug()<<"weight size:"<<weight.h()<<"X"<<weight.w();
    out<<weight.b<<"\n";
    for(int i=0;i<weight.h();i++)
    {
        for(int j=0;j<weight.w();j++)
        {
            //qDebug()<<"Hi"<<QString::number(weight[i][j]);
            out<<QString::number(weight[i][j])<<" ";
        }
        out<<"\n";
    }
    file.close();

}

void NeuronM::operator =(NeuronM b)
{
    if(this==&b)
        return;
    weight=b.weight;
    name=b.name;
    dir=b.dir;
}

QVector<double>& NeuronM::operator [](int i)
{
    return weight[i];
}

void NeuronM::Ini()
{
    for(int i=0;i<weight.h();i++)
        for(int j=0;j<weight.w();j++)
            weight[i][j]=randDouble(IniA,IniB);
    weight.b=randDouble(IniA,IniB);
    double mid=weight.mid();

    for(int i=0;i<weight.h();i++)
        for(int j=0;j<weight.w();j++)
            weight[i][j]-=mid;
    weight.b-=mid;
    //qDebug()<<mid<<weight.mid();
    Save();
}
