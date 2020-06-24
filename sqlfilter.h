#ifndef SQLFILTER_H
#define SQLFILTER_H

#include <QWidget>
#include "inisettings.h"

namespace Ui {
class SQLFilter;
}

class SQLFilter : public QWidget
{
    Q_OBJECT

public:
    explicit SQLFilter(QWidget *parent = nullptr);
    ~SQLFilter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SQLFilter *ui;
};

#endif // SQLFILTER_H
