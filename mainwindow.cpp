#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    SetupForm = new TSetupForm;
    FilterForm = new SQLFilter;
    NewRulonForm = new NewRulonDialog;

    // MODBUS
    Temps = new ModBusMaster(this);
    Temps->ConnectModbus(INIFile.GetParamStr("Modbus/Temps/host"));
    LightPost = new ModBusMaster(this);
    LightPost->ConnectModbus(INIFile.GetParamStr("Modbus/LightPost/host"));
    //

    if (INIFile.GetParam("debug")==0)
    {
     ui->GetLirBtn->setHidden(true);
    }

    MainCounter=0;

    beep=false;
    lampstatus=-1;

    ui->StopBut->setHidden(true);

    MainWindow::makePlot();
    DataCount=0;
    srand(8);

    //
    lastLIR=0;
    zeroLIR=0;
    lastLAMP=-1;
    //

    //
    SensorTable.clear();
    for (int i=0; i<INIFile.GetParam("Main/NumberOfPairs")*2; i++)
    {
     SensorTable.push_back(INIFile.GetParam("Sensors/"+QString::number(i)+"/Address"));
    }
    for (int i=0; i<SensorTable.count(); i++)
    qDebug() << "table " << i << "sensor =" << SensorTable[i];
    //

    ui->SensorValues->setColumnCount(1+INIFile.GetParam("Main/NumberOfPairs"));
    ui->SensorValues->setRowCount(5);
    ui->SensorValues->setShowGrid(true);
    ui->SensorValues->hideColumn(0);
    ui->SensorValues->hideRow(0);
    ui->SensorValues->hideRow(1);
    ui->SensorValues->hideRow(2);
    for (int i=0;i<2+INIFile.GetParam("Main/NumberOfPairs");i++) ui->SensorValues->setColumnWidth(i,INIFile.GetParam("Interface/ColumnWidth"));
    for (int i=0;i<5;i++) ui->SensorValues->setRowHeight(i,INIFile.GetParam("Interface/RowHeight"));

    int err;
    SetApiMode(OWENIO_API_OLD);
    err=OpenPort(1 - 1, spd_9600, prty_NONE, databits_8, stopbit_1, RS485CONV_AUTO);
    qDebug() << "OWEN Open" << err;

    timer2 = new QTimer;
    connect(timer2, SIGNAL(timeout()), this, SLOT(slotTimerAlarm2()));
    timer2->start(500);
}

MainWindow::~MainWindow()
{
    ClosePort();
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
    QPen Pen;

    // creating Plots and set Pen type
    for (int i=0;i<6;i++)
    {
    Pen.setColor(GetColorForChannel(i));
    Pen.setWidth(3);
    ui->customPlot->addGraph();
    ui->customPlot->graph(i)->setPen(Pen);
    }

    Pen.setColor(GetColorForChannel(3));

    // setting Axis
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

    //ui->customPlot->xAxis->setLabel("Время");

    ui->customPlot->yAxis->setRange((double)INIFile.GetParam("Plot/Ymin")/10, (double)INIFile.GetParam("Plot/Ymax")/10);

    ui->customPlot->replot();

}

void MainWindow::on_pushButtonStart_clicked()
{
    NewRulonForm->RulonId=-1;
    NewRulonForm->showMaximized();
    NewRulonForm->updateAll();

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

    beep=false;
    lampstatus=0;

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
    float MaxSpeed, MinSpeed;
    MinSpeed=100000;
    MaxSpeed=-100000;

    // cleaning
    for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
    {
    ui->customPlot->graph(i)->data()->clear();
    }


    // setting XAxis in time
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

    for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
    {
    if (
            (i==0 && ui->ch01->isChecked())     ||
            (i==1 && ui->ch02->isChecked())     ||
            (i==2 && ui->ch03->isChecked())     ||
            (i==3 && ui->ch04->isChecked())     ||
            (i==4 && ui->ch05->isChecked()))
        {
        ui->customPlot->graph(i)->addData(OneMeasure.cdatetime.toSecsSinceEpoch(),(double)OneMeasure.data.data()[i]/1000);
        }
    }

    if (OneMeasure.SPEED>MaxSpeed) MaxSpeed=OneMeasure.SPEED;
    if (OneMeasure.SPEED<MinSpeed && OneMeasure.SPEED>0) { MinSpeed=OneMeasure.SPEED;}

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
   lamp(1,false);

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
    lampstatus=-1;
    timer->stop();
    timer3->stop();
    //если поток
    //RFMeasures.setRunning(false);
    ui->pushButtonStart->setHidden(false);
    ui->StopBut->setHidden(true);
}

