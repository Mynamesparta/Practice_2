#include "convolutional_neural_network.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork():dir(pathNeuronWeight),eta(0.5),alpha(1)
{
    qDebug()<<"Ini Convolutional Neural Nerwork:"<<dir.path();
    if(dir.exists())
    {
        QStringList filters;
        filters<<"[a-z,A-Z,0-9]*";
        dir.setNameFilters(filters);
        QStringList list=dir.entryList();
        //qDebug()<<"size of list="<<list.size();
        foreach (QString dirinfo, list)
        {
            break;
            qDebug()<<"add Searcher:"<<dirinfo;
            Searcher n(pathNeuronWeight+dirinfo,dirinfo);
            searchers<<n;
        }

        hideLayer_n.resize(deapth_ofHideNetwork);
        hideLayer_1_n.resize(deapth_ofHideNetwork);
        for(int i=0;i<deapth_ofHideNetwork;i++)
            for(int j=0;j<number_of_neuron_inHideLayer[i];j++)
            {

                NeuronM n(dir.path()+"/Hide_Neuron_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j)+".txt",
                         size_of_neuron_inHideLayer[i],size_of_neuron_inHideLayer[i]);
                hideLayer_n[i]<<n;
                n=NeuronM(dir.path()+"/Hide_Neuron_1_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j)+".txt",
                         size_of_neuron_inHideLayer[i],size_of_neuron_inHideLayer[i]);
                hideLayer_1_n[i]<<n;
            }

        fullLayer_n.resize(deapth_ofFullNetwork);
        fullLayer_1_n.resize(deapth_ofFullNetwork);
        for(int i=0;i<deapth_ofFullNetwork;i++)
            for(int j=0;j<number_of_neuron_inFullLayer[i];j++)
            {
                NeuronV n(dir.path()+"/Full_Neuron_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j),
                         size_of_neuron_inFullLayer[i]);
                fullLayer_n[i]<<n;
                n=NeuronV(dir.path()+"/Full_Neuron_1_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j),
                         size_of_neuron_inFullLayer[i]);
                fullLayer_1_n[i]<<n;
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
    hide_mapsY.clear();
    full_mapsY.clear();
    hide_mapsV.clear();
    full_mapsV.clear();
    hide_mapsV.resize(deapth_ofHideNetwork);
    full_mapsV.resize(deapth_ofFullNetwork);
    current_hide_map<<image.red<<image.green<<image.blue;
    int i,j,k;
    Matrix m;

    //=================hide=layer==========================
    for(i=0;i<deapth_ofHideNetwork;i++)
    {
        for(j=0;j<number_of_neuron_inHideLayer[i];j++)
        {
            m=current_hide_map[0]*hideLayer_n[i][j].weight;
            for(k=1;k<current_hide_map.size();k++)
            {
                m=m+current_hide_map[k]*hideLayer_n[i][j].weight;
            }
            m=m/diminutive_number[i];
            hide_mapsV[i]<<m.dFunction();
            next_hide_map<<m.Function();
        }
        hide_mapsY<<current_hide_map;
        current_hide_map=next_hide_map;
        next_hide_map.clear();
    }
    //=================full=layer==========================
    current_full_map=NeuronV(current_hide_map);
    full_mapsV<<NeuronV(hide_mapsV[deapth_ofHideNetwork-1]);
    for(i=0;i<deapth_ofFullNetwork;i++)
    {
        next_full_map=NeuronV(number_of_neuron_inFullLayer[i]);
        for(j=0;j<number_of_neuron_inFullLayer[i];j++)
        {
            next_full_map[j]=current_full_map*fullLayer_n[i][j];
        }
        full_mapsV<<next_full_map.dFunction();
        full_mapsY<<current_full_map;
        current_full_map=next_full_map.Function();
    }
    full_mapsY<<current_full_map;
    return current_full_map.Function().data;
}


void ConvolutionalNeuralNetwork::Training(Image &image, QVector<double>& _d)
{
    NeuronV res(Evolve(image));
    NeuronV d(_d);
    int l,i,j;
    //=================full=layer==========================
    NeuronV current_full_delta,next_full_delta;
    current_full_delta=d-res;
    l=deapth_ofFullNetwork-1;
    next_full_delta=NeuronV(number_of_neuron_inFullLayer[l]);
    fullLayer_n_1=fullLayer_n;
    for(i=0;i<number_of_neuron_inFullLayer[l];i++)
    {
        next_full_delta[i]=current_full_delta[i]*full_mapsV[l][i];
    }
    changeWeight(current_full_delta,fullLayer_1_n[l],fullLayer_n[l],fullLayer_n_1[l],full_mapsY[l]);
    l--;
    for(;l>=0;l--)
    {
        current_full_delta=next_full_delta;
        next_full_delta=NeuronV(number_of_neuron_inFullLayer[l]);
        for(i=0;i<number_of_neuron_inFullLayer[l];i++)
        {
            for(j=0;j<number_of_neuron_inFullLayer[l+1];j++)
            {
                next_full_delta[i]+=current_full_delta[j]*fullLayer_n[l][i][j];
            }
            next_full_delta[i]*=full_mapsV[l][i];
        }
        changeWeight(current_full_delta,fullLayer_1_n[l],fullLayer_n[l],fullLayer_n_1[l],full_mapsY[l]);
    }
    //=================hide=layer==========================
    QVector<Matrix> current_hide_delta,next_hide_delta;
    l=deapth_ofHideNetwork-1;
    for(i=0;i<next_full_delta.data.size();i++)
    {
        Matrix m(1,1);
        m[0][0]=next_full_delta[i];
        current_hide_delta<<m*diminutive_number[l];
    }
    changeWeight(current_hide_delta,hideLayer_1_n[l],hideLayer_n[l],hideLayer_n_1[l],hide_mapsY[l]);

    for(l=deapth_ofHideNetwork-2;l>=0;l--)
    {
        findDelta(hide_mapsV[l],hideLayer_n[l+1],next_hide_delta,current_hide_delta);
        current_hide_delta=next_hide_delta;
        for(i=0;i<current_hide_delta.size();i++)
        {
            current_hide_delta[i]=current_hide_delta[i]*diminutive_number[l];
        }
        changeWeight(current_hide_delta,hideLayer_1_n[l],hideLayer_n[l],hideLayer_n_1[l],hide_mapsY[l]);
    }

    //=================time=toEnd==========================
    SaveNewWeight();
}

void ConvolutionalNeuralNetwork::findDelta(QVector<Matrix> &V, QVector<NeuronM> &weight_n, QVector<Matrix> &nextDelta, QVector<Matrix> &currentDelta)
{
       static Matrix weight;
       static int i,j;
       nextDelta.resize(currentDelta.size());
       for(j=0;j<weight_n.size();j++)
       {
           weight=weight_n[j].weight.Reverse();
           for(i=0;i<currentDelta.size();i++)
           {
               nextDelta[j]=nextDelta[i]+currentDelta[j]*weight;
           }
       }
       for(i=0;i<nextDelta.size();i++)
       {
           nextDelta[i]=Matrix::multiplication(nextDelta[i],V[i]);
       }
}
void ConvolutionalNeuralNetwork::changeWeight(NeuronV& delta,QVector<NeuronV>& weight_1_n,QVector<NeuronV>& weight_n,QVector<NeuronV>& weight_n_1,NeuronV& Y)
{
    static int i,j;
    weight_n_1=weight_n;
    for(j=0;j<weight_n_1.size();j++)
    {
        for(i=0;i<weight_n_1[j].data.size();i++)
        {
            weight_n_1[j][i]=weight_n[j][i]+alpha*weight_1_n[j][i]+eta*delta[j]*Y[i];
        }
    }
}

void ConvolutionalNeuralNetwork::changeWeight(QVector<Matrix> &delta, QVector<NeuronM> &weight_1_n, QVector<NeuronM> &weight_n, QVector<NeuronM> &weight_n_1, QVector<Matrix> &Y)
{
    static int j,x,y;
    static Matrix midD,midY,m;
    weight_n_1=weight_n;
    static double n;
    n=0;
    for(j=0;j<weight_n_1.size();j++)
    {
        m=Y[j].lazy_middel(weight_n_1[j].weight.w(),weight_n_1[j].weight.h());
        for(x=0;x<weight_n_1[j].weight.w();x++)
            for(y=0;y<weight_n_1[j].weight.h();y++)
            {
                midY[y][x]=midY[y][x]*(n/(n+1))+m[y][x]*(1/(n+1));
            }
        n++;
    }
    for(j=0;j<weight_n_1.size();j++)
    {
        midD=delta[j].lazy_middel(weight_n_1[j].weight.w(),weight_n_1[j].weight.h());
        for(x=0;x<weight_n_1[j].weight.w();x++)
            for(y=0;y<weight_n_1[j].weight.h();y++)
            {
                weight_n_1[j][y][x]=weight_n[j][y][x]+alpha*weight_1_n[j][y][x]+eta*midD[y][x]*midY[y][x];
            }
    }
}


void ConvolutionalNeuralNetwork::SaveNewWeight()
{
    fullLayer_1_n=fullLayer_n;
    fullLayer_n=fullLayer_n_1;
    for(int l=0;l<hideLayer_n.size();l++)
    {
        for(int j=0;j<hideLayer_n[l].size();j++)
        {
            hideLayer_1_n[l][j].weight=hideLayer_n[l][j].weight;
            hideLayer_n[l][j].weight=hideLayer_n_1[l][j].weight;
            hideLayer_1_n[l][j].Save();
            hideLayer_n[l][j].Save();
        }
    }
    for(int l=0;l<fullLayer_n.size();l++)
    {
        for(int j=0;j<fullLayer_n[l].size();j++)
        {
            fullLayer_1_n[l][j].data=fullLayer_n[l][j].data;
            fullLayer_n[l][j].data=fullLayer_n_1[l][j].data;
            fullLayer_1_n[l][j].Save();
            fullLayer_n[l][j].Save();
        }
    }
}


