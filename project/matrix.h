#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QDebug>
#include "World_of_Const.h"
using namespace World_of_Const;
class Matrix
{
public:
    Matrix(int w,int h);
    Matrix();
    QVector<double> operator[](int i);
    double& getElement(int i,int j);
    QVector<QVector<double> >& getData();
    Matrix operator*(Matrix &b);
    Matrix operator/(int b);
    void operator=(Matrix&);
    inline int w();
    inline int h();

private:
    QVector<QVector<double> > data;
    int _w,_h;
    double null_elem;
};

#endif // MATRIX_H
