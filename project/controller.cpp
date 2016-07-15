#include "controller.h"

Controller::Controller(QApplication* _app):app(_app)
{
    QObject::connect(&main,SIGNAL(ShowMustGoOn(int)),this,SLOT(Slot_Show(int)));
    QObject::connect(&training,SIGNAL(ShowMustGoOn(int)),this,SLOT(Slot_Show(int)));
    QObject::connect(&test,SIGNAL(ShowMustGoOn(int)),this,SLOT(Slot_Show(int)));
    QObject::connect(&imageF,SIGNAL(ShowMustGoOn(int)),this,SLOT(Slot_Show(int)));

    QObject::connect(&test,SIGNAL(Loadinfo(int,int,bool)),this,SLOT(Slot_TestLoad(int,int,bool)));
    QObject::connect(&test,SIGNAL(Loadinfo(QStringList)),this,SLOT(Slot_TestLoad(QStringList)));

    QObject::connect(this,SIGNAL(StartTraining()),this,SLOT(Start()));

    QObject::connect(&imageF,SIGNAL(Next()),this,SLOT(NextImage()));
    QObject::connect(&imageF,SIGNAL(Previous()),this,SLOT(PreviousImage()));

    Slot_Show(0);
}

void Controller::Slot_Show(int i)
{
    switch(i)
    {
    case 0:
        main.show();
        training.hide();
        test.hide();
        imageF.hide();
        break;
    case 1:
        main.hide();
        training.show();
        test.hide();
        imageF.hide();
        StartTraining();
        break;
    case 2:
        main.hide();
        training.hide();
        test.show();
        imageF.hide();
        break;
    case 3:
        main.hide();
        training.hide();
        test.hide();
        imageF.show();
        break;
    }
}

void Controller::Slot_TestLoad(int dir, int number, bool random)
{
    qDebug()<<"Dir";
    QStringList list;
    switch(dir)
    {
    case 0:
        list=loader.getAllFiles(pathTrainingImage);
        break;
    case 1:
        list=loader.getAllFiles(pathTestImage);
        break;
    }
    loader.addFiles(list,(number==0?-1:number),random);
    StartTest();
}

void Controller::Slot_TestLoad(QStringList list)
{
    qDebug()<<"List";
    loader.addFiles(list);
    StartTest();
}

void Controller::Start()
{
    loader.Clear();
    QVector<QStringList> list=loader.getAllClassesFiles(pathTrainingImage);
    int i=0;
    int j=0;
    bool TimeToEnd=true;
    forever
    {
        if(j>=list.size())
        {
            if(TimeToEnd)
                break;
            j=0;
            i++;
            TimeToEnd=true;
            continue;
        }
        if(i<list[j].size())
        {
            loader.addFile(list[j][i]);
            TimeToEnd=false;
        }
        j++;
    }
    int Number_of_TrainImage=loader.size();
    QTime timer;
    for(int i=0;i<Number_of_TrainImage;i++)
    {
        training.ChangeProgress(i*100/Number_of_TrainImage);
        timer.start();
        while(timer.elapsed()<1000)
        {
            app->processEvents();
        }
    }
    training.ChangeProgress(100);
}

void Controller::StartTest()
{
    Slot_Show(3);
    current_size=loader.size();
    Image image=loader.take();
    imageF.setImage(image);
    index_of_currentImage=1;
    imageF.setProgress(index_of_currentImage,current_size);
    imageF.setEnablNext(true);
    imageF.setClasses(2,"Hello World",0.33);
}

void Controller::NextImage()
{
    Image image=loader.take();
    imageF.setImage(image);
    imageF.setProgress(++index_of_currentImage,current_size);
    if(index_of_currentImage==current_size)
        imageF.setEnablNext(false);
}

void Controller::PreviousImage()
{

}
