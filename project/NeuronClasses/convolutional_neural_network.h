#ifndef CONVOLUTIONAL_NEURAL_NETWORK_H
#define CONVOLUTIONAL_NEURAL_NETWORK_H
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include <QRegExp>
#include "neuronv.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "searcher.h"
#include "ImageController/image.h"
class ConvolutionalNeuralNetwork
{
public:
    ConvolutionalNeuralNetwork();
    QString getName_of_Classes(QString path);
    QVector<int> getVofInt(QString path);
    QVector<double> Evolve(Image& image);
    void Training(Image& image,QVector<double>& d);
    void changeWeight(NeuronV& delta,QVector<NeuronV>& weight_1_n,QVector<NeuronV>& weight_n,QVector<NeuronV>& weight_n_1,NeuronV& Y);
    void changeWeight(QVector<Matrix> &delta, QVector<NeuronM> &weight_1_n, QVector<NeuronM> &weight_n, QVector<NeuronM> &weight_n_1, QVector<Matrix> &Y);
    void findDelta(QVector<Matrix>& V,QVector<NeuronM>& weight_n,QVector<Matrix>& nextDelta,QVector<Matrix>& currentDelta);
    //double multiplication(QVector<Matrix>& vec,Matrix& weight);
    //double multiplication(QVector<double>& vec,Matrix& weight);
private:
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

    QVector<QVector<Matrix> > hide_mapsY;
    QVector<QVector<Matrix> > hide_mapsV;
    QVector<NeuronV> full_mapsY;
    QVector<NeuronV> full_mapsV;

    double eta,alpha;

    void SaveNewWeight();



};

#endif // CONVOLUTIONAL_NEURAL_NETWORK_H
