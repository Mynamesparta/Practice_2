#include "matrix.h"

Matrix::Matrix(int w,int h)
{
    data.resize(h);
    for(int i=0;i<h;i++)
    {
        data[i].resize(w);
    }
    //qDebug()<<data;
}

Matrix::Matrix()
{

}

void Matrix::Initialization(int w ,int h)
{
    data.resize(h);
    for(int i=0;i<h;i++)
    {
        data[i].clear();
        data[i].resize(w);
    }
    //qDebug()<<data;

}

double& Matrix::getElement(int i, int j)
{
    if(j<0||j>=w()||i<0||i>=h())
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

QVector<double>& Matrix::operator [](int i)
{
    return data[i];
}

Matrix::Matrix Matrix::operator *(Matrix &weight)
{
    Matrix c(w(),h());
    static int j,i,dj,di;
    static int dw,dh;
    dw=weight.w()/2;
    dh=weight.h()/2;
    for(j=0;j<w();j+=step_of_WeightM)
        for(i=0;i<h();i+=step_of_WeightM)
        {
            for(dj=0;dj<weight.w();dj++)
            {
                for(di=0;di<weight.h();di++)
                {
                    c.getElement(i,j)+=this->getElement(i+di-dh,j+dj-dw)*weight.getElement(di,dj);
                }
            }
        }
    return c;
}

Matrix::Matrix Matrix::operator *(int b)
{
    int _w=w()*b;
    int _h=h()*b;
    Matrix c(_w,_h);
    static int i,j,di,dj;
    for(i=0;i<w();i++)
        for(j=0;j<h();j++)
        {
            for(di=0;di<b;di++)
                for(dj=0;dj<b;dj++)
                {
                    c[j*b+dj][i*b+di]=getElement(j,i);
                }
        }
    return c;
}

Matrix::Matrix Matrix::operator /(int b)
{
    int _w=w()/b+(w()%b==0?0:1);
    int _h=h()/b+(h()%b==0?0:1);
    Matrix c(_w,_h);
    static int i,j,di,dj;
    static double max,elem;
    for(i=0;i<_w*b;i+=b)
        for(j=0;j<_h*b;j+=b)
        {
            max=-1;
            for(di=0;di<b;di++)
                for(dj=0;dj<b;dj++)
                {
                    elem=this->getElement(j+dj,i+di);
                    if(max<elem)
                        max=elem;
                }
            c.getElement(j/b,i/b)=max;
        }
    return c;
}

void Matrix::operator =(Matrix b)
{
    data=b.getData();
}

Matrix Matrix::operator +(Matrix b)
{
    Matrix c(w(),h());
    static int x,y;
    for(x=0;x<w();x++)
        for(y=0;y<h();y++)
            c[y][x]=this->getElement(y,x)+b.getElement(y,x);
    return c;
}

int Matrix::h()
{
    return data.size();
}
int Matrix::w()
{
    if(h()==0)
        return 0;
    return data[0].size();
}

QString Matrix::toString()
{
    QString text;
    for(int y=0;y<h();y++)
    {
        for(int x=0;x<w();x++)
        {
            text+=QString::number(data[y][x])+" ";
        }
        text+="\n";
    }
    return text;
}

double Matrix::mid()
{
    double mid=0;
    double n=0;
    for(int y=0;y<h();y++)
        for(int x=0;x<w();x++)
        {
            mid=mid*(n/(n+1))+data[y][x]/(n+1);
            n++;
        }
    return mid;
}


void Matrix::normalizationF()
{
    for(int x=0;x<w();x++)
    {
        for(int y=0;y<h();y++)
        {
            data[y][x]/=255;
        }
    }
}
void Matrix::normalizationC()
{
    for(int x=0;x<w();x++)
    {
        for(int y=0;y<h();y++)
        {
            data[y][x]*=255;
        }
    }
}

Matrix Matrix::Function()
{
    Matrix c(w(),h());
    for(int x=0;x<w();x++)
    {
        for(int y=0;y<h();y++)
        {
            c[y][x]=f(data[y][x]);
        }
    }
    return c;
}

Matrix Matrix::dFunction()
{
    Matrix c(w(),h());
    for(int x=0;x<w();x++)
    {
        for(int y=0;y<h();y++)
        {
            c[y][x]=df(data[y][x]);
        }
    }
    return c;
}

Matrix Matrix::lazy_middel(int _w, int _h)
{
    Matrix rez(_w,_h);
    static int x,y,dx,dy;
    double n;
    int _2w=_w/2,_2h=_h/2;
    for(dx=-_2w;dx<=_2w;dx++)
    {
        for(dy=-_2h;dy<=_2h;dy++)
        {
            n=0;
            for(x=dx;x<w()+dx;x++)
                for(y=dy;y<h()+dy;y++)
                {
                    rez[dy+_2h][dx+_2w]=rez[dy+_2h][dx+_2w]*(n/(n+1))+getElement(y,x)/(n+1);
                    n++;
                }
        }
    }
    return rez;
}

Matrix Matrix::Reverse()
{
    Matrix c(w(),h());
    static int x,y;
    for(x=0;x<w();x++)
    {
        for(y=0;y<h();y++)
        {
            c[y][x]=data[h()-y][w()-x];
        }
    }
    return c;
}

Matrix Matrix::multiplication(Matrix &a, Matrix &b)
{
    static int x,y;
    Matrix c(a.w(),a.h());
    for(x=0;x<a.w();x++)
    {
        for(y=0;y<a.h();y++)
        {
            c[y][x]=a[y][x]*b[y][x];
        }
    }
    return c;
}
