#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDebug>
#include <QApplication>
#include <QThread>
#include <QTime>
#include <QImage>
#include <QStringList>
#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QList>

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
    QString getName_of_Classes(QString path);
    QVector<double> getVofDouble(QString path);
    void Ini_speed();
private:
    MainWindow main;
    TrainingForm training;
    TestForm test;
    ImageForm imageF;
    Loader loader;
    QApplication* app;
    int current_size;
    int Number_of_TrainImage;
    int index_of_current_Image;

    QStringList classes_name;
    QVector<QRegExp> reg_for_classes_name;
    QList<double> list_of_E;
    double current_speed_of_alpha;
    double current_speed_of_eta;
    int AlphaIndex;
    int EtaIndex;
    //int number_of_Image;
    double eta,alpha;
    double number_of_Image;
    bool TimeToPauseTraining;
    void StartTest();
    void ini_vector_of_classes_name();
    void Save_speed();
    void Load_speed();
    void Update_speed();
signals:
    void StartTraining();
    void StartEvolve(Image*);
    void StartTraining(Image*,QVector<double>);
    void EndTraining();
    void IniTraining();
    void PlusETraining();
    void Alpha_EtaUpdate(double alpha,double eta);
public slots:
    void Slot_Show(int i);
    void Slot_TestLoad(int dir,int number,bool random);
    void Slot_TestLoad(QStringList);
    void NextImage();
    void PreviousImage();
    void Start();
    void Save_trainingM();
    void SlotEvolveEnd(QVector<double>);
    void SlotTrainingEnd(double);
    void SlotEtaChanged(double e);
    void SlotAlphaChanged(double al);
    //void Slot_TestLoad(QStringList list);
signals:

};

#endif // CONTROLLER_H
