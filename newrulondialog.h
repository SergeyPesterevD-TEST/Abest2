#ifndef NEWRULONDIALOG_H
#define NEWRULONDIALOG_H

#include <QDialog>
#include <SQLmodule.h>

namespace Ui {
class NewRulonDialog;
}

class NewRulonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewRulonDialog(QWidget *parent = nullptr);
    ~NewRulonDialog();
    QVector <SqlModule::CartonTypes> TypesList;
    QVector <SqlModule::UsersTypes> UsersList;
    void updateAll();

    SqlModule::CurrentRulon Rulon;
    int RulonId;
    float nominal, min, max, offset;

private slots:
    void on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_buttonBox_accepted();

private:
    Ui::NewRulonDialog *ui;


};

#endif // NEWRULONDIALOG_H
