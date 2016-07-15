#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QWidget>
#include <QDebug>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include "ImageController/image.h"

namespace Ui {
    class ImageForm;
}

class ImageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ImageForm(QWidget *parent = 0);
    ~ImageForm();
    void setProgress(int i,int s);
    void setImage(Image &image);
    void setEnablNext(bool b);
    void setClasses(int i,QString name,double p);

signals:
    void ShowMustGoOn(int i);
    void Next();
    void Previous();
private slots:
    void on_BackButton_clicked();

    void on_PreviousButton_clicked();

    void on_NextButton_clicked();

private:
    Ui::ImageForm *ui;
    QGraphicsScene scene;
    QGraphicsPixmapItem* pixmap;
};

#endif // IMAGEFORM_H
