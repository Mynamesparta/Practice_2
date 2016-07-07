#include "matrix.h"

Matrix::Matrix(int w,int h)
{
    data.resize(h);
    for(int i=0;i<h;i++)
    {
        data[i].resize(w);
    }
    qDebug()<<data;
}

Matrix::Matrix()
{

}

double& Matrix::getElement(int i, int j)
{
    if(i<0||i>=_w||j<0||j>=_h)
    {
        null_elem=0;
        return null_elem;
    }
    return data[i][j];
}

QVector<QVector<double> >& Matrix::getData()
{
    return data;
}

QVector<double> Matrix::operator [](int i)
{
    return data[i];
}

Matrix::Matrix Matrix::operator *(Matrix &weight)
{
    Matrix c(_w,_h);
    static int i,j,di,dj;
    static int dw,dh;
    dw=weight.w()/2;
    dh=weight.h()/2;
    for(i=0;i<_w;i+=step_of_WeightM)
        for(j=0;j<_h;j+=step_of_WeightM)
        {
            for(di=0;di<weight.w();di++)
            {
                for(dj=0;dj<weight.h();dj++)
                {
                    c.getElement(i,j)+=this->getElement(i+di-dw,i+dj-dh)*weight.getElement(di,dj);
                }
            }
        }
    return c;
}

Matrix::Matrix Matrix::operator /(int b)
{
    Matrix c(_w/b,_h/b);
    static int i,j,di,dj;
    static double max,elem;
    for(i=0;i<_w;i+=b)
        for(j=0;j<_h;j+=b)
        {
            max=-1;
            for(di=0;di<b;di++)
                for(dj=0;dj<b;dj++)
                {
                    elem=this->getElement(i+di,j+dj);
                    if(max<elem)
                        max=elem;
                }
            c.getElement(i/b,j/b)=max;
        }
    return c;
}

void Matrix::operator =(Matrix& b)
{
    this->_h=b.h();
    this->_w=b.w();
    data=b.getData();
}

int Matrix::h()
{
    return _h;
}
int Matrix::w()
{
    return _w;
}
