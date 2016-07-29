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
    double lenght();
    void Ini();
    void SaveMap(QString path);
    QVector<double> data;
    double b;

    static QVector<Matrix> getVec_of_Matrix(NeuronV& vec,int w,int h);


private:
    QString name;
    QString path;
};

#endif // VECTOR_H
