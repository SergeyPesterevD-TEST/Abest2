#ifndef CHARTFROMSQL_H
#define CHARTFROMSQL_H

#include <QDialog>
#include "SQLmodule.h"

namespace Ui {
class ChartFromSQL;
}

class ChartFromSQL : public QDialog
{
    Q_OBJECT

public:
    explicit ChartFromSQL(QWidget *parent = nullptr);
    ~ChartFromSQL();
    void ShowChart(QString KeyAsString);

private slots:
    void on_ch05_stateChanged(int arg1);

    void on_ch04_stateChanged(int arg1);

    void on_ch03_stateChanged(int arg1);

    void on_ch02_stateChanged(int arg1);

    void on_ch01_stateChanged(int arg1);

    void on_chAll_stateChanged(int arg1);

private:
    Ui::ChartFromSQL *ui;
    SqlModule *SQLConnection;
    void RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures, float minY, float maxY);
    QColor GetColorForChannel(int i);
    QVector<SqlModule::Top100> Top100Measures;
    QString LaserKey;

};

#endif // CHARTFROMSQL_H
