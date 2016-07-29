#include "convolutional_neural_network.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork():dir(pathNeuronWeight),eta(0.2),alpha(0.5),endTraining(false)
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
                /*/
                n=NeuronM(dir.path()+"/Hide_Neuron_1_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j)+".txt",
                         size_of_neuron_inHideLayer[i],size_of_neuron_inHideLayer[i]);
                /*/
                n.weight.Initialization(n.weight.w(),n.weight.h());
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
                /*/
                n=NeuronV(dir.path()+"/Full_Neuron_1_n/"+QString::number(i)+"_"+QString::number(j)+".txt",
                         QString::number(j),
                         size_of_neuron_inFullLayer[i]);
                /*/
                int l=n.data.size();
                n.data.clear();
                n.data.resize(l);
                fullLayer_1_n[i]<<n;
            }
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }
    //Ini();
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

QVector<double> ConvolutionalNeuralNetwork::Evolve(Image *image)
{
    QVector<Matrix> current_hide_map,next_hide_map;
    NeuronV current_full_map,next_full_map;
    hide_maps_Y.clear();
    full_maps_Y.clear();
    hide_maps_dY.clear();
    full_maps_dY.clear();
    current_hide_map<<image->red.to1()<<image->green.to1()<<image->blue.to1();
    delete image;
    int i,j,k;
    Matrix m;

    //=================hide=layer==========================
    hide_maps_Y.resize(deapth_ofHideNetwork);
    hide_maps_dY.resize(deapth_ofHideNetwork);
    for(i=0;i<deapth_ofHideNetwork;i++)
    {
        hide_maps_dY[i].resize(number_of_neuron_inHideLayer[i]);
        next_hide_map.resize(number_of_neuron_inHideLayer[i]);
        for(j=0;j<number_of_neuron_inHideLayer[i];j++)
        {
            m=current_hide_map[0]*hideLayer_n[i][j].weight;
            for(k=1;k<current_hide_map.size();k++)
            {
                m=m+current_hide_map[k]*hideLayer_n[i][j].weight;
            }
            m=m/diminutive_number[i];
            hide_maps_dY[i][j]=m.dFunction();
            next_hide_map[j]=m.Function();
        }
        hide_maps_Y[i]=current_hide_map;
        //qDebug()<<"Hide Layer:"<<i<<current_hide_map[0].toString();
        current_hide_map=next_hide_map;
        next_hide_map.clear();
    }
    if(TimeForTemp)
    {
        for(i=0;i<hide_maps_dY.size();i++)
            for(j=0;j<hide_maps_dY[i].size();j++)
            {
                hide_maps_dY[i][j].SaveMap(pathTemp+"hide_"+QString::number(i+1)+"_"+QString::number(j)+"_dY.txt");
            }
        for(i=0;i<hide_maps_Y.size();i++)
            for(j=0;j<hide_maps_Y[i].size();j++)
                hide_maps_Y[i][j].SaveMap(pathTemp+"hide_"+QString::number(i)+"_"+QString::number(j)+"_Y.txt");
    }
    //=================full=layer==========================
    current_full_map=NeuronV(current_hide_map);
    full_maps_dY<<NeuronV(hide_maps_dY.last());
    full_maps_dY.last().SaveMap(pathTemp+"fullDY_-1.txt");

    for(i=0;i<deapth_ofFullNetwork;i++)
    {
        next_full_map=NeuronV(number_of_neuron_inFullLayer[i]);
        //qDebug()<<"full_map"<<current_full_map.data;
        for(j=0;j<number_of_neuron_inFullLayer[i];j++)
        {
            next_full_map[j]=current_full_map*fullLayer_n[i][j];
        }
        full_maps_dY<<next_full_map.dFunction();
        full_maps_Y <<current_full_map;
        //qDebug()<<"Full Layer:"<<i<<current_full_map.data;
        current_full_map=next_full_map.Function();
    }
    full_maps_Y<<current_full_map;
    if(TimeForTemp)
    {
        for(i=0;i<full_maps_Y.size();i++)
            full_maps_Y[i].SaveMap(pathTemp+"full_"+QString::number(i)+"_Y.txt");
        for(i=0;i<full_maps_dY.size();i++)
            full_maps_dY[i].SaveMap(pathTemp+"full_"+QString::number(i)+"_DY.txt");
    }
    //qDebug()<<"Full Layer:";
    return current_full_map.data;
}


