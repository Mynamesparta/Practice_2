#include <QtGui/QApplication>
#include "mainwindow.h"
#include "matrix.h"
#include "World_of_Const.h"
#include "NeuronClasses/searcher.h"
#include "NeuronClasses/convolutional_neural_network.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    ConvolutionalNeuralNetwork cnn;
    return 0;
    return a.exec();
}
