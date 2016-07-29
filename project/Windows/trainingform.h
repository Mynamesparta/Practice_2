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
    void setE(double c,double t=-1,double h=-1);
signals:
    void ShowMustGoOn(int i);
    void Save();
    void Update_Alpha(double a);
    void Update_Eta(double e);
private slots:
    void on_BackButton_clicked();

    void on_SaveButton_clicked();

    void Slot_Ini();

    void Slot_plusE();

    void on_verticalSliderAlpha_sliderMoved(int position);

    void on_verticalSliderEta_sliderMoved(int position);

public slots:
    void Slot_Alpha_Eta(double alpha,double eta);
private:
    Ui::TrainingForm *ui;
    int index_of_E;
};

#endif // TRAININGFORM_H
