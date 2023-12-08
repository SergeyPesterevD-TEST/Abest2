#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    CurrentUser="";
    CurrentisAdmin=0;
    ui->WrongPassword->setVisible(false);
}

UserDialog::~UserDialog()
{
    delete ui;
}

UserDialog::UpdateAll()
{
    SqlModule *SQLConnection=new SqlModule;
    if (INIFile.GetParam("NoPort")==1)
        {
        SQLConnection->SqlGetUsers(UsersList,"isadmin=1");
        } else
            {
            SQLConnection->SqlGetUsers(UsersList,"");
            }
    ui->UsersComboBox->clear();
    for (int i=0;i<UsersList.count();i++)
    {
        ui->UsersComboBox->addItem(UsersList[i].username,UsersList[i].key);
    }
    ui->lineEdit->setText("");
    SQLConnection->deleteLater();
}

void UserDialog::on_buttonBox_accepted()
{
    for (int i=0;i<UsersList.count();i++)
    {
        if (UsersList[i].username==ui->UsersComboBox->currentText())
        {
            if (UsersList[i].password==ui->lineEdit->text())
            {
                // login success
                CurrentUser=UsersList[i].username;
                CurrentisAdmin=UsersList[i].isadmin;
                return;
            }

        }
    }
    CurrentUser="";
    CurrentisAdmin=0;
  ui->WrongPassword->setVisible(true);
  this->showFullScreen();
}


void UserDialog::on_UserDialog_rejected()
{
  CurrentUser="";
  CurrentisAdmin=0;
  ui->lineEdit->setText("");
}

