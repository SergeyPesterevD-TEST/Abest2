#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRandomGenerator>
#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
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
#include "ModBusMaster.h"
#include <QMap>
#include <cmath>
#include "owen/owen_io.h"
#include "newrulondialog.h"
#include "referencedialog.h"
#include "userdialog.h"
#include "ConfirmationDialog.h"

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

    float LL; // lenght global

public slots:

private slots:
    void MyGetMessage(QVector<int> OutputMeasures);
    void RestartPower();
    void slotTimerAlarm();  //опрос рифтэк
    void slotTimerAlarm2(); //прорисовка фильтра
    void slotTimerAlarm3(); //прорисовка рифтэк

    void Delay(int msec);

    void makePlot();

    void RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures);
    void RepaintRiftek2(QVector<SqlModule::Top100> *Top100Measures, float minY, float maxY);
    int IsChannelOn(int channel);

    void FilterRiftek(QVector<SqlModule::Top100> *Top100Measures, QVector<int> *CurrentData);
    void FilterRiftek2(QVector<SqlModule::Top100> *Top100Measures);

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

    void lamp(int i, bool beep);

    void on_pushButton_clicked();

    void on_FilterButton_2_clicked();

    void on_pushButton_2_clicked();

private:

    QThread RFThreadThread;
    RFThread RFMeasures;
    //

    QVector<int> SensorTable;
    QVector<ToFilter> Filter;
    ToFilter FilterOne;
    int FilterCount;
    int MainCounter;
    BOOL beep;
    bool NoWatchDog;
    int lampstatus;
    //
    ModBusMaster *Temps;
    ModBusMaster *LightPost;
    //
    SqlModule *SQLConnection;
    //
    unsigned long long lastLIR;
    unsigned long long zeroLIR;
    int lastLAMP;
    QDateTime lastLIRTIME;
    //
    QTimer *timer;  //опрос рифтэк
    QTimer *timer2; //прорисовка фильтра
    QTimer *timer3; //прорисовка рифтэк
    //
    TSetupForm *SetupForm;
    SQLFilter *FilterForm;
    NewRulonDialog *NewRulonForm;
    ReferenceDialog *ReferenceDialogForm;
    UserDialog *UserDialogForm;

    //
    ConfirmationDialog *CDialog;
    Ui::MainWindow *ui;
    RF603 RFSensors;
    int DataCount;

    void UpdateRiftek();
};
#endif // MAINWINDOW_H
