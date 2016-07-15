#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDebug>
#include <QApplication>
#include <QThread>
#include <QTime>
#include <QImage>

#include "Windows/mainwindow.h"
#include "Windows/testform.h"
#include "Windows/trainingform.h"
#include "Windows/imageform.h"
#include "ImageController/image.h"
#include "ImageController/loader.h"
#include "NeuronClasses/convolutional_neural_network.h"

class Controller:public QObject
{
    Q_OBJECT
public:
    Controller(QApplication* app);
private:
    MainWindow main;
    TrainingForm training;
    TestForm test;
    ImageForm imageF;
    Loader loader;
    ConvolutionalNeuralNetwork CNN;
    QApplication* app;
    int current_size;
    int index_of_currentImage;
    void StartTest();
signals:
    void StartTraining();
public slots:
    void Slot_Show(int i);
    void Slot_TestLoad(int dir,int number,bool random);
    void Slot_TestLoad(QStringList);
    void NextImage();
    void PreviousImage();
    void Start();
    //void Slot_TestLoad(QStringList list);
signals:

};

#endif // CONTROLLER_H
