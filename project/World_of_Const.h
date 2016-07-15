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

    const int deapth_ofHideNetwork=4;
    const int number_of_neuron_inHideLayer[]={16,14,12,10};
    const int deapth_ofFullNetwork=2;
    const int number_of_neuron_inFullLayer[]={10,10};
    const int diminutive_number[]={5,4,4,5};
    const int size_of_neuron_inHideLayer[]={7,5,5,3};
    const int size_of_neuron_inFullLayer[]={10,10};

    const int w_of_inputImage=400;
    const int h_of_inputImage=400;

    static int randInt(double a,double b)
    {
        b++;
        b-=0.000000001;
        double r=rand();
        return a+r/RAND_MAX*(b-a);
    }
    static inline double f(double x)
    {
        return 1/(1+exp(-x));
    }

    static inline double df(double x)
    {
        return f(x)*(1-f(x));
    }
}
#endif // WORLD_OF_CONST_H
