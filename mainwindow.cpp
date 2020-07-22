#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    SetupForm = new TSetupForm;
    FilterForm = new SQLFilter;


    if (INIFile.GetParam("debug")==0)
    {
     ui->GetLirBtn->setHidden(true);
    }

    MainCounter=0;

    lamp(-1);
    ui->StopBut->setHidden(true);
    ui->CancelFilterBut->setHidden(true);
    ui->FilterFlag->setHidden(true);

    MainWindow::makePlot();
    DataCount=0;
    srand(8);

    //
    lastLIR=0;
    zeroLIR=0;
    lastLAMP=-1;
    //

    ui->SensorValues->setColumnCount(7);
    ui->SensorValues->setRowCount(4);
    ui->SensorValues->setShowGrid(true);
    ui->SensorValues->hideColumn(0);
    ui->SensorValues->hideRow(0);
    ui->SensorValues->hideRow(1);
    ui->SensorValues->hideRow(2);
    for (int i=0;i<7;i++) ui->SensorValues->setColumnWidth(i,INIFile.GetParam("Interface/ColumnWidth"));
    for (int i=0;i<4;i++) ui->SensorValues->setRowHeight(i,INIFile.GetParam("Interface/RowHeight"));

    timer2 = new QTimer;
    connect(timer2, SIGNAL(timeout()), this, SLOT(slotTimerAlarm2()));
    timer2->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::GetColorForChannel(int i)
{
    QColor Color;
    if (i==0) Color.setRgb(255,255,0);
    if (i==1) Color.setRgb(255,0,0);
    if (i==2) Color.setRgb(255,0,255);
    if (i==3) Color.setRgb(100,100,255);
    if (i==4) Color.setRgb(0,255,255);
    if (i==5) Color.setRgb(0,255,0);
    return Color;
}


void MainWindow::makePlot()
{
    for (int i=0;i<6;i++)
    {
    ui->customPlot->addGraph();
    QPen Pen;

    Pen.setColor(GetColorForChannel(i));
    Pen.setWidth(3);


    ui->customPlot->graph(i)->setPen(Pen);
    }

    QString PlotScale="";
    switch (INIFile.GetParam("Plot/Scale"))
    {
    case 1:
        PlotScale="мкм";
        break;
    case 1000:
        PlotScale="мм";
        break;
    case 10000:
        PlotScale="cм";
        break;
    case 1000000:
        PlotScale="м";
        break;
    }
    ui->customPlot->yAxis->setLabel("Толщина, "+PlotScale);

    PlotScale="";
    switch (INIFile.GetParam("Plot/ScaleLength"))
    {
    case 1:
        PlotScale="мм";
        break;
    case 1000:
        PlotScale="м";
        break;
    case 1000000:
        PlotScale="км";
        break;
    }
    if (INIFile.GetParam("Plot/Time")==1)
    {
     ui->customPlot->xAxis->setLabel("Время");
    } else {    ui->customPlot->xAxis->setLabel("Длина, "+PlotScale);  }
    ui->customPlot->yAxis->setRange(INIFile.GetParam("Plot/Ymin")/10, INIFile.GetParam("Plot/Ymax")/10);
    ui->customPlot->replot();
}

void MainWindow::on_pushButtonStart_clicked()
{
    SqlModule *SQLConnection=new SqlModule;

    ui->pushButtonStart->setHidden(true);
    ui->StopBut->setHidden(false);
    FilterCount=0;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(INIFile.GetParam("Main/Timer"));
    timer3 = new QTimer;
    connect(timer3, SIGNAL(timeout()), this, SLOT(slotTimerAlarm3()));
    timer3->start(INIFile.GetParam("Main/TimerUpdate"));

    beep=TRUE;
    lamp(0);
//    ui->customPlot->graph(0)->data()->clear();
//    ui->customPlot->replot();

/*
    // потоковая работа с РИФТЭК
    connect(&RFMeasures,&RFThread::EmitMeasures,this,&MainWindow::UpdateRF);
    connect(&RFThreadThread,&QThread::started,&RFMeasures,&RFThread::run);
    connect(&RFMeasures, &RFThread::finished, &RFThreadThread,
    &QThread::terminate);
    RFMeasures.moveToThread(&RFThreadThread);
    RFMeasures.setRunning(true);
    RFThreadThread.start();
*/
}



