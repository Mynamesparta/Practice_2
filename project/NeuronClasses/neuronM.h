#ifndef NEURON_H
#define NEURON_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QVector>
#include "matrix.h"
#include "World_of_Const.h"


class NeuronM
{
public:
    NeuronM(QString dir,QString name,int w=w_of_Neuron,int h=h_of_Neuron);
    NeuronM();
    ~NeuronM();
    void Initialization(QString dir,QString name,int w=w_of_Neuron,int h=h_of_Neuron);
    void Save();
    void operator=(NeuronM b);
    QVector<double>& operator[](int i);
    void Ini();
    Matrix weight;
    //double b;
    QString name;
    QString dir;
private:
};

#endif // NEURON_H
