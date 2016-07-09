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
    Matrix red,green,blue;
};

#endif // IMAGE_H
