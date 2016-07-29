#ifndef CONVOLUTIONAL_NEURAL_NETWORK_H
#define CONVOLUTIONAL_NEURAL_NETWORK_H
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include <QRegExp>
#include <QThread>
#include "neuronv.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "searcher.h"
#include "ImageController/image.h"
class ConvolutionalNeuralNetwork:public QObject
{
    Q_OBJECT
public:
    ConvolutionalNeuralNetwork();
    QString getName_of_Classes(QString path);
    QVector<int> getVofInt(QString path);
    QVector<double> Evolve(Image* image);
    double Training(Image* image,QVector<double>& d);
    void changeWeight(NeuronV& delta,QVector<NeuronV>& weight_1_n,QVector<NeuronV>& weight_n,QVector<NeuronV>& weight_n_1,NeuronV& Y);
    void changeWeight(QVector<Matrix> &delta, QVector<NeuronM> &weight_1_n, QVector<NeuronM> &weight_n, QVector<NeuronM> &weight_n_1, QVector<Matrix> &Y);
    void findDelta(QVector<Matrix>& dY,QVector<NeuronM>& weight_n,QVector<Matrix>& nextDelta,QVector<Matrix>& currentDelta);
    void findDelta(NeuronV& dY,QVector<NeuronV>& weight_n,NeuronV& nextDelta, NeuronV& currentDelta);
    //double multiplication(QVector<Matrix>& vec,Matrix& weight);
    //double multiplication(QVector<double>& vec,Matrix& weight);
    void run();
    void Ini();
public slots:
    void Slot_Evolve(Image* image);
    void Slot_Training(Image* image,QVector<double> d);
    void Slot_End_Training();
    void Slot_Update_Alpha_Eta(double al,double e);
signals:
    void TrainingEnd(double E);
    void EvolveEnd(QVector<double>);
private:
    bool endTraining;
    int _height;
    int _deapth;
    QDir dir;
    QVector<Searcher> searchers;
    QVector<QVector<NeuronM> > hideLayer_n;
    QVector<QVector<NeuronV> > fullLayer_n;
    QVector<QVector<NeuronM> > hideLayer_1_n;
    QVector<QVector<NeuronV> > fullLayer_1_n;
    QVector<QVector<NeuronM> > hideLayer_n_1;
    QVector<QVector<NeuronV> > fullLayer_n_1;
    QStringList classes_name;
    QVector<QRegExp> reg_for_classes_name;
    void ini_vector_of_classes_name();

    QVector<QVector<Matrix> > hide_maps_Y;
    QVector<QVector<Matrix> > hide_maps_dY;
    QVector<NeuronV> full_maps_Y;
    QVector<NeuronV> full_maps_dY;

    double eta,alpha;

    void SaveNewWeight();



};

#endif // CONVOLUTIONAL_NEURAL_NETWORK_H
