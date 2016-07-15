#include "imageform.h"
#include "ui_imageform.h"

ImageForm::ImageForm(QWidget *parent) :
    QWidget(parent),pixmap(0),
    ui(new Ui::ImageForm)
{
    ui->setupUi(this);
    ui->View->setScene(&scene);
}

ImageForm::~ImageForm()
{
    delete ui;
}

void ImageForm::setProgress(int i, int s)
{
    ui->progressBar->setFormat(QString::number(i)+"/"+QString::number(s));
}

void ImageForm::on_BackButton_clicked()
{
    ShowMustGoOn(0);
}

void ImageForm::on_PreviousButton_clicked()
{
    Previous();
}

void ImageForm::on_NextButton_clicked()
{
    Next();
}

void ImageForm::setImage(Image &image)
{
    QImage i=image.getQImage();
    qDebug()<<i.width()<<i.height();
    if(pixmap!=0)
        scene.removeItem(pixmap);
    pixmap=scene.addPixmap(QPixmap::fromImage(i));

}

void ImageForm::setEnablNext(bool b)
{
    ui->NextButton->setEnabled(b);
}

void ImageForm::setClasses(int i, QString name, double p)
{
    switch(i)
    {
    case 1:
        ui->progressBar1->setFormat(name);
        ui->progressBar1->setValue(p*100);
        break;
    case 2:
        ui->progressBar2->setFormat(name);
        ui->progressBar2->setValue(p*100);
        break;
    case 3:
        ui->progressBar3->setFormat(name);
        ui->progressBar3->setValue(p*100);
        break;
    case 4:
        ui->progressBar4->setFormat(name);
        ui->progressBar4->setValue(p*100);
        break;
    case 5:
        ui->progressBar5->setFormat(name);
        ui->progressBar5->setValue(p*100);
        break;
    }
}