double ConvolutionalNeuralNetwork::Training(Image *image, QVector<double>& _d)
{
    qDebug()<<"=========================================================================================";
    NeuronV res(Evolve(image));
    qDebug()<<"Alpha and Eta"<<alpha<<eta;
    qDebug()<<"res="<<res.data;
    qDebug()<<"d="<<_d;
    NeuronV d(_d);
    int l,i,j;
    hideLayer_n_1.clear();
    hideLayer_n_1.resize(deapth_ofHideNetwork);
    fullLayer_n_1.clear();
    fullLayer_n_1.resize(deapth_ofFullNetwork);
    //=================full=layer==========================
    NeuronV current_full_delta,next_full_delta;
    current_full_delta=d-res;
    qDebug()<<"delta"<<current_full_delta.data;
    double E=-1;//current_full_delta.lenght();
    for(int k=0;k<current_full_delta.data.size();k++)
    {
        if(E<ABS(current_full_delta[k]))
            E=ABS(current_full_delta[k]);
    }
    E=0.5*current_full_delta.lenght();
    l=deapth_ofFullNetwork-1;
    next_full_delta=NeuronV(number_of_neuron_inFullLayer[l]);
    fullLayer_n_1=fullLayer_n;
    //
    for(i=0;i<number_of_neuron_inFullLayer[l];i++)
    {
        current_full_delta[i]=current_full_delta[i]*full_maps_dY[l+1][i];
    }
    //
    changeWeight(current_full_delta,fullLayer_1_n[l],fullLayer_n[l],fullLayer_n_1[l],full_maps_Y[l]);
    qDebug()<<1<<"Training";
    l--;
    for(;l>=0;l--)
    {
        /*/
        current_full_delta=next_full_delta;
        qDebug()<<"delta"<<l<<current_full_delta.data;
        next_full_delta=NeuronV(number_of_neuron_inFullLayer[l]);
        for(i=0;i<number_of_neuron_inFullLayer[l];i++)
        {
            for(j=0;j<number_of_neuron_inFullLayer[l+1];j++)
            {
                next_full_delta[i]+=current_full_delta[j]*fullLayer_n[l+1][j][i];
            }
            next_full_delta[i]*=full_maps_dY[l][i];
        }
        //qDebug()<<next_full_delta.data;
        /*/
        findDelta(full_maps_dY[l+1],fullLayer_n[l+1],next_full_delta,current_full_delta);
        current_full_delta=next_full_delta;
        changeWeight(current_full_delta,fullLayer_1_n[l],fullLayer_n[l],fullLayer_n_1[l],full_maps_Y[l]);
    }
    findDelta(full_maps_dY[0],fullLayer_n[0],next_full_delta,current_full_delta);
    //qDebug()<<next_full_delta.data;
    qDebug()<<2<<"Training";
    //=================hide=layer==========================
    QVector<Matrix> current_hide_delta,next_hide_delta;
    l=deapth_ofHideNetwork-1;
    //qDebug()<<"delta"<<-1<<next_full_delta.data;
    current_hide_delta=NeuronV::getVec_of_Matrix(next_full_delta,1,1);
    for(i=0;i<current_hide_delta.size();i++)
    {
        current_hide_delta[i]=current_hide_delta[i]*diminutive_number[l];
    }
    qDebug()<<3<<"Training";
    //qDebug()<<l+1<<hide_mapsY.size();

    changeWeight(current_hide_delta,hideLayer_1_n[l],hideLayer_n[l],hideLayer_n_1[l],hide_maps_Y[l]);
    qDebug()<<4<<"Training";
    l--;
    for(l=deapth_ofHideNetwork-2;l>=0;l--)
    {
        //qDebug()<<"l="<<l;
        findDelta(hide_maps_dY[l],hideLayer_n[l+1],next_hide_delta,current_hide_delta);
        current_hide_delta=next_hide_delta;
        for(i=0;i<current_hide_delta.size();i++)
        {
            current_hide_delta[i]=current_hide_delta[i]*diminutive_number[l];
        }
        //qDebug()<<"changeWeight";
        changeWeight(current_hide_delta,hideLayer_1_n[l],hideLayer_n[l],hideLayer_n_1[l],hide_maps_Y[l]);
    }
    //qDebug()<<++index<<"Training";

    //=================time=toEnd==========================
    SaveNewWeight();
    return E;
}

