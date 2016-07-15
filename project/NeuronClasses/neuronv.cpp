#include "neuronv.h"

NeuronV::NeuronV()
{
}

NeuronV::NeuronV(QVector<Matrix> &b)
{
    for(int i=0;i<b.size();i++)
    {
        for(int x=0;x<b[i].w();x++)
        {
            for(int y=0;y<b[i].h();y++)
            {
                data<<b[i][y][x];
            }
        }
    }
}

NeuronV::NeuronV(QString _path,QString name,int size):name(name),path(_path)
{
    data.resize(size);
    QFile file(_path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line=file.readLine();
        QStringList list=line.split(" ");
        for(int i=0;i<list.size()&&i<data.size();i++)
        {
            if(!list[i].isEmpty())
                data[i]=list[i].toDouble();
        }
        file.close();
    }
    save();
}

NeuronV::NeuronV(int size)
{
    data.resize(size);
}

void NeuronV::save()
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QString text;
        QTextStream out(&file);
        for(int i=0;i<data.size();i++)
        {
            text+=QString::number(data[i])+" ";
        }
        out<<text;
        file.close();
    }
}

void NeuronV::Function()
{
    for(int i=0;i<data.size();i++)
    {
        data[i]=f(data[i]);
    }
}

double NeuronV::operator *(NeuronV b)
{
    double c=0;
    for(int i=0;i<data.size();i++)
    {
        c+=data[i]*b[i];
    }
    return c;
}

double& NeuronV::operator [](int i)
{
    return data[i];
}

void NeuronV::operator =(NeuronV b)
{
    data=b.data;
}


