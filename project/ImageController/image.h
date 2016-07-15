#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QDebug>
#include <QColor>
#include <QString>

#include "matrix.h"

class Image
{
public:
    Image();
    Image(QImage& image);
    Image(QString path);
    void Initialization(QImage& image);
    void operator=(Image i);
    void resize(int w,int h);
    void save(QString path);
    QImage getQImage();
    Matrix red,green,blue;
private:
    void _resize(double w,double h,Matrix& m);
    QString name_of_image;
    QString name_of_class;

};

#endif // IMAGE_H
