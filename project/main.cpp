#include <QtGui/QApplication>
#include <QThread>
#include <QDebug>
#include "controller.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "NeuronClasses/searcher.h"
#include "NeuronClasses/convolutional_neural_network.h"
#include "ImageController/loader.h"
#include "ImageController/image.h"
#include "NeuronClasses/neuronv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller con(&a);
    ConvolutionalNeuralNetwork* CNN=new ConvolutionalNeuralNetwork();

    QObject::connect(CNN,SIGNAL(EvolveEnd(QVector<double>)),&con,SLOT(SlotEvolveEnd(QVector<double>)));
    QObject::connect(CNN,SIGNAL(TrainingEnd(double)),&con,SLOT(SlotTrainingEnd(double)));
    QObject::connect(&con,SIGNAL(StartEvolve(Image*)),CNN,SLOT(Slot_Evolve(Image*)));
    QObject::connect(&con,SIGNAL(StartTraining(Image*,QVector<double>)),CNN,SLOT(Slot_Training(Image*,QVector<double>)));
    QObject::connect(&con,SIGNAL(Alpha_EtaUpdate(double,double)),CNN,SLOT(Slot_Update_Alpha_Eta(double,double)));
    QObject::connect(&con,SIGNAL(EndTraining()),CNN,SLOT(Slot_End_Training()));

    QThread * t=new QThread();
    QObject::connect(t,SIGNAL(finished()),t,SLOT(deleteLater()));
    QObject::connect(t,SIGNAL(finished()),CNN,SLOT(deleteLater()));
    CNN->moveToThread(t);
    //CNN->Ini();
    //con.Ini_speed();
    t->start();
    qRegisterMetaType<QVector<double> >("QVector<double>");
    //qDebug()<<"Hello"<<df(0);

    /*/
    Matrix b(5,5);
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            b[i][j]=i+j;
    qDebug()<<b.toString();
    qDebug()<<(b*3).toString();
    return 0;
    /*/
    return a.exec();
}
