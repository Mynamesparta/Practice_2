#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T15:11:35
#
#-------------------------------------------------

QT       += core gui

TARGET = Practice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matrix.cpp \
    NeuronClasses//convolutional_neural_network.cpp \
    #neuralnetwork.cpp \
    NeuronClasses//neuron.cpp \
    NeuronClasses//searcher.cpp \
    ImageController//image.cpp \
    ImageController/loader.cpp

HEADERS  += mainwindow.h \
    matrix.h \
    World_of_Const.h \
    NeuronClasses//convolutional_neural_network.h \
    #neuralnetwork.h \
    NeuronClasses//neuron.h \
    NeuronClasses//searcher.h \
    ImageController//image.h \
    ImageController/loader.h

FORMS    += mainwindow.ui
