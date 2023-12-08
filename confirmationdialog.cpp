#include "confirmationdialog.h"
#include "ui_confirmationdialog.h"

ConfirmationDialog::ConfirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("ОК");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
}

ConfirmationDialog::~ConfirmationDialog()
{
    delete ui;
}

void ConfirmationDialog::SetMessage(QString theMessage)
{
    ui->DMessage->setText(theMessage);
}