void MainWindow::RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures)
{
    SqlModule::Top100 OneMeasure;
    int ChannelToShow;

    for (int i=0;i<6;i++)
    {
    ui->customPlot->graph(i)->data()->clear();
    }

    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    timeTicker->setDateTimeFormat("hh:mm");
    ui->customPlot->xAxis->setTicker(timeTicker);

    qint64 tBegin,tEnd;
    for (int i=0;i<Top100Measures->count();i++)
    {
    OneMeasure=Top100Measures->data()[i];

    if (i==0) { tBegin=OneMeasure.cdatetime.toSecsSinceEpoch(); }
    if (i==Top100Measures->count()-1)  {  tEnd=OneMeasure.cdatetime.toSecsSinceEpoch();
    }

    for (int i=0;i<6;i++)
    {
    if ((i==0 && ui->ch00->isChecked())     ||
            (i==1 && ui->ch01->isChecked())     ||
            (i==2 && ui->ch02->isChecked())     ||
            (i==3 && ui->ch03->isChecked())     ||
            (i==4 && ui->ch04->isChecked())     ||
            (i==5 && ui->ch05->isChecked()))
        {
        ui->customPlot->graph(i)->addData(OneMeasure.cdatetime.toSecsSinceEpoch(),(double)OneMeasure.data.data()[i]/1000);
        }
    }
    }
    ui->customPlot->xAxis->setRange(tBegin, tEnd);
    ui->customPlot->yAxis->setRange((double)INIFile.GetParam("Plot/Ymin")/10, (double)INIFile.GetParam("Plot/Ymax")/10);
    ui->customPlot->replot();
}

void MainWindow::UpdateRiftek()  // one measure
{
}

void MainWindow::on_GetRiftekBtn_clicked()
{
}


void MainWindow::on_SettingsBut_clicked()
{
   SetupForm->showMaximized();

}

void MainWindow::on_GetLirBtn_clicked()
{
//    LirMain();
}

void MainWindow::on_ThreadBut_clicked()
{
}


void MainWindow::UpdateRF(QVector<int> OutputMeasures)
{
//    RepaintRiftek(&OutputMeasures);
}

void MainWindow::on_StopBut_clicked()
{
    beep=FALSE;
    lamp(-1);
    timer->stop();
    timer3->stop();
    //если поток
    //RFMeasures.setRunning(false);
    ui->pushButtonStart->setHidden(false);
    ui->StopBut->setHidden(true);
}

void MainWindow::slotTimerAlarm2()    // забираем из базы большой архив
{
    if (INIFile.GetParam("FilterSQL/Enabled")==1)
       {
        ui->FilterFlag->setHidden(false);
        ui->CancelFilterBut->setHidden(false);

        if (INIFile.GetParam("FilterSQL/Do")==1)
            {
            INIFile.SetParam("FilterSQL/Do",0);
            SQLConnection->SqlGetLast(-1, 0, &FilterMeasures); // get last points
            RepaintRiftek(&FilterMeasures);
            }
      } else
            {
            ui->FilterFlag->setHidden(true);
            ui->CancelFilterBut->setHidden(true);
            }

}

