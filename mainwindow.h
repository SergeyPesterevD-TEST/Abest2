#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRandomGenerator>
#include <QMainWindow>
#include <QTimer>
#include "windows.h"
#include "objbase.h"
#include "inisettings.h"
#include "tsetupform.h"
#include "rfthread.h"
#include "SQLmodule.h"
#include "RF603.h"
#include "ui_mainwindow.h"
#include "sqlfilter.h"
#include "algorithms/filters.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ToFilter
{
QVector<int> data;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    IniSettings INIFile;
    QVector<int> Measures;
    QVector<float> AverageRowMeasures;
    QVector<SqlModule::Top100> Top100Measures;
    QVector<SqlModule::Top100> LastMeasures;
    QVector<SqlModule::Top100> FilterMeasures;

public slots:
    void UpdateRF(QVector<int> OutputMeasures);

private slots:   

    void slotTimerAlarm();  //опрос рифтэк
    void slotTimerAlarm2(); //прорисовка фильтра
    void slotTimerAlarm3(); //прорисовка рифтэк

    void makePlot();

    void RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures); 

    void FilterRiftek(QVector<SqlModule::Top100> *Top100Measures, QVector<int> *CurrentData);
    void FilterRiftek2(QVector<SqlModule::Top100> *Top100Measures);

    void GetLIR(unsigned long *LIR, QDateTime *LIRTIME);

    void RefillTableRiftek2(QVector<int> *CurrentData, QVector<int> *Measures);
    void RefillTableRiftek(QVector<SqlModule::Top100> *Top100Measures, QVector<int> *Measures);

    void on_pushButtonStart_clicked();

    void on_GetRiftekBtn_clicked();

    void on_SettingsBut_clicked();

    void on_GetLirBtn_clicked();

    void on_ThreadBut_clicked();

    void on_StopBut_clicked();

    void on_FilterButton_clicked();

    void on_CancelFilterBut_clicked();

    void on_ch0_stateChanged(int arg1);

    void on_ch1_stateChanged(int arg1);

    void on_ch2_stateChanged(int arg1);

    void on_ch3_stateChanged(int arg1);

    void on_ch4_stateChanged(int arg1);

    void on_ch5_stateChanged(int arg1);

    QColor GetColorForChannel(int i);

    void lamp(int i, bool force);

    void on_pushButton_clicked();

private:

    QThread RFThreadThread;
    RFThread RFMeasures;
    //
    QVector<ToFilter> Filter;
    ToFilter FilterOne;
    int FilterCount;
    int MainCounter;
    BOOL beep;
    //
    SqlModule *SQLConnection;
    //
    unsigned long lastLIR;
    unsigned long zeroLIR;
    int lastLAMP;
    QDateTime lastLIRTIME;
    //
    QTimer *timer;  //опрос рифтэк
    QTimer *timer2; //прорисовка фильтра
    QTimer *timer3; //прорисовка рифтэк
    //
    TSetupForm *SetupForm;
    SQLFilter *FilterForm;
    Ui::MainWindow *ui;
    RF603 RFSensors;
    int DataCount;

    void UpdateRiftek();
};
#endif // MAINWINDOW_H
