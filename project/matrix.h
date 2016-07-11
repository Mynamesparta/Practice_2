#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QDebug>
#include <QString>
#include "World_of_Const.h"
using namespace World_of_Const;
class Matrix
{
public:
    Matrix(int w,int h);
    Matrix();
    void Initialization(int w ,int h);
    QVector<double>& operator[](int i);
    double& getElement(int i,int j);
    QVector<QVector<double> >& getData();
    Matrix operator*(Matrix &b);
    Matrix operator/(int b);
    void operator=(Matrix&);
    int w();
    int h();
    QString toString();
    double mid();

private:
    QVector<QVector<double> > data;
    double null_elem;
};

#endif // MATRIX_H