void MainWindow::slotTimerAlarm()   // основной поток по работе с РИФТЭК
{
    float ThickValue;
    QVector<int> CurrentData;

    if (INIFile.GetParam("NoPort")==0)
    {
    // working with hardware RIFTEK
    RFSensors.RF603_CheckSensors(&INIFile, &Measures);
    } else
    {
    // when working without sensors. just to check algorhytms.

    Measures.clear();
    for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
    {
        Measures.push_back(4100+1000*rand()/RAND_MAX);
        Measures.push_back(4100+1000*rand()/RAND_MAX);
    }
    }
    QApplication::processEvents();

    CurrentData.clear();
    // Определяем толщину из показаний датчиков
    for (int i=0; i<INIFile.GetParam("Main/NumberOfPairs"); i++)
    {
    ThickValue=INIFile.GetCalib(i,"Base")-Measures.data()[i]-Measures.data()[i+INIFile.GetParam("Main/NumberOfPairs")];
    if (Measures.data()[i]==0 || Measures.data()[i+INIFile.GetParam("Main/NumberOfPairs")]==0)
        {     ThickValue=0;    }
    CurrentData.push_back(ThickValue);
    //qDebug() << "Канал " << i << "ThickValue =" << ThickValue;
    }

    SqlModule::Top100 OnePacket;
    OnePacket.rulon="rulon3";
    OnePacket.cdatetime=QDateTime::currentDateTime();
    OnePacket.data=CurrentData;

    LastMeasures.push_back(OnePacket);

    //qDebug() << "Количество в буфере " << LastMeasures.count();

    // ограничиваем LastMeasures размером фильтра
    if (LastMeasures.count()>INIFile.GetParam("Main/FilterSize"))
       { LastMeasures.pop_front();  }

    // прогоняем фильтр по LastMeasures, отображаем на экране и кладем в базу каждый n-ный.
    CurrentData.clear();
    FilterRiftek(&LastMeasures,&CurrentData);
    /*qDebug() << "после фильтра";
    for (int i=0; i<INIFile.GetParam("Main/NumberOfPairs"); i++)
    {
        qDebug() << CurrentData.data()[i];
    }*/
    // в CurrentData лежит то, что нужно показать

    RefillTableRiftek2(&CurrentData,&Measures);
    MainCounter++;

    if (MainCounter>30)
    {
        // refresh LIR
        unsigned long LIR;
        QDateTime LIRTIME;
        float LL,LL2;
        float LSPEED;
        LL=0;
        LL2=0;
        LSPEED=0;


        //if (zeroLIR!=0) // if ZERO is not set jump over
        {
            int i=0;
            do {  i++;  GetLIR(&LIR, &LIRTIME);  } while (LIR==0 && i<5);

            if (LIR!=0)  // if success
            { //qDebug() << "LIR success " << i;
            if (lastLIR!=0)  // if it is not the first data
                {
                if (INIFile.GetParam("Lir/IPR")!=0)
                {
                if (zeroLIR!=0) {LL=M_PI*INIFile.GetParam("Lir/D")*(LIR-zeroLIR)/INIFile.GetParam("Lir/IPR");}
                LL2=M_PI*INIFile.GetParam("Lir/D")*(LIR-lastLIR)/INIFile.GetParam("Lir/IPR");
                ui->LIRedit->setText(QString::number(LL/1000,'f', 2));
                //qDebug() << "L " << LL;

                if (LIRTIME.toSecsSinceEpoch()-lastLIRTIME.toSecsSinceEpoch()!=0)
                    {
                    LSPEED=LL2/
                        (LIRTIME.toSecsSinceEpoch()-lastLIRTIME.toSecsSinceEpoch());
                    //qDebug() << "S " << LSPEED;
                    ui->SPEEDedit->setText(QString::number(LSPEED/1000,'f', 2));
                    }
                }
                }
            lastLIR=LIR;
            lastLIRTIME=LIRTIME;
            //qDebug() << "lastLIR " << lastLIR;
            //qDebug() << "lastLIRTIME " << lastLIRTIME;
            } else { qDebug() << "LIR failed"; }
       }
       // ~refresh LIR
    qDebug() << "SQL insert";
    SQLConnection->SqlPutMeasure2("rulon4",&CurrentData, LL/1000, LSPEED/1000);

    MainCounter=0;
    }
}

void MainWindow::slotTimerAlarm3()  // прорисовка графика медленная
{

    SQLConnection->SqlGetLast(0, INIFile.GetParam("Plot/Xhours"), &Top100Measures); // get last points
    if (INIFile.GetParam("FilterSQL/Enabled")==0)
    {
    RepaintRiftek(&Top100Measures);
    }
}

void MainWindow::FilterRiftek(QVector<SqlModule::Top100> *Top100Measures, QVector<int> *CurrentData)
{
    int CountNotZero;
    double Average;
    SqlModule::Top100 OneMeasure;
    CurrentData->clear();
    for (int ch=0;ch<INIFile.GetParam("Main/NumberOfPairs");ch++)
        {
        Average=0; CountNotZero=0;
        for (int j=0;j<Top100Measures->count();j++)
                {
                OneMeasure=Top100Measures->data()[j];
                if (OneMeasure.data.data()[ch]>0)
                    {
                    Average=Average+OneMeasure.data.data()[ch];
                    CountNotZero++;
                    }
                }
            if (CountNotZero!=0)
                {
                Average=Average/CountNotZero;
                } else Average=0;
        CurrentData->push_back(Average);
        }
}

void MainWindow::FilterRiftek2(QVector<SqlModule::Top100> *Top100Measures)
{
    int CountNotZero;
    double Average;
    SqlModule::Top100 OneMeasure;

    if (Top100Measures->count()>INIFile.GetParam("Main/FilterSize")*2)
    {
    for (int i=Top100Measures->count()-INIFile.GetParam("Main/FilterSize");i>0;i--)
        {
        for (int ch=0;ch<INIFile.GetParam("Main/NumberOfPairs");ch++)
            {
            Average=0; CountNotZero=0;
            for (int j=0;j<INIFile.GetParam("Main/FilterSize");j++)
                {
                if (i+j<Top100Measures->count())
                {
                OneMeasure=Top100Measures->data()[i+j];
                if (OneMeasure.data.data()[ch]>0)
                    {
                    Average=Average+OneMeasure.data.data()[ch];
                    CountNotZero++;
                    }
                }
                }
            if (CountNotZero!=0)
                {
                Average=Average/CountNotZero;
                } else Average=0;
                int xCount;
                xCount=i+INIFile.GetParam("Main/FilterSize");
                if (i+INIFile.GetParam("Main/FilterSize")>=Top100Measures->count())
                { xCount=Top100Measures->count()-1; }

                OneMeasure=Top100Measures->data()[xCount];
                OneMeasure.data.data()[ch]=Average;
                Top100Measures->data()[xCount]=OneMeasure;

            }
        }
    }
}


