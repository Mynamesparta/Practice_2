#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*/
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(dialog.exec())
        fileNames=dialog.selectedFiles();
    qDebug()<<fileNames;
    /*/
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_TrainingButton_clicked()
{
    ShowMustGoOn(1);
}

void MainWindow::on_TestButton_clicked()
{
    ShowMustGoOn(2);
}
