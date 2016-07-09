#include "image.h"
Image::Image()
{

}

Image::Image(QImage &image)
{
    red.Initialization(image.width(),image.height());
    green=red;
    blue=red;
    QRgb rgb;
    for(int i=0;i<image.height();i++)
        for(int j=0;j<image.width();j++)
        {
            rgb=image.pixel(j,i);
            red[i][j]=qRed(rgb);
            blue[i][j]=qBlue(rgb);
            green[i][j]=qGreen(rgb);
        }
}

Image::Image(QString path)
{
    QImage image(path);
    Initialization(image);
}

void Image::Initialization(QImage &image)
{
    red.Initialization(image.width(),image.height());
    green=red;
    blue=red;
    QRgb rgb;
    for(int i=0;i<image.height();i++)
        for(int j=0;j<image.width();j++)
        {
            rgb=image.pixel(j,i);
            red[i][j]=qRed(rgb);
            blue[i][j]=qBlue(rgb);
            green[i][j]=qGreen(rgb);
        }
}

void Image::operator =(Image i)
{
    red=i.red;
    blue=i.blue;
    green=i.green;
}
