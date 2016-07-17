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
    NeuronV(QVector<Matrix> &b);
    NeuronV(QVector<double> b);
    NeuronV(QString path,QString name, int size);
    NeuronV(int size);
    NeuronV Function();
    NeuronV dFunction();
    double& operator[](int i);
    double operator*(NeuronV b);
    NeuronV operator-(NeuronV& b);
    void operator=(NeuronV b);
    void Save();
    QVector<double> data;


private:
    QString name;
    QString path;
};

#endif // VECTOR_H
