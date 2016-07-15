#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

#include "testform.h"
#include "trainingform.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void ShowMustGoOn(int i);

private slots:
    void on_TrainingButton_clicked();

    void on_TestButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
