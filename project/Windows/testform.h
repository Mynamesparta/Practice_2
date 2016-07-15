#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QDebug>
#include <QRegExp>
#include <QFileDialog>
#include <QString>

namespace Ui {
    class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();
signals:
    void ShowMustGoOn(int i);
    void Loadinfo(int,int,bool);
    void Loadinfo(QStringList);
private slots:
    void on_BackButton_clicked();

    void on_Number_of_File_textChanged(const QString &arg1);

    void on_ChooseradioButton_clicked(bool checked);

    void on_Training_ImageradioButton_clicked(bool checked);

    void on_Test_ImageradioButton_clicked(bool checked);

    void on_ChooseButton_clicked();

    void on_TestButton_clicked();

private:
    Ui::TestForm *ui;
    QFileDialog dialog;
    QStringList inputlist;
};

#endif // TESTFORM_H
