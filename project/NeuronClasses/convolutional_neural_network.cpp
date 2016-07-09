#include "convolutional_neural_network.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork():dir(pathNeuronWeight)
{
    qDebug()<<"Ini Convolutional Neural Nerwork:"<<dir.path();
    if(dir.exists())
    {
        QStringList filters;
        filters<<"[a-z,A-Z,0-9]*";
        dir.setNameFilters(filters);
        QStringList list=dir.entryList();
        qDebug()<<"size of list="<<list.size();
        foreach (QString dirinfo, list)
        {
            qDebug()<<"add Searcher:"<<dirinfo;
            Searcher n(pathNeuronWeight+dirinfo,dirinfo);
            searchers<<n;
        }

        hideLayer.resize(deapth_ofNetwork);
        for(int i=0;i<deapth_ofNetwork;i++)
            for(int j=0;j<number_of_neuron_inLayer[i];j++)
            {
                Neuron n(dir.path()+"/"+QString::number(i)+"_"+QString::number(j)+".txt",QString::number(i)+"_"+QString::number(j)+".txt");
                hideLayer[i]<<n;
            }
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }
}
