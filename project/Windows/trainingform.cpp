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
