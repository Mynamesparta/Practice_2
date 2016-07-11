#ifndef WORLD_OF_CONST_H
#define WORLD_OF_CONST_H
#include <QString>
#include "cstdlib"
namespace World_of_Const
{
    const int step_of_WeightM=1;
    //const int height_ofNetwork=3;
    const int w_of_Neuron=5;
    const int h_of_Neuron=5;

    const QString pathNeuronWeight="debug/NeuronWeight/";
    const QString pathTrainingImage="debug/Image/Training/";
    const QString pathTestImage="debug/Image/Test/";

    const int deapth_ofNetwork=4;
    const int number_of_neuron_inLayer[]={8,8,8,8};

    const int w_of_inputImage=400;
    const int h_of_inputImage=400;

    static int randInt(double a,double b)
    {
        b++;
        b-=0.000000001;
        double r=rand();
        return a+r/RAND_MAX*(b-a);
    }
}
#endif // WORLD_OF_CONST_H
