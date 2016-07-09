#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork():dir(Direction_of_NeuralNetwork)
{
    qDebug()<<dir.path();
    if(dir.exists())
    {
        QStringList filters;
        filters<<"*.txt";
        dir.setNameFilters(filters);
        QFileInfoList list=dir.entryInfoList();
        QFileInfo fileinfo;
        for(int i=0;i<list.size();i++)
        {
            fileinfo=list.at(i);
            qDebug()<<"Load:"<<fileinfo.fileName();
            neurons.push_back(new Neuron(Direction_of_NeuralNetwork,fileinfo.fileName()));
        }
    }
    else
    {
        qDebug()<<"Something wrong: Dir doesnt exists!";
    }
    for(int i=0;i<size_of_symbol;i++)
    {
        for(int j=0;j<size_of_symbol;j++)
            if(i==j)
                input[i][i]=1;
            else
                input[i][j]=0;
    }
    //
    //Restart();
}


void NeuralNetwork::Load(vector<PicObject *> vec)
{
    int j,i;
    vector<PicObject*>::iterator iter=vec.begin();
    PicObject* pic;
    for(i=0;i<size_of_symbol;i++)
    {
        for(j=0;j<size_of_symbol;j++)
        {
            pic=*iter;
            input[i][j]=(pic->colorR.red>=128?0:1);
            iter++;
            if(iter==vec.end())
                return;
        }
    }
}

void NeuralNetwork::Load(vector<short> & vec)
{
    int i,j;
    vector<short>::iterator iter=vec.begin();
    short s;
    for(i=0;i<size_of_symbol;i++)
        for(j=0;j<size_of_symbol;j++)
        {
            s=*iter;
            input[i][j]=s;
            iter++;
            if(iter==vec.end())
                return;
        }
}

void NeuralNetwork::Load(short in[World_of_Const::size_of_symbol][World_of_Const::size_of_symbol])
{
    for(int i=0;i<World_of_Const::size_of_symbol;i++)
        for(int j=0;j<World_of_Const::size_of_symbol;j++)
            input[i][j]=in[i][j];
}

void NeuralNetwork::Restart()
{
    //return;
    vector<Neuron*>::iterator iter=neurons.begin();
    Neuron* cur_neuron;
    for(;iter!=neurons.end();iter++)
    {
        cur_neuron=*iter;
        cur_neuron->Restart();
    }

}

QString NeuralNetwork::FindSymbol()
{
    vector<Neuron*>::iterator iter=neurons.begin();
    Neuron* cur_neuron;
    Neuron* best_neuron=0;
    int curSum;
    int maxSum=-10000000;
    for(;iter!=neurons.end();iter++)
    {
        cur_neuron=*iter;
        curSum=cur_neuron->FindSume(input);
        if(curSum>maxSum)
        {
            maxSum=curSum;
            best_neuron=cur_neuron;
        }
    }
    if(best_neuron==0)
        return "";
    return best_neuron->name;
}

QString NeuralNetwork::TimeToTraining()
{
    QString neuronsAnswer=FindSymbol();
    QString trainerAnswer=window.ShowMustGoOn(input,neuronsAnswer);
    if(trainerAnswer=="Fail")
    {
        qDebug()<<"Time to Fail";
        return "~";
    }
    Neuron* n;
    if(trainerAnswer!=neuronsAnswer)
    {
        n=FindNeuron(neuronsAnswer);
        if(n==0)
            qDebug()<<"Something wrong in metod TimeToTraining: n==0";
        else
            (*n)-=input;
        n=FindNeuron(trainerAnswer);
        if(n==0)
            qDebug()<<"Something wrong in metod TimeToTraining: n==0";
        else
            (*n)+=input;
    }
    else
    {
        //n=FindNeuron(neuronsAnswer);
        //(*n)+=input;
    }
    return trainerAnswer;
}

Neuron* NeuralNetwork::FindNeuron(QString name)
{
    vector<Neuron*>::iterator iter=neurons.begin();
    Neuron* cur_neuron;
    for(;iter!=neurons.end();iter++)
    {
        cur_neuron=*iter;
        if(cur_neuron->name==name)
            return cur_neuron;
    }
    return 0;
}

void NeuralNetwork::Paint(Image &image,QString name="")
{
    image.setImage(input,name);
    //image.save("NeuralNetwork");
}


//============================================Neural==========================

Neuron::Neuron(QString dir,QString name):dir(dir),name(name.replace(".txt",""))
{
    qDebug()<<name.replace(".txt","");
    QFile file(dir+name+".txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    QString line;
    QStringList stringlist;
    int i=0;
    do
    {
        line=in.readLine();
        if(line=="")
            continue;
        stringlist=line.split(" ");
        for(int j=0;j<stringlist.size();j++)
        {
            if(j==size_of_symbol)
                break;
            if(stringlist[j]!="")
            {
                weight[i][j]=stringlist[j].toInt();
            }
        }
        i++;
        if(i==size_of_symbol)
            break;

    }
    while(!line.isNull());

    QString text;
    for(int i=0;i<size_of_symbol;i++)
    {
        text="";
        for(int j=0;j<size_of_symbol;j++)
            text+=QString::number(weight[i][j])+" ";
        //qDebug()<<text;
    }
    file.close();
    qDebug()<<"---------------------------------";
    Save();

}

void Neuron::Save()
{
    QFile file(dir+name+".txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);

    for(int i=0;i<size_of_symbol;i++)
    {
        for(int j=0;j<size_of_symbol;j++)
        {
            out<<QString::number(weight[i][j])<<" ";
        }
        out<<"\n";
    }
    file.close();

}

void Neuron::Restart()
{
    //return;
    for(int i=0;i<size_of_symbol;i++)
    {
        for(int j=0;j<size_of_symbol;j++)
        {
            weight[i][j]=0;
        }

    }
    Save();
}

int Neuron::FindSume(short (*input)[size_of_symbol])
{
    static int i,j,sum;
    sum=0;
    for(i=0;i<size_of_symbol;i++)
    {
        for(j=0;j<size_of_symbol;j++)
        {
            sum+=input[i][j]*weight[i][j];
        }
    }
    return sum;
}

Neuron& Neuron::operator +=(short (*input)[size_of_symbol])
{
    static int i,j;
    for(i=0;i<size_of_symbol;i++)
        for(j=0;j<size_of_symbol;j++)
            weight[i][j]+=input[i][j];
    this->Save();
    return *this;
}

Neuron& Neuron::operator -=(short (*input)[size_of_symbol])
{
    static int i,j;
    for(i=0;i<size_of_symbol;i++)
        for(j=0;j<size_of_symbol;j++)
            weight[i][j]-=input[i][j];
    this->Save();
    return *this;
}

Neuron& Neuron::operator =(Neuron& B)
{
    if(this==&B)
        return *this;
    static int i,j;
    for(i=0;i<size_of_symbol;i++)
        for(j=0;j<size_of_symbol;j++)
            weight[i][j]=B.weight[i][j];
    name=B.name;
    dir=B.dir;
    this->Save();
    return *this;
}
/*/
Neuron& Neuron::operator +=(short (*input)[size_of_symbol])
{
    *this=*this+input;
    return *this;
}

Neuron& Neuron::operator -=(short (*input)[size_of_symbol])
{
    *this=*this-input;
    return *this;
}
/*/

