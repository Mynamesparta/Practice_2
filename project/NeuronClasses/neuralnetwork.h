#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include "vector"
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>

using namespace World_of_Const;
class Neuron;
class NeuralNetwork
{
private:

    QDir dir;
    vector<Neuron*> neurons;
    short input[size_of_symbol][size_of_symbol];
    NeuralNetworkTrainer window;
    void Restart();

public:
    NeuralNetwork();
    void Load(vector<PicObject*>);
    void Load(vector<short>&);
    void Load(short [World_of_Const::size_of_symbol][World_of_Const::size_of_symbol]);
    QString FindSymbol();
    QString TimeToTraining();
    Neuron* FindNeuron(QString name);
    void Paint(Image& image,QString);
};

class Neuron
{
public:
    Neuron(QString dir,QString name);
    void Save();
    void Restart();
    int FindSume(short (*input)[size_of_symbol]);
    //Neuron& operator+(short(*input)[size_of_symbol]);
    //Neuron& operator-(short(*input)[size_of_symbol]);
    Neuron& operator=(Neuron &B);
    Neuron& operator+=(short(*input)[size_of_symbol]);
    Neuron& operator-=(short(*input)[size_of_symbol]);

    int weight[size_of_symbol][size_of_symbol];
    QString name;
    QString dir;
private:
};


#endif // NEURALNETWORK_H