void MainWindow::RefillTableRiftek(QVector<SqlModule::Top100> *Top100Measures, QVector<int> *Measures)
{
SqlModule::Top100 OneMeasure;

OneMeasure=Top100Measures->data()[Top100Measures->count()-1];
BOOL flag;
flag=FALSE;

for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
   {
    if (Measures->data()[i]==0 || Measures->data()[i+INIFile.GetParam("Main/NumberOfPairs")]==0)
    {
    ui->SensorValues->setItem(3, 6-i, new QTableWidgetItem(QString::number(0,'f',INIFile.GetParam("Main/Digits"))));
    ui->SensorValues->item(3,6-i)->setBackground(GetColorForChannel(i));
    flag=TRUE;
    }
    else
    {
        ui->SensorValues->setItem(3, 6-i,
        new QTableWidgetItem(QString::number((double)OneMeasure.data.data()[i]/INIFile.GetParam("Plot/Scale"),'f',INIFile.GetParam("Main/Digits"))));
        ui->SensorValues->item(3,6-i)->setBackground(GetColorForChannel(i));
    }    
   }
if (flag) {        lamp(2);} else {        lamp(0);}
}


void MainWindow::RefillTableRiftek2(QVector<int> *CurrentData, QVector<int> *Measures)
{
BOOL flag;
flag=FALSE;

for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
   {
    if (Measures->data()[i]==0 || Measures->data()[i+INIFile.GetParam("Main/NumberOfPairs")]==0)
    {
    ui->SensorValues->setItem(3, 6-i, new QTableWidgetItem(QString::number(0,'f',INIFile.GetParam("Main/Digits"))));
    ui->SensorValues->item(3,6-i)->setBackground(GetColorForChannel(i));
    flag=TRUE;
    }
    else
    {
        ui->SensorValues->setItem(3, 6-i,
        new QTableWidgetItem(QString::number((double)CurrentData->data()[i]/INIFile.GetParam("Plot/Scale"),'f',INIFile.GetParam("Main/Digits"))));
        ui->SensorValues->item(3,6-i)->setBackground(GetColorForChannel(i));
    }
   }
if (flag) {        lamp(2);} else {        lamp(0);}
}


void MainWindow::on_FilterButton_clicked()
{
    FilterForm->showMaximized();
}

void MainWindow::on_CancelFilterBut_clicked()
{
    INIFile.SetParam("FilterSQL/Enabled",0);
}

void MainWindow::on_ch0_stateChanged(int arg1)
{
    if (INIFile.GetParam("FilterSQL/Enabled")==1)
        {
        RepaintRiftek(&FilterMeasures);
        }
}

void MainWindow::on_ch1_stateChanged(int arg1)
{
    this->on_ch0_stateChanged(arg1);
}

void MainWindow::on_ch2_stateChanged(int arg1)
{
    this->on_ch0_stateChanged(arg1);
}

void MainWindow::on_ch3_stateChanged(int arg1)
{
    this->on_ch0_stateChanged(arg1);
}

void MainWindow::on_ch4_stateChanged(int arg1)
{
    this->on_ch0_stateChanged(arg1);
}

void MainWindow::on_ch5_stateChanged(int arg1)
{
    this->on_ch0_stateChanged(arg1);
}

void MainWindow::GetLIR(unsigned long *LIR, QDateTime *LIRTIME)
{
        QProcess process;
        QString LIRResponse;
        *LIRTIME = QDateTime::currentDateTime();

        process.start( "C:\\THICKNESS\\Installer\\lirlen.exe"); //, QStringList() << "-t" );
        if( !process.waitForStarted() || !process.waitForFinished() ) {
            return;
        }
        LIRResponse=process.readAllStandardOutput();
        LIRResponse.chop(2);
        LIRResponse.remove(0,1);
        *LIR = LIRResponse.toULong();
/*        qDebug() << LIRResponse;
        qDebug() << *LIR;
        qDebug() << *LIRTIME;*/
}

void MainWindow::lamp(int i)
{
QStringList ql;

if (lastLAMP==i) {return; } // if the state is changed
lastLAMP=i;

if (ui->AlarmBox->isChecked())
{
if (i==-1) ql.push_back("32");
if (i==0) ql.push_back("64");
if (i==1) ql.push_back("16");
if (i==2 && beep) ql.push_back("144");
if (i==2 && !beep) ql.push_back("128");
} else ql.push_back("32");

QProcess::startDetached("C:\\THICKNESS\\Installer\\lirQT.exe",ql);

}

void MainWindow::on_pushButton_clicked()   //reset lir
{
    unsigned long LIR;
    QDateTime LIRTIME;

    GetLIR(&LIR, &LIRTIME);

    zeroLIR=LIR;
}
