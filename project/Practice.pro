#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T15:11:35
#
#-------------------------------------------------

QT       += core gui

TARGET = Practice
TEMPLATE = app


SOURCES += main.cpp\
        Windows/mainwindow.cpp \
    matrix.cpp \
    NeuronClasses//convolutional_neural_network.cpp \
    #neuralnetwork.cpp \
    NeuronClasses//neuronm.cpp \
    NeuronClasses//searcher.cpp \
    NeuronClasses//neuronv.cpp\
    ImageController//image.cpp \
    ImageController/loader.cpp \
    Windows/testform.cpp \
    Windows/trainingform.cpp \
    controller.cpp \
    Windows/imageform.cpp

HEADERS  += Windows/mainwindow.h \
    matrix.h \
    World_of_Const.h \
    NeuronClasses//convolutional_neural_network.h \
    #neuralnetwork.h \
    NeuronClasses//neuronm.h \
    NeuronClasses//searcher.h \
    NeuronClasses//neuronv.h\
    ImageController//image.h \
    ImageController/loader.h \
    Windows/testform.h \
    Windows/trainingform.h \
    controller.h \
    Windows/imageform.h

FORMS    += Windows/mainwindow.ui \
    Windows/testform.ui \
    Windows/trainingform.ui \
    Windows/imageform.ui
