#ifndef REFERENCEDIALOG_H
#define REFERENCEDIALOG_H

#include <QDialog>
#include <SQLmodule.h>

namespace Ui {
class ReferenceDialog;
}

class ReferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReferenceDialog(QWidget *parent = nullptr);
    ~ReferenceDialog();
    UpdateAll();
    QVector <SqlModule::CartonTypes> TypesList;
    QVector <SqlModule::UsersTypes> UsersList;
    int GlobalcurrentRow,GlobalcurrentRow2;


private slots:
    void on_UserTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ReferenceDialog *ui;
};

#endif // REFERENCEDIALOG_H
