#include "tsetupform.h"
#include "ui_tsetupform.h"
#include "SQLmodule.h"

TSetupForm::TSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TSetupForm)
{
    ui->setupUi(this);


    IniSettings *INIFile = new IniSettings;

    ui->MinBox->setValue((double)INIFile->GetParam("Plot/Ymin")/10);
    ui->MaxBox->setValue((double)INIFile->GetParam("Plot/Ymax")/10);
    ui->MinSpeed->setValue((double)INIFile->GetParam("Plot/SYmin")/10);
    ui->MaxSpeed->setValue((double)INIFile->GetParam("Plot/SYmax")/10);
    ui->HowManyHours->setValue(INIFile->GetParam("Plot/Xhours"));
    ui->AverageRowMin->setValue(INIFile->GetParam("Main/AverageRow"));
    UpdateMinMax();

    delete(INIFile);
}

TSetupForm::~TSetupForm()
{
    delete ui;
}


void TSetupForm::on_SaveButton_clicked()
{
    IniSettings *INIFile = new IniSettings;
    INIFile->SetParam("Plot/Ymin",ui->MinBox->value()*10);
    INIFile->SetParam("Plot/Ymax",ui->MaxBox->value()*10);
    INIFile->SetParam("Plot/SYmin",ui->MinSpeed->value()*10);
    INIFile->SetParam("Plot/SYmax",ui->MaxSpeed->value()*10);
    INIFile->SetParam("Plot/Xhours",ui->HowManyHours->value());
    INIFile->SetParam("Main/AverageRow",ui->AverageRowMin->value());

    delete(INIFile);

    this->close();
}

void TSetupForm::UpdateMinMax()
{
ui->MaxBox->setMinimum(ui->MinBox->value()+0.1);
ui->MinBox->setMaximum(ui->MaxBox->value()-0.1);
}

void TSetupForm::on_MinBox_valueChanged(double arg1)
{
UpdateMinMax();
}

void TSetupForm::on_MaxBox_valueChanged(const QString &arg1)
{
UpdateMinMax();
}

void TSetupForm::on_SaveButton_2_clicked()
{this->close();
}
