#ifndef SEARCHER_H
#define SEARCHER_H

#include "neuronm.h"
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
    inline QVector<NeuronM> & getHideNeuron();
    inline NeuronM& getOutNeuron();
private:
    QDir dir;
    QString name;
    QVector<NeuronM>  hideNeuron;
    NeuronM outputNeuron;
};

#endif // SEARCHER_H
