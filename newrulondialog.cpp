#include "newrulondialog.h"
#include "ui_newrulondialog.h"

NewRulonDialog::NewRulonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRulonDialog)
{
    ui->setupUi(this);
}

NewRulonDialog::~NewRulonDialog()
{
    delete ui;
}
