#include "referencedialog.h"
#include "ui_referencedialog.h"

ReferenceDialog::ReferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReferenceDialog)
{
    ui->setupUi(this);
}

ReferenceDialog::~ReferenceDialog()
{
    delete ui;
}
