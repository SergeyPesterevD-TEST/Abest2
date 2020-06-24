#ifndef TSETUPFORM_H
#define TSETUPFORM_H

#include <QWidget>
#include "inisettings.h"

namespace Ui {
class TSetupForm;
}

class TSetupForm : public QWidget
{
    Q_OBJECT

public:
    explicit TSetupForm(QWidget *parent = nullptr);
    ~TSetupForm();

private slots:

    void on_SaveButton_clicked();

    void UpdateMinMax();

    void on_MinBox_valueChanged(double arg1);

    void on_MaxBox_valueChanged(const QString &arg1);

    void on_SaveButton_2_clicked();

private:
    Ui::TSetupForm *ui;
};

#endif // TSETUPFORM_H
