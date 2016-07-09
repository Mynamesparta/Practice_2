#ifndef CONVOLUTIONAL_NEURAL_NETWORK_H
#define CONVOLUTIONAL_NEURAL_NETWORK_H
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include "matrix.h"
#include "World_of_Const.h"
#include "searcher.h"
class ConvolutionalNeuralNetwork
{
public:
    ConvolutionalNeuralNetwork();
private:
    int _height;
    int _deapth;
    QDir dir;
    QVector<Searcher> searchers;
    QVector<QVector<Neuron> > hideLayer;

};

#endif // CONVOLUTIONAL_NEURAL_NETWORK_H
