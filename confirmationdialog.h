#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class ConfirmationDialog;
}

class ConfirmationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationDialog(QWidget *parent = nullptr);
    ~ConfirmationDialog();
    void SetMessage(QString theMessage);

private slots:


private:
    Ui::ConfirmationDialog *ui;
};

#endif // CONFIRMATIONDIALOG_H
