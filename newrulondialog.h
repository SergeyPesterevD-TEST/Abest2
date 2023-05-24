#ifndef NEWRULONDIALOG_H
#define NEWRULONDIALOG_H

#include <QDialog>

namespace Ui {
class NewRulonDialog;
}

class NewRulonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewRulonDialog(QWidget *parent = nullptr);
    ~NewRulonDialog();

private:
    Ui::NewRulonDialog *ui;
};

#endif // NEWRULONDIALOG_H
