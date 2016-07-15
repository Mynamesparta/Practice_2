#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QWidget>

namespace Ui {
    class TrainingForm;
}

class TrainingForm : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = 0);
    void ChangeProgress(int p);
    ~TrainingForm();
signals:
    void ShowMustGoOn(int i);
private slots:
    void on_BackButton_clicked();

private:
    Ui::TrainingForm *ui;
};

#endif // TRAININGFORM_H
