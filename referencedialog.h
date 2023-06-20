#ifndef REFERENCEDIALOG_H
#define REFERENCEDIALOG_H

#include <QDialog>

namespace Ui {
class ReferenceDialog;
}

class ReferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReferenceDialog(QWidget *parent = nullptr);
    ~ReferenceDialog();

private:
    Ui::ReferenceDialog *ui;
};

#endif // REFERENCEDIALOG_H
