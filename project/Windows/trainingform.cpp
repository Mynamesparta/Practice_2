#include "trainingform.h"
#include "ui_trainingform.h"

TrainingForm::TrainingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::on_BackButton_clicked()
{
    ShowMustGoOn(0);
}

void TrainingForm::ChangeProgress(int p)
{
    ui->progressBar->setValue(p);
}

void TrainingForm::on_SaveButton_clicked()
{
    ShowMustGoOn(0);
    Save();
}

void TrainingForm::setE(double c, double t, double h)
{
    ui->lcdNumberCur->display(c);
    ui->lcdNumber10->display(t);
    ui->lcdNumber100->display(h);
}

void TrainingForm::Slot_Ini()
{
    index_of_E=1;
    ui->lcdNumberCurEra->display(index_of_E);
}

void TrainingForm::Slot_plusE()
{
    ui->lcdNumberCurEra->display(++index_of_E);
}

void TrainingForm::Slot_Alpha_Eta(double alpha,double eta)
{
    ui->lcdNumberCurAlpha->display(alpha);
    ui->lcdNumberCurEta->display(eta);
}

void TrainingForm::on_verticalSliderAlpha_sliderMoved(int position)
{
    Update_Alpha((double)position/1000);
}

void TrainingForm::on_verticalSliderEta_sliderMoved(int position)
{
    Update_Eta((double)position/1000);
}
