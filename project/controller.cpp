#include "controller.h"

Controller::Controller(QApplication* _app):app(_app),TimeToPauseTraining(false)
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

    QObject::connect(&training,SIGNAL(Save()),this,SLOT(Save_trainingM()));
    QObject::connect(this,SIGNAL(IniTraining()),&training,SLOT(Slot_Ini()));
    QObject::connect(this,SIGNAL(PlusETraining()),&training,SLOT(Slot_plusE()));
    QObject::connect(this,SIGNAL(Alpha_EtaUpdate(double,double)),&training,SLOT(Slot_Alpha_Eta(double,double)));

    QObject::connect(&training,SIGNAL(Update_Alpha(double)),this,SLOT(SlotAlphaChanged(double)));
    QObject::connect(&training,SIGNAL(Update_Eta(double)),this,SLOT(SlotEtaChanged(double)));

    Slot_Show(0);
    ini_vector_of_classes_name();

    Load_speed();
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
    Number_of_TrainImage=loader.Load_Queue("Training.txt");
    Load_speed();
    int start;
    if(!RandomStartTrainingTime)
    {
        if(Number_of_TrainImage==0)
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
            Number_of_TrainImage=loader.size();
            start=0;
        }
        else
        {
            start=Number_of_TrainImage-loader.size();
        }
    }
    else
    {
        QStringList list=loader.getAllFiles(pathTrainingImage);
        loader.addFiles(list,-1,true);
        Number_of_TrainImage=loader.size();
        start=0;
    }
    Image* image=loader.takepointer();
    QString name=getName_of_Classes(image->getPath());
    while(name.isEmpty())
    {
        delete image;
        if(loader.size()==0)
        {
            if(!RandomStartTrainingTime)
                return;
            PlusETraining();
            QStringList list=loader.getAllFiles(pathTrainingImage);
            loader.addFiles(list,-1,true);
            index_of_current_Image=-1;
        }
        image=loader.takepointer();
        name=getName_of_Classes(image->getPath());
    }
    QVector<double> d=getVofDouble(name);
    IniTraining();
    StartTraining(image,d);
    index_of_current_Image=start;
    training.ChangeProgress(index_of_current_Image*100/Number_of_TrainImage);
    Update_speed();



    /*/
    QTime timer;
    for(int i=start;i<Number_of_TrainImage;i++)
    {
        training.ChangeProgress(i*100/Number_of_TrainImage);
        timer.start();
        loader.take();
        while(timer.elapsed()<1000)
        {
            app->processEvents();
        }
    }
    training.ChangeProgress(100);
    /*/
}

void Controller::StartTest()
{
    Slot_Show(3);
    current_size=loader.size();
    Image* image=loader.takepointer();
    imageF.setImage(*image);
    index_of_current_Image=1;
    imageF.setProgress(index_of_current_Image,current_size);
    imageF.setEnablNext(false);
    imageF.setClasses(2,"Hello World",0.33);
    StartEvolve(image);
    qDebug()<<"lazy timing";
}

void Controller::NextImage()
{
    Image* image=loader.takepointer();
    imageF.setImage(*image);
    imageF.setProgress(++index_of_current_Image,current_size);
    StartEvolve(image);
    imageF.setEnablNext(false);
}

void Controller::PreviousImage()
{

}

void Controller::Save_trainingM()
{
    loader.Save_Queue("Training.txt",Number_of_TrainImage);
    TimeToPauseTraining=true;
    //EndTraining();
}

void Controller::SlotEvolveEnd(QVector<double> d)
{
    if(index_of_current_Image<current_size)
        imageF.setEnablNext(true);
    double last_max=1,current_max=-1,index_of_max=-1;
    for(int i=1;i<=5;i++)
    {
        for(int j=0;j<d.size();j++)
        {
            if(current_max<d[j]&&d[j]<=last_max)
            {
                current_max=d[j];
                index_of_max=j;
            }
        }
        if(index_of_max==-1)
        {
            qDebug()<<"Something wrong:SlotEvolveEnd class Controller";
        }
        else
        {
            //qDebug()<<"current_max"<<current_max;
            imageF.setClasses(i,classes_name[index_of_max],current_max);
            d[index_of_max]=2;
            last_max=current_max;
            current_max=-1;
            index_of_max=-1;
        }
    }
}

void Controller::SlotTrainingEnd(double E)
{
    if(TimeToPauseTraining)
    {
        TimeToPauseTraining=false;
        return;
    }
    list_of_E<<E;
    if(list_of_E.size()>100)
    {
        list_of_E.removeFirst();
    }
    double E10=100,E100=100;
    for(int i=list_of_E.size()-1;i>=0&&i>=list_of_E.size()-9;i--)
    {
        if(list_of_E[i]<E10)
        {
            E10=list_of_E[i];
        }
    }
    for(int i=list_of_E.size()-1;i>=0;i--)
    {
        if(list_of_E[i]<E100)
        {
            E100=list_of_E[i];
        }
    }
    training.setE(E,E10,E100);

    if(loader.size()==0)
    {
        PlusETraining();
        QStringList list=loader.getAllFiles(pathTrainingImage);
        loader.addFiles(list,-1,RandomNewEra);
        index_of_current_Image=-1;
    }
    Image* image=loader.takepointer();
    QString name=getName_of_Classes(image->getPath());
    while(name.isEmpty())
    {
        delete image;
        if(loader.size()==0)
            return;
        image=loader.takepointer();
        name=getName_of_Classes(image->getPath());
    }
    QVector<double> d=getVofDouble(name);
    StartTraining(image,d);
    training.ChangeProgress(++index_of_current_Image*100/Number_of_TrainImage);
    //Update_speed();
}
void Controller::ini_vector_of_classes_name()
{
    QFile file(pathNeuronWeight+"/Name_of_classes.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&file);
        QString line;
        int i=0;
        line=in.readLine();
        while(!line.isNull())
        {
            classes_name<<line;
            reg_for_classes_name<<QRegExp(line);
            line=in.readLine();
        }

    }
    else
    {
        qDebug()<<"Something wrong:file \"Name_of_classes.txt\" doesnt exist ";
    }
    qDebug()<<"classes_name"<<classes_name;
    return;
    QDir d(pathNeuronWeight);
    QStringList filters;
    d.setNameFilters(filters);
    QStringList flist=d.entryList();
    QRegExp r("^[a-z ]+$");
    foreach(QString name,flist)
    {
        if(name.contains(r))
        {
            classes_name<<name;
            reg_for_classes_name<<QRegExp(name);
        }
    }
}

