#ifndef VECTOR_H
#define VECTOR_H

#include <QDebug>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QFile>

#include "matrix.h"

class NeuronV
{
public:
    NeuronV();
    NeuronV(QVector<Matrix>&b);
    NeuronV(QString path,QString name, int size);
    NeuronV(int size);
    void Function();
    double& operator[](int i);
    double operator*(NeuronV b);
    void operator=(NeuronV b);
    void save();
    QVector<double> data;


private:
    QString name;
    QString path;
};

#endif // VECTOR_H