void ConvolutionalNeuralNetwork::findDelta(QVector<Matrix> &dY, QVector<NeuronM> &weight_n, QVector<Matrix> &nextDelta, QVector<Matrix> &currentDelta)
{
    static Matrix weight;
    static int i,j;
    nextDelta.resize(dY.size());
    Matrix d(currentDelta[0].w(),currentDelta[0].h());
    qDebug()<<"currentDelta"<<weight_n.size()<<currentDelta.size();
    for(int i=0;i<weight_n.size();i++)
    {
        weight=weight_n[i].weight.Reverse();
        d=d+currentDelta[i]*(weight);
    }
    /*/
    for(j=0;j<weight_n.size();j++)
    {
        weight=weight_n[j].weight.Reverse();
        nextDelta[j].Initialization(currentDelta[0].w(),currentDelta[0].h());
        for(i=0;i<currentDelta.size();i++)
        {
            nextDelta[j]=nextDelta[j]+currentDelta[i]*weight;
        }
    }
    /*/
    qDebug()<<"V"<<nextDelta.size()<<dY.size();
    for(i=0;i<nextDelta.size();i++)
    {
        nextDelta[i]=Matrix::multiplication(d,dY[i]);//nextDelta[i]
    }
}

void ConvolutionalNeuralNetwork::findDelta(NeuronV& dY, QVector<NeuronV> &weight_n, NeuronV &nextDelta, NeuronV &currentDelta)
{
    nextDelta.data.clear();
    nextDelta.data.resize(dY.data.size());
    static int j,k;
    for(j=0;j<nextDelta.data.size();j++)
    {
        for(k=0;k<weight_n.size();k++)
        {
            nextDelta[j]+=currentDelta[k]*weight_n[k][j];
        }
        nextDelta[j]*=dY[j];
    }
}

void ConvolutionalNeuralNetwork::changeWeight(NeuronV& delta,QVector<NeuronV>& weight_1_n,QVector<NeuronV>& weight_n,QVector<NeuronV>& weight_n_1,NeuronV& Y)
{
    static int i,j;
    weight_n_1=weight_n;
    double d;
    for(j=0;j<weight_n_1.size();j++)
    {
        for(i=0;i<weight_n_1[j].data.size();i++)
        {
            d=alpha*weight_1_n[j][i]+eta*delta[j]*Y[i];
            weight_n_1[j][i]=weight_n[j][i]+d;
            weight_1_n[j][i]=d;
        }
        d=alpha*weight_1_n[j].b+eta*delta[j];
        weight_n_1[j].b=weight_n[j].b+d;
        weight_1_n[j].b=d;
    }
}

void ConvolutionalNeuralNetwork::changeWeight(QVector<Matrix> &delta, QVector<NeuronM> &weight_1_n, QVector<NeuronM> &weight_n, QVector<NeuronM> &weight_n_1, QVector<Matrix> &Y)
{
    //qDebug()<<"^^";
    static int j,i,x,y,dx,dy;
    static double d;
    static Matrix midD,midY,m;
    int w=weight_n[0].weight.w();
    int h=weight_n[0].weight.h();
    int w2=w/2;
    int h2=h/2;
    weight_n_1.clear();
    weight_n_1.resize(weight_n.size());
    for(int i=0;i<weight_n.size();i++)
    {
        weight_n_1[i].weight=weight_n[i].weight;
    }
    //qDebug()<<"Oks";
    /*/
    static double n;
    j=0;
    midY=Y[j].lazy_middel(weight_n_1[j].weight.w(),weight_n_1[j].weight.h());
    n=1;
    //qDebug()<<"Oks";
    int _w=weight_n_1[0].weight.w();
    int _h=weight_n_1[0].weight.h();
    for(j=1;j<Y.size();j++)
    {
        m=Y[j].lazy_middel(_w,_h);
        //qDebug()<<m.toString();
        for(x=0;x<_w;x++)
            for(y=0;y<_h;y++)
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
                d=alpha*weight_1_n[j][y][x]+eta*midD[y][x]*midY[y][x];
                weight_n_1[j][y][x]=weight_n[j][y][x]+d;
                weight_1_n[j][y][x]=d;
            }
        d=alpha*weight_1_n[j].weight.b+eta*midD[weight_n[j].weight.h()/2+1][weight_n[j].weight.w()/2+1];
        weight_n_1[j].weight.b+=d;
        weight_1_n[j].weight.b=d;
    }
    //qDebug()<<"end";
    //

    Matrix dw;
    Matrix D;
    Matrix E(weight_n_1[0].weight.w(),weight_n_1[0].weight.h());
    for(dx=0;dx<weight_n_1[0].weight.w();dx++)
        for(dy=0;dy<weight_n_1[0].weight.h();dy++)
        {
            E[dx][dy]=1;
        }
    for(j=0;j<weight_n_1.size();j++)
    {
        dw.Initialization(Y[0].w(),Y[0].h());
        D=delta[j]*E;
        for(i=0;i<Y.size();i++)
        {
            dw=dw+Matrix::multiplication(Y[i],D);
        }
        dw=dw.lazy_sum(E.w(),E.h());
        for(x=0;x<weight_n_1[j].weight.w();x++)
            for(y=0;y<weight_n_1[j].weight.h();y++)
            {
                d=alpha*weight_1_n[j][y][x]+eta*dw[y][x];
                weight_n_1[j][y][x]=weight_n[j][y][x]+d;
                weight_1_n[j][y][x]=d;
            }
        d=alpha*weight_1_n[j].weight.b+eta*dw[E.h()/2][E.w()/2];
        weight_n_1[j].weight.b+=d;
        weight_1_n[j].weight.b=d;
    }
    /*/
    double dw;
    double n;
    for(j=0;j<weight_n.size();j++)
    {
        for(dx=-w2;dx<=w2;dx++)
        {
            for(dy=-h2;dy<=h2;dy++)
            {
                weight_n_1[j][dy+h2][dx+w2]=0;
                dw=0;
                n=0;
                for(i=0;i<Y.size();i++)
                {
                    dw=dw*(n/(n+1))+Matrix::scal_multiplication_mid(Y[i],delta[j],dx,dy)/(n+1);
                    n++;
                }
                dw*=eta;
                dw+=weight_1_n[j][dy+h2][dx+w2]*alpha;
                weight_n_1[j][dy+h2][dx+w2]=weight_n[j][dy+h2][dx+w2]+dw;
                weight_1_n[j][dy+h2][dx+w2]=dw;
            }
            dw=delta[j].mid()*eta+weight_1_n[j].weight.b*alpha;
            weight_n_1[j].weight.b=weight_n[j].weight.b+dw;
            weight_1_n[j].weight.b=dw;
        }

    }
}


