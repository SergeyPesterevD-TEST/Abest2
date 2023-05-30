#ifndef SQLFILTER_H
#define SQLFILTER_H

#include <QWidget>
#include "inisettings.h"
#include "SQLmodule.h"

namespace Ui {
class SQLFilter;
}

class SQLFilter : public QWidget
{
    Q_OBJECT

public:
    explicit SQLFilter(QWidget *parent = nullptr);
    ~SQLFilter();

    void UpdateTable();
    int RulonId;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::SQLFilter *ui;
};

#endif // SQLFILTER_H
