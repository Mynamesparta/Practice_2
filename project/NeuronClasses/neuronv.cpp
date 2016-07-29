#include "neuronv.h"

NeuronV::NeuronV()
{
}

NeuronV::NeuronV(QVector<Matrix>& a):b(0)
{
    for(int i=0;i<a.size();i++)
    {
        for(int y=0;y<a[i].h();y++)
        {
            for(int x=0;x<a[i].w();x++)
            {
                data<<a[i][y][x];
            }
        }
    }
}

NeuronV::NeuronV(QVector<double> a):b(0)
{
    data=a;
}

NeuronV::NeuronV(QString _path,QString name,int size):name(name),path(_path)
{
    data.resize(size);
    QFile file(_path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line=file.readLine();
        b=line.toDouble();
        line=file.readLine();
        QStringList list=line.split(" ");
        for(int i=0;i<list.size()&&i<data.size();i++)
        {
            if(!list[i].isEmpty())
                data[i]=list[i].toDouble();
        }
        file.close();
    }
    Save();
}

NeuronV::NeuronV(int size)
{
    data.resize(size);
}

void NeuronV::Save()
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QString text;
        QTextStream out(&file);
        out<<b<<"\n";
        for(int i=0;i<data.size();i++)
        {
            text+=QString::number(data[i])+" ";
        }
        out<<text;
        file.close();
    }
}

void NeuronV::SaveMap(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QString text;
        QTextStream out(&file);
        out<<b<<"\n";
        for(int i=0;i<data.size();i++)
        {
            text+=QString::number(data[i])+" ";
        }
        out<<text;
        file.close();
    }
}

double NeuronV::lenght()
{
    double l=0;
    for(int i=0;i<data.size();i++)
    {
        l+=data[i]*data[i];
    }
    return l;
}

void NeuronV::Ini()
{
    double mid=0;
    double n=0;
    for(int i=0;i<data.size();i++)
    {
        data[i]=randDouble(IniA,IniB);
        mid=mid*(n/(n+1))+data[i]/(n+1);
        n++;
    }
    b=randDouble(IniA,IniB);
    mid=mid*(n/(n+1))+b/(n+1);

    for(int i=0;i<data.size();i++)
    {
        data[i]-=mid;
    }
    b-=mid;
    Save();
}

NeuronV NeuronV::Function()
{
    NeuronV c(data.size());
    for(int i=0;i<data.size();i++)
    {
        c[i]=f(data[i]);
    }
    return c;
}

NeuronV NeuronV::dFunction()
{
    NeuronV c(data.size());
    for(int i=0;i<data.size();i++)
    {
        c[i]=df(data[i]);
    }
    return c;
}

double NeuronV::operator *(NeuronV weight)
{
    double c=0;
    for(int i=0;i<data.size();i++)
    {
        c+=data[i]*weight[i];
    }
    c+=weight.b;
    return c;
}

NeuronV NeuronV::operator -(NeuronV &b)
{
    NeuronV c(data.size());
    for(int i=0;i<data.size();i++)
        c[i]=data[i]-b[i];
    return c;
}

double& NeuronV::operator [](int i)
{
    return data[i];
}

void NeuronV::operator =(NeuronV a)
{
    data=a.data;
    b=a.b;
}


QVector<Matrix> NeuronV::getVec_of_Matrix(NeuronV &vec, int w,int h)
{
    QVector<Matrix> rez;
    static int x,y;
    x=0;
    y=0;
    Matrix m(w,h);
    for(int i=0;i<vec.data.size();i++)
    {
        m[y][x]=vec[i];
        x++;
        if(x==w)
        {
            x=0;
            y++;
            if(y==h)
            {
                rez<<m;
                y=0;
            }
        }
    }
    rez<<m;
    return rez;
}
