#ifndef NEURON_H
#define NEURON_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QVector>
#include "matrix.h"
#include "World_of_Const.h"


class Neuron
{
public:
    Neuron(QString dir,QString name,int w=w_of_Neuron,int h=h_of_Neuron);
    Neuron();
    void Initialization(QString dir,QString name,int w=w_of_Neuron,int h=h_of_Neuron);
    void Save();
    void operator=(Neuron b);
    Matrix weight;
    QString name;
    QString dir;
private:
};

#endif // NEURON_H