void ConvolutionalNeuralNetwork::SaveNewWeight()
{
    for(int j=0;j<hideLayer_1_n[0].size();j++)
    {
        //qDebug()<<"dhide Layer"<<hideLayer_1_n[0][j].weight.toString();
    }
    for(int l=0;l<hideLayer_n.size();l++)
    {
        //qDebug()<<"Hide Layer"<<l<<fullLayer_n[l].first().data;
        //qDebug()<<"dHide Layer"<<l<<hideLayer_1_n[l].first().weight.toString();
        for(int j=0;j<hideLayer_n[l].size();j++)
        {
            //hideLayer_1_n[l][j].weight=hideLayer_n[l][j].weight;
            hideLayer_n[l][j].weight=hideLayer_n_1[l][j].weight;
            //hideLayer_1_n[l][j].Save();
            hideLayer_n[l][j].Save();
        }
    }
    for(int l=0;l<fullLayer_n.size();l++)
    {
        qDebug()<<"Full Layer"<<l<<fullLayer_n[l].first().data;
        qDebug()<<"dFull Layer"<<l<<fullLayer_1_n[l].first().data;
        for(int j=0;j<fullLayer_n[l].size();j++)
        {
            //fullLayer_1_n[l][j].data=fullLayer_n[l][j].data;
            fullLayer_n[l][j].data=fullLayer_n_1[l][j].data;
            //fullLayer_1_n[l][j].Save();
            fullLayer_n[l][j].Save();
        }
    }
}

void ConvolutionalNeuralNetwork::Ini()
{
    for(int l=0;l<hideLayer_n.size();l++)
    {
        for(int j=0;j<hideLayer_n[l].size();j++)
        {
            hideLayer_n[l][j].Ini();
        }
    }
    for(int l=0;l<fullLayer_n.size();l++)
    {
        for(int j=0;j<fullLayer_n[l].size();j++)
        {
            fullLayer_n[l][j].Ini();
        }
    }
}

//===============================================================QThread==================
void ConvolutionalNeuralNetwork::run()
{
    //qDebug()<<thread();
    forever
    {
        //exec();
    }
}
void ConvolutionalNeuralNetwork::Slot_End_Training()
{
    endTraining=true;
}

void ConvolutionalNeuralNetwork::Slot_Update_Alpha_Eta(double al, double e)
{
    alpha=al;
    eta=e;
}

void ConvolutionalNeuralNetwork::Slot_Evolve(Image *image)
{
    //qDebug()<<"isFinished?"<<isFinished();
    QVector<double> vec=(Evolve(image));
    EvolveEnd(vec);
}

void ConvolutionalNeuralNetwork::Slot_Training(Image *image, QVector<double> d)
{
    if(endTraining)
    {
        endTraining=false;
        return;
    }
    double E=Training(image,d);
    TrainingEnd(E);
}


