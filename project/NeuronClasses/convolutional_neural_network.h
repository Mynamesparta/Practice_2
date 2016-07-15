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
    double multiplication(QVector<Matrix>& vec,Matrix& weight);
    double multiplication(QVector<double>& vec,Matrix& weight);
private:
    int _height;
    int _deapth;
    QDir dir;
    QVector<Searcher> searchers;
    QVector<QVector<NeuronM> > hideLayer;
    QVector<QVector<NeuronV> > fullLayer;
    QStringList classes_name;
    QVector<QRegExp> reg_for_classes_name;
    void ini_vector_of_classes_name();

    QVector<QVector<Matrix> > hide_maps;
    QVector<NeuronV> full_maps;

};

#endif // CONVOLUTIONAL_NEURAL_NETWORK_H
