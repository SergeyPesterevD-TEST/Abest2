#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "SQLmodule.h"
#include "inisettings.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();
    UpdateAll();
    QVector <SqlModule::UsersTypes> UsersList;
    QString CurrentUser;
    int CurrentisAdmin;
    IniSettings INIFile;

private slots:
    void on_buttonBox_accepted();

    void on_UserDialog_rejected();

private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_H
