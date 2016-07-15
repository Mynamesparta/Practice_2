#include "searcher.h"

Searcher::Searcher(QString qsdir, QString name):dir(qsdir),name(name)
{
    qDebug()<<"add New Searcher:"<<dir.path();
    if(dir.exists())
    {
        QStringList filters;
        filters<<"[0-9]*.txt";
        dir.setNameFilters(filters);
        QFileInfoList list=dir.entryInfoList();
        qDebug()<<"size of list="<<list.size();
        foreach (QFileInfo fileinfo, list)
        {
            qDebug()<<"Load:"<<fileinfo.fileName();
            NeuronM n(fileinfo.filePath(),fileinfo.fileName());
            hideNeuron<<n;
        }
        outputNeuron.Initialization(dir.path()+"/output.txt","output.txt");
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }
}

Searcher::Searcher()
{

}

void Searcher::Initialization(QString qsdir,QString _name)
{
    dir=qsdir;
    name=_name;

    qDebug()<<"add New Searcher:"<<dir.path();
    if(dir.exists())
    {
        QStringList filters;
        filters<<"[0-9]*.txt";
        dir.setNameFilters(filters);
        QFileInfoList list=dir.entryInfoList();
        qDebug()<<"size of list="<<list.size();
        foreach (QFileInfo fileinfo, list)
        {
            qDebug()<<"Load:"<<fileinfo.fileName();
            NeuronM n(fileinfo.filePath(),fileinfo.fileName());
            hideNeuron<<n;
        }
        outputNeuron.Initialization(dir.path()+"/output.txt","output.txt");
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }

}

void Searcher::operator =(Searcher s)
{
    name=s.getName();
    hideNeuron=s.getHideNeuron();
    outputNeuron=s.getOutNeuron();
}

QString Searcher::getName()
{
    return name;
}

QVector<NeuronM>& Searcher::getHideNeuron()
{
    return hideNeuron;
}

NeuronM& Searcher::getOutNeuron()
{
    return outputNeuron;
}
