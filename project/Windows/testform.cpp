#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),dialog(this),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
    ui->TestButton->setEnabled(false);
    ui->ChooseButton->hide();
    ui->Options->hide();
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::on_BackButton_clicked()
{
    ShowMustGoOn(0);
}

void TestForm::on_Number_of_File_textChanged(const QString &arg1)
{
    QString text=arg1;
    text.replace(QRegExp("[^0-9]"),"");
    ui->Number_of_File->setText(text);
    if(text.isEmpty())
    {
        ui->TestButton->setEnabled(false);
    }
    else
        ui->TestButton->setEnabled(true);

}

void TestForm::on_ChooseradioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->ChooseButton->show();
        ui->TestButton->setEnabled(true);
        ui->Options->hide();
    }
}

void TestForm::on_Training_ImageradioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->ChooseButton->hide();
        ui->Options->show();
        ui->TestButton->setEnabled(!ui->Number_of_File->text().isEmpty());
    }
}

void TestForm::on_Test_ImageradioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->ChooseButton->hide();
        ui->Options->show();
        ui->TestButton->setEnabled(!ui->Number_of_File->text().isEmpty());
    }
}

void TestForm::on_ChooseButton_clicked()
{
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
        inputlist=dialog.selectedFiles();
}

void TestForm::on_TestButton_clicked()
{
    if(ui->Training_ImageradioButton->isChecked())
    {
        Loadinfo(0,(ui->Number_of_File->text()).toInt(),ui->RandomTimecheckBox->isChecked());
    }
    if(ui->Test_ImageradioButton->isChecked())
    {
        Loadinfo(1,(ui->Number_of_File->text()).toInt(),ui->RandomTimecheckBox->isChecked());
    }
    if(ui->ChooseradioButton->isChecked())
    {
        Loadinfo(inputlist);
    }
}