void Controller::Save_speed()
{
    QFile file(pathLoader+"/Speed.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream out(&file);
        out<<number_of_Image<<"\n";
        out<<AlphaIndex<<"\n";
        out<<EtaIndex<<"\n";
        out<<current_speed_of_alpha<<"\n";
        out<<current_speed_of_eta<<"\n";
        out<<alpha<<"\n";
        out<<eta<<"\n";
    }
    else
    {
        qDebug()<<"Something wrong:file \"speed.txt\" doesnt exist ";
    }
    file.close();
}

void Controller::Load_speed()
{
    QFile file(pathLoader+"/Speed.txt");
    if(!file.exists())
        return;
    QString text;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        text=file.readLine();
        qDebug()<<text;
        number_of_Image=text.toInt();

        text=file.readLine();
        qDebug()<<text;
        AlphaIndex=text.toInt();

        text=file.readLine();
        qDebug()<<text;
        EtaIndex=text.toInt();

        text=file.readLine();
        qDebug()<<text;
        current_speed_of_alpha=text.toDouble();

        text=file.readLine();
        qDebug()<<text;
        current_speed_of_eta=text.toDouble();

        text=file.readLine();
        qDebug()<<text;
        alpha=text.toDouble();

        text=file.readLine();
        qDebug()<<text;
        eta=text.toDouble();

        Alpha_EtaUpdate(alpha,eta);
        qDebug()<<"==================================================="<<alpha<<eta;
    }
    else
    {
        qDebug()<<"Something wrong:file \"speed.txt\" doesnt exist ";
    }
    file.close();
}

void Controller::Ini_speed()
{
    number_of_Image=0;
    AlphaIndex=EtaIndex=-1;
    alpha=start_alpha;
    eta=start_eta;
    Save_speed();
    Alpha_EtaUpdate(alpha,eta);
}

void Controller::Update_speed()
{
    number_of_Image++;
    if(AlphaIndex==-1)
    {
        AlphaIndex++;
        current_speed_of_alpha=(speed_of_alpha[AlphaIndex][0]-alpha)/(speed_of_alpha[AlphaIndex][1]*Number_of_TrainImage-number_of_Image);
    }
    if(AlphaIndex<size_of_alpha)
    {
        if(number_of_Image/Number_of_TrainImage>=speed_of_alpha[AlphaIndex][1])
        {
            AlphaIndex++;
            if(AlphaIndex<size_of_alpha)
            {
                current_speed_of_alpha=(speed_of_alpha[AlphaIndex][0]-alpha)/((int)(speed_of_alpha[AlphaIndex][1]*Number_of_TrainImage)-number_of_Image);
            }
        }
        alpha+=current_speed_of_alpha;
    }
    else
    {
        alpha=speed_of_alpha[size_of_alpha-1][0];
    }
    if(EtaIndex==-1)
    {
        EtaIndex++;
        current_speed_of_eta=(speed_of_eta[EtaIndex][0]-eta)/((int)(speed_of_eta[EtaIndex][1]*Number_of_TrainImage)-number_of_Image);
    }
    if(EtaIndex<size_of_eta)
    {
        if(number_of_Image/Number_of_TrainImage>=speed_of_eta[EtaIndex][1])
        {
            EtaIndex++;
            if(EtaIndex<size_of_eta)
            {
                current_speed_of_eta=(speed_of_eta[EtaIndex][0]-eta)/((int)(speed_of_eta[EtaIndex][1]*Number_of_TrainImage)-number_of_Image);
            }
        }
        eta+=current_speed_of_eta;
    }
    else
    {
        eta=speed_of_eta[size_of_eta][0];
    }
    Alpha_EtaUpdate(alpha,eta);
    Save_speed();
}

QString Controller::getName_of_Classes(QString path)
{
    for(int i=0;i<classes_name.size();i++)
    {
        if(path.contains(reg_for_classes_name[i]))
            return classes_name[i];
    }
    return "";
}

QVector<double> Controller::getVofDouble(QString path)
{
    QVector<double> vec(classes_name.size(),0);
    for(int i=0;i<classes_name.size();i++)
    {
        if(path.contains(reg_for_classes_name[i]))
        {
            vec[i]=1;
            return vec;
        }

    }
    return vec;
}

void Controller::SlotEtaChanged(double e)
{
    eta=e;
    Alpha_EtaUpdate(alpha,eta);
}

void Controller::SlotAlphaChanged(double al)
{
    alpha=al;
    Alpha_EtaUpdate(alpha,eta);
}
