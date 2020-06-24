#include "sqlfilter.h"
#include "ui_sqlfilter.h"

SQLFilter::SQLFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLFilter)
{
    ui->setupUi(this);
    ui->ToValue->setDateTime(QDateTime::currentDateTime());
    ui->FromValue->setDateTime(QDateTime::currentDateTime().addSecs(-2*60*60));

}

SQLFilter::~SQLFilter()
{
    delete ui;
}

void SQLFilter::on_pushButton_clicked()
{
    IniSettings *INIFile = new IniSettings;
    INIFile->SetParamStr("FilterSQL/From",ui->FromValue->dateTime().toString(Qt::ISODate));
    INIFile->SetParamStr("FilterSQL/To",ui->ToValue->dateTime().toString(Qt::ISODate));
    INIFile->SetParam("FilterSQL/Enabled",1);
    INIFile->SetParam("FilterSQL/Do",1);
    delete(INIFile);

    this->close();
}

void SQLFilter::on_pushButton_2_clicked()
{
    this->close();

}
