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
    _path=path;
    QImage image(path);
    qDebug()<<"Ini";
    Initialization(image);
    qDebug()<<"end INI";
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
    qDebug()<<red.mid();
}

void Image::operator =(Image i)
{
    red=i.red;
    blue=i.blue;
    green=i.green;
}

void Image::save(QString path)
{
    QImage im(red.w(),red.h(),QImage::Format_RGB32);
    qDebug()<<"start save";
    for(int x=0;x<red.w();x++)
    {
        for(int y=0;y<red.h();y++)
        {
            im.setPixel(x,y,qRgb((int)red[y][x],(int)green[y][x],(int)blue[y][x]));
        }
    }
    im.save(path);
}

QImage Image::getQImage()
{
    QImage im(red.w(),red.h(),QImage::Format_RGB32);
    for(int x=0;x<red.w();x++)
    {
        for(int y=0;y<red.h();y++)
        {
            im.setPixel(x,y,qRgb((int)red[y][x],(int)green[y][x],(int)blue[y][x]));
        }
    }
    return im;
}

QString Image::getPath()
{
    return _path;
}

void Image::resize(int w, int h)
{
    _resize(w,h,red);
    _resize(w,h,green);
    _resize(w,h,blue);
}

void Image::_resize(double w, double h, Matrix &m)
{
    Matrix res(w,m.h());
    int x_input,y_input,x_output,y_output;
    int d,fill_of_pix;
    double current_pix;

    for(y_output=0;y_output<m.h();y_output++)
    {
        d=w;
        fill_of_pix=0;
        x_input=x_output=0;
        current_pix=0;
        while(x_output<w)
        {
            if(fill_of_pix+d>=m.w())
            {
                current_pix+=m[y_output][x_input]*(1-(double)fill_of_pix/m.w());
                res[y_output][x_output]=current_pix;
                current_pix=0;
                d-=(m.w()-fill_of_pix);
                fill_of_pix=0;
                x_output++;
            }
            else
            {
                current_pix+=m[y_output][x_input]*d/m.w();
                x_input++;
                fill_of_pix+=d;
                d=w;
            }
        }
    }

    m=res;
    res.Initialization(w,h);
    for(x_output=0;x_output<w;x_output++)
    {
        d=h;
        fill_of_pix=0;
        y_input=y_output=0;
        current_pix=0;
        while(y_output<h)
        {
            if(fill_of_pix+d>=m.h())
            {
                if(y_input<m.h())
                    current_pix+=m[y_input][x_output]*(1-(double)fill_of_pix/m.h());
                res[y_output][x_output]=current_pix;
                current_pix=0;
                d-=(m.h()-fill_of_pix);
                fill_of_pix=0;
                y_output++;
            }
            else
            {
                current_pix+=m[y_input][x_output]*d/m.h();
                y_input++;
                fill_of_pix+=d;
                d=h;
            }
        }
    }
    m=res;
}
