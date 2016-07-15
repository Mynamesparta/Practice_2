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

        hideLayer.resize(deapth_ofHideNetwork);
        for(int i=0;i<deapth_ofHideNetwork;i++)
            for(int j=0;j<number_of_neuron_inHideLayer[i];j++)
            {
                NeuronM n(dir.path()+"/Hide_Neuron_"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j)+".txt",
                         size_of_neuron_inHideLayer[i],size_of_neuron_inHideLayer[i]);
                hideLayer[i]<<n;
            }

        fullLayer.resize(deapth_ofFullNetwork);
        for(int i=0;i<deapth_ofFullNetwork;i++)
            for(int j=0;j<number_of_neuron_inFullLayer[i];j++)
            {
                NeuronV n(dir.path()+"/Full_Neuron_"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j),
                         size_of_neuron_inFullLayer[i]);
                fullLayer[i]<<n;
            }
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }
    ini_vector_of_classes_name();
    qDebug()<<"classes_name"<<classes_name;
}

void ConvolutionalNeuralNetwork::ini_vector_of_classes_name()
{
    QFile file(pathNeuronWeight+"/Name_of_classes.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        QString line;
        int i=0;
        line=in.readLine();
        while(!line.isNull())
        {
            classes_name<<line;
            reg_for_classes_name<<QRegExp(line);
            line=in.readLine();
        }

    }
    else
    {
        qDebug()<<"Something wrong:file \"Name_of_classes.txt\" doesnt exist ";
    }
    qDebug()<<classes_name;
    return;
    QDir d(pathNeuronWeight);
    QStringList filters;
    dir.setNameFilters(filters);
    QStringList flist=d.entryList();
    QRegExp r("^[a-z ]+$");
    foreach(QString name,flist)
    {
        if(name.contains(r))
        {
            classes_name<<name;
            reg_for_classes_name<<QRegExp(name);
        }
    }
}

QString ConvolutionalNeuralNetwork::getName_of_Classes(QString path)
{
    for(int i=0;i<classes_name.size();i++)
    {
        if(path.contains(reg_for_classes_name[i]))
            return classes_name[i];
    }
    return "";
}

QVector<int> ConvolutionalNeuralNetwork::getVofInt(QString path)
{
    QVector<int> vec(classes_name.size(),0);
    for(int i=0;i<classes_name.size();i++)
    {
        if(path.contains(reg_for_classes_name[i]))
        {
            vec[i]=1;
            return vec;
        }

    }
    return vec;
}

QVector<double> ConvolutionalNeuralNetwork::Evolve(Image &image)
{
    QVector<Matrix> current_hide_map,next_hide_map;
    NeuronV current_full_map,next_full_map;
    hide_maps.clear();
    full_maps.clear();
    current_hide_map<<image.red<<image.green<<image.blue;
    int i,j,k;
    Matrix m;
    //=================hide=layer==========================
    for(i=0;i<deapth_ofHideNetwork;i++)
    {
        for(j=0;j<number_of_neuron_inHideLayer[i];j++)
        {
            m=current_hide_map[0]*hideLayer[i][j].weight;
            for(k=1;k<current_hide_map.size();k++)
            {
                m=m+current_hide_map[k]*hideLayer[i][j].weight;
            }
            m=m/diminutive_number[i];
            m.Function();
            next_hide_map<<m;
        }
        hide_maps<<current_hide_map;
        current_hide_map=next_hide_map;
        next_hide_map.clear();
    }
    //=================full=layer==========================
    current_full_map=NeuronV(current_hide_map);
    for(i=0;i<deapth_ofFullNetwork;i++)
    {
        next_full_map=NeuronV(number_of_neuron_inFullLayer[i]);
        for(j=0;j<number_of_neuron_inFullLayer[i];j++)
        {
            next_full_map[j]=current_full_map*fullLayer[i][j];
        }
        full_maps<<current_full_map;
        current_full_map=next_full_map;
    }
    full_maps<<current_full_map;
    return current_full_map;
}