void MainWindow::slotTimerAlarm2()    // забираем из базы большой архив
{

    // OWEN
    int DCNT=0;
    int DSPD=0;
    DWORD address=2;

    ReadSI8BCD(address, ADRTYPE_8BIT, "DCNT", DCNT);
    qDebug() << "OWEN DCNT Get" << DCNT;
    QThread::msleep(500);
    ReadSI8BCD(address, ADRTYPE_8BIT, "DSPD", DSPD);
    qDebug() << "OWEN DSPD Get" << DSPD;
    int hrs=0;
    int mins=0;
    int sec=0;
    int msec=0;
    QThread::msleep(500);
    ReadDTMR(address, ADRTYPE_8BIT, hrs,mins,sec,msec);
    qDebug() << "OWEN DTMR Get" << hrs << mins << sec << msec;

    // !OWEN

    Temps->ModbusReadInputRegisters(1);
    ui->Temperatures->setText(
        QString::number(Temps->DIVector[0]/100)+" C,"+
        QString::number(Temps->DIVector[1]/100)+" C,"+
        QString::number(Temps->DIVector[2]/100)+" C,"+
        QString::number(Temps->DIVector[3]/100)+" C"
        );
    //return;

    if (INIFile.GetParam("FilterSQL/Enabled")==1)
       {

        if (INIFile.GetParam("FilterSQL/Do")==1)
            {
            INIFile.SetParam("FilterSQL/Do",0);
            SQLConnection->SqlGetLast(-1, 0, &FilterMeasures); // get last points
            RepaintRiftek(&FilterMeasures);
            }
      } else
            {
            }

}

void MainWindow::slotTimerAlarm()   // основной поток по работе с РИФТЭК
{
    float ThickValue;
    QVector<int> CurrentData;

    //lamp(1,false);

    if (INIFile.GetParam("NoPort")==0)
    {
    // working with hardware RIFTEK
    RFSensors.RF603_CheckSensors(&INIFile, &Measures);
    } else
    {
    // when working without sensors. just to check algorhytms.
    Measures.clear();
    for (int i=0;i<=INIFile.GetParam("Main/NumberOfPairs")+1;i++)
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
    ThickValue=INIFile.GetCalib(i,"Base")-Measures.data()[SensorTable[i]]-Measures.data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]];

    if (Measures.data()[SensorTable[i]]==0 || Measures.data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]]==0)
        {     ThickValue=0;    }
    CurrentData.push_back(ThickValue);
    qDebug() << "Канал " << i << SensorTable[i] << SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]
        << INIFile.GetCalib(i,"Base")
             << Measures.data()[SensorTable[i]] << Measures.data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]] << "ThickValue =" << ThickValue;
    }

    SqlModule::Top100 OnePacket;
    OnePacket.rulon="rulon3";
    OnePacket.cdatetime=QDateTime::currentDateTime();
    OnePacket.data=CurrentData;

    LastMeasures.push_back(OnePacket);

    // ограничиваем LastMeasures размером фильтра
    if (LastMeasures.count()>INIFile.GetParam("Main/FilterSize"))
       { LastMeasures.pop_front();  }

    // прогоняем фильтр по LastMeasures, отображаем на экране и кладем в базу каждый n-ный.
    CurrentData.clear();
    FilterRiftek(&LastMeasures,&CurrentData);

    // в CurrentData лежит то, что нужно показать
    RefillTableRiftek2(&CurrentData,&Measures);

    MainCounter++;

    if (MainCounter>30)
    {
        // refresh LIR
        unsigned long long LIR;
        QDateTime LIRTIME;
        float LL,LL2;
        float LSPEED;
        LL=0;
        LL2=0;
        LSPEED=0;


        /*//if (zeroLIR!=0) // if ZERO is not set jump over
        {

> 23 47 49 48 47 53 48 4E 4A 55  <
23 47 49 48 47 53 48 4E 4A 55
> 23 47 49 48 47 53 48 4E 4A 55 4E 48 51 0D  < 23 47 49 48 47 53 48 4E 4A 55 4E 48 51 0D 23 47 49 47 4B 53 48 4E 4A 52 47 47 47 47 47 47 47 4A 56 4C 49 0D

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
                    ui->SPEEDedit->setText(QString::number(60*LSPEED/1000,'f', 2));
                    }
                }
                }
            lastLIR=LIR;
            lastLIRTIME=LIRTIME;
  //          qDebug() << "lastLIR " << lastLIR;
  //          qDebug() << "lastLIRTIME " << lastLIRTIME;
            } else { qDebug() << "LIR failed"; }
       }*/
       // ~refresh LIR
    qDebug() << "SQL insert";
    SQLConnection->SqlPutMeasure2("rulon4",&CurrentData, LL/1000, LSPEED/1000);
    lampstatus=lastLAMP;
    MainCounter=0;
    }
}

