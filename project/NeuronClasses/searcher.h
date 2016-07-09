#ifndef SEARCHER_H
#define SEARCHER_H

#include "neuron.h"
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDir>
#include <QFile>

class Searcher
{
public:
    Searcher(QString qsdir,QString name);
    Searcher();
    void Initialization(QString qsdir,QString name);
    void operator= (Searcher s);
    inline QString getName();
    inline QVector<Neuron> & getHideNeuron();
    inline Neuron& getOutNeuron();
private:
    QDir dir;
    QString name;
    QVector<Neuron>  hideNeuron;
    Neuron outputNeuron;
};

#endif // SEARCHER_H
