#ifndef WORLD_OF_CONST_H
#define WORLD_OF_CONST_H
#include <QString>
#include "cstdlib"
#include "math.h"
namespace World_of_Const
{
    const int step_of_WeightM=1;
    //const int height_ofNetwork=3;
    const int w_of_Neuron=5;
    const int h_of_Neuron=5;

    const QString pathNeuronWeight="debug/NeuronWeight/";
    const QString pathTrainingImage="debug/Image/Training/";
    const QString pathTestImage="debug/Image/Test/";
    const QString pathLoader="debug/Loader/";
    const QString pathTemp="debug/Temp/";

    const int deapth_ofHideNetwork=4;
    const int number_of_neuron_inHideLayer[]={4,10,16,20};
    const int deapth_ofFullNetwork=3;
    const int number_of_neuron_inFullLayer[]={18,18,9};
    const int diminutive_number[]={4,4,4,5};
    const int size_of_neuron_inHideLayer[]={5,5,3,3};
    const int size_of_neuron_inFullLayer[]={20,18,18};
    const double IniA=-0.05;
    const double IniB=-IniA;

    const bool TimeForTemp=false;
    const bool RandomStartTrainingTime=false;
    const bool RandomNewEra=true;

    const int w_of_inputImage=320;
    const int h_of_inputImage=320;

    const double start_eta=0.2;
    const double start_alpha=0.5;
    const int size_of_eta=9;
    const int size_of_alpha=9;
    const double speed_of_eta[size_of_eta][2]={{0.1,0.2},{0.05,0.8},{0.03,1.1},{0.1,1.5},{0.03,2},{0.1,2.5},{0.03,3},{0.1,3.5},{0.03,4}};
    const double speed_of_alpha[size_of_alpha][2]={{0.3,0.3},{0.1,0.8},{0.05,1.1},{0.3,1.5},{0.05,2},{0.3,2.5},{0.05,3},{0.3,3.5},{0.05,4}};



    static int randInt(double a,double b)
    {
        b++;
        b-=0.000000001;
        double r=rand();
        return a+r/RAND_MAX*(b-a);
    }
    static double randDouble(double a,double b)
    {
        double r=rand();
        return a+r/RAND_MAX*(b-a);
    }
    const double two_thirds=(double)2/3;
    static inline double f(double x)
    {
        //qDebug()<<two_thirds;
        return 1.7159*tanh(x*two_thirds);
        return 1/(1+exp(-x));
        return (x>=0?x:0.1*x);
        if(x>=0)
            return x;
        return 0.1*x;
    }

    static inline double df(double x)
    {
        double c=cosh(x*two_thirds);
        static double dem=1.7159*two_thirds;
        return dem/(c*c);
        static double d,e;
        e=exp(x);
        d=e+1;
        return e/(d*d);
        if(x>0)
            return 1;
        if(x==0)
            return 0.55;
        return 0.1;
        //
        /*/
        return (x>0?1:(x==0?0.55:0.1));
        /*/
    }
    static inline double ABS(double x)
    {
        return (x>=0?x:-x);
    }
}
#endif // WORLD_OF_CONST_H