void MainWindow::slotTimerAlarm3()  // прорисовка графика медленная
{

    SQLConnection->SqlGetLast(0, INIFile.GetParam("Plot/Xhours"), &Top100Measures); // get last points
    SQLConnection->SqlGetAverageRow(INIFile.GetParam("Main/AverageRow"), &AverageRowMeasures); // get last points
    if (INIFile.GetParam("FilterSQL/Enabled")==0)
    {
        for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
        {
        ui->SensorValues->setItem(4, INIFile.GetParam("Main/NumberOfPairs")-i, new QTableWidgetItem(QString::number(AverageRowMeasures.data()[i],'f',INIFile.GetParam("Main/Digits"))));
        ui->SensorValues->item(4,INIFile.GetParam("Main/NumberOfPairs")-i)->setBackground(GetColorForChannel(i));
        }
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
        if (Measures->data()[SensorTable[i]]==0 || Measures->data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]]==0)
    //if (Measures->data()[i]==0 || Measures->data()[i+INIFile.GetParam("Main/NumberOfPairs")]==0)
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
if (flag) {        lampstatus=2;} else {        lampstatus=0;}
}


void MainWindow::RefillTableRiftek2(QVector<int> *CurrentData, QVector<int> *Measures)
{
BOOL flag;
flag=FALSE;

for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
   {
    if (Measures->data()[SensorTable[i]]==0 || Measures->data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]]==0)
    {
//    ui->SensorValues->setItem(3, INIFile.GetParam("Main/NumberOfPairs")-i, new QTableWidgetItem(QString::number(0,'f',INIFile.GetParam("Main/Digits"))));
      ui->SensorValues->setItem(3, INIFile.GetParam("Main/NumberOfPairs")-i,
                                  new QTableWidgetItem("["+QString::number((double)CurrentData->data()[i]/INIFile.GetParam("Plot/Scale"),'f',INIFile.GetParam("Main/Digits"))+"]"));

    ui->SensorValues->item(3,INIFile.GetParam("Main/NumberOfPairs")-i)->setBackground(GetColorForChannel(i));
    flag=TRUE;
    }
    else
    {
//    qDebug() << "AF" << i << (double)CurrentData->data()[i];
        ui->SensorValues->setItem(3, INIFile.GetParam("Main/NumberOfPairs")-i,
        new QTableWidgetItem(QString::number((double)CurrentData->data()[i]/INIFile.GetParam("Plot/Scale"),'f',INIFile.GetParam("Main/Digits"))));
        ui->SensorValues->item(3,INIFile.GetParam("Main/NumberOfPairs")-i)->setBackground(GetColorForChannel(i));
    }
   }
if (flag) {        lampstatus=2;} else {        lampstatus=0;}
}


void MainWindow::on_FilterButton_clicked()
{
    FilterForm->showMaximized();
}

void MainWindow::on_CancelFilterBut_clicked()
{

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

void MainWindow::GetLIR(unsigned long long *LIR, QDateTime *LIRTIME)
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
        *LIR = LIRResponse.toULongLong();
        qDebug() << LIRResponse;
        qDebug() << *LIR;
        qDebug() << *LIRTIME;
}

void MainWindow::lamp(int i, bool beep)
{
/*
 -1 NOTHING
 0 green
 1 yellow
 2 red
 beep
 */
        int status=0;
        for (int j=0;j<3;j++)
            {
            if (j==i) { status+=pow(2,j); }
            }
            if (beep) { status+=8; }

LightPost->WriteMultipleCoils(0,status,4);
}

void MainWindow::on_pushButton_clicked()   //reset lir
{
    unsigned long long LIR;
    QDateTime LIRTIME;

    GetLIR(&LIR, &LIRTIME);

    zeroLIR=LIR;
}
