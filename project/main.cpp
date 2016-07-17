#include <QtGui/QApplication>
#include "controller.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "NeuronClasses/searcher.h"
#include "NeuronClasses/convolutional_neural_network.h"
#include "ImageController/loader.h"
#include "ImageController/image.h"
#include "NeuronClasses/neuronv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller con(&a);
    /*/
    Matrix b(5,5);
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            b[i][j]=i+j;
    qDebug()<<b.toString();
    qDebug()<<(b*3).toString();
    return 0;
    /*/
    return a.exec();
}
