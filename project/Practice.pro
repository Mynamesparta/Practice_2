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
    image.cpp

HEADERS  += mainwindow.h \
    matrix.h \
    World_of_Const.h \
    NeuronClasses//convolutional_neural_network.h \
    #neuralnetwork.h \
    NeuronClasses//neuron.h \
    NeuronClasses//searcher.h \
    image.h

FORMS    += mainwindow.ui
