#include <QtGui/QApplication>
#include "mainwindow.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "NeuronClasses/searcher.h"
#include "NeuronClasses/convolutional_neural_network.h"
#include "ImageController/loader.h"
#include "ImageController/image.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    //ConvolutionalNeuralNetwork cnn;
    Loader l;
    //
    l.add(pathTrainingImage+"dog",-1,true);
    l.take();
    l.take();
    l.take();
    /*/
    Matrix m(4,1);
    for(int i=0;i<1;i++)
        for(int j=0;j<4;j++)
        {
            m[i][j]=j;
        }
    qDebug()<<m.toString();
    Image i;
    i.red=m;
    i.green=m;
    i.blue=m;
    i.resize(6,1);
    qDebug()<<i.red.toString();
    /*/

    return 0;
    return a.exec();
}
