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
    ReferenceDialogForm = new ReferenceDialog;
    UserDialogForm = new UserDialog;

    // MODBUS
    Temps = new ModBusMaster(this);
    Temps->ConnectModbus(INIFile.GetParamStr("Modbus/Temps/host"));
    LightPost = new ModBusMaster(this);
    LightPost->ConnectModbus(INIFile.GetParamStr("Modbus/LightPost/host"));
    //

    MainCounter=0;

    beep=false;
    lampstatus=-1;

    ui->StopBut->setHidden(true);

    makePlot();

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

    lamp(1, false);
    UserDialogForm->UpdateAll();
    UserDialogForm->showFullScreen();
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
    if (i==5) Color.setRgb(0,255,0); //average
    if (i==6) Color.setRgb(160,160,160); //max
    if (i==7) Color.setRgb(160,160,160); //min
    return Color;
}


void MainWindow::makePlot()
{
    QPen Pen;

    // creating Plots and set Pen type
    for (int i=0;i<8;i++)
    {
    Pen.setColor(GetColorForChannel(i));
    if (i==5) {Pen.setWidth(3);} else { Pen.setWidth(1);}
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
    // основной поток по работе с РИФТЭК
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(INIFile.GetParam("Main/Timer"));
    timer3 = new QTimer;
    // прорисовка графика медленная
    connect(timer3, SIGNAL(timeout()), this, SLOT(slotTimerAlarm3()));
    timer3->start(INIFile.GetParam("Main/TimerUpdate"));
    lamp(0, false);
    beep=false;
    lampstatus=0;

    delete(SQLConnection);

//    ui->customPlot->graph(0)->data()->clear();
//    ui->customPlot->replot();


}



void MainWindow::RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures)
{
    SqlModule::Top100 OneMeasure;

    // cleaning
    for (int i=0;i<8;i++)
    {
    ui->customPlot->graph(i)->data()->clear();
    }

    // setting XAxis in time
    //    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    //    timeTicker->setDateTimeFormat("hh:mm");
    //    ui->customPlot->xAxis->setTicker(timeTicker);

    if (Top100Measures->count()<=5) return;

    float tBegin,tEnd;
    OneMeasure=Top100Measures->data()[0];
    tBegin=OneMeasure.LIR;
    OneMeasure=Top100Measures->data()[Top100Measures->count()-1];
    tEnd=OneMeasure.LIR;
    ui->customPlot->xAxis->setRange(tBegin, tEnd);
    ui->customPlot->yAxis->setRange(NewRulonForm->Rulon.min-0.1, NewRulonForm->Rulon.max+0.1);

    qDebug() << "GRAPH tBegin" << tBegin;
    qDebug() << "GRAPH tEnd" << tEnd;

    // max and min
    ui->customPlot->graph(6)->addData(tBegin,NewRulonForm->Rulon.max);
    ui->customPlot->graph(6)->addData(tEnd,NewRulonForm->Rulon.max);
    ui->customPlot->graph(7)->addData(tBegin,NewRulonForm->Rulon.min);
    ui->customPlot->graph(7)->addData(tEnd,NewRulonForm->Rulon.min);
    //

    for (int j=0;j<Top100Measures->count();j++)
    {
    OneMeasure=Top100Measures->data()[j];
    float Average=0;

    for (int i=0;i<INIFile.GetParam("Main/NumberOfPairs");i++)
    {
    if (
            (i==0 && ui->ch01->isChecked())     ||
            (i==1 && ui->ch02->isChecked())     ||
            (i==2 && ui->ch03->isChecked())     ||
            (i==3 && ui->ch04->isChecked())     ||
            (i==4 && ui->ch05->isChecked()))
        {
        Average+=(double)OneMeasure.data.data()[i]/1000;
        ui->customPlot->graph(i)->addData(OneMeasure.LIR,(double)OneMeasure.data.data()[i]/1000);
        }
    }

    if (ui->chAll->isChecked())  // Average
    {
    ui->customPlot->graph(5)->addData(OneMeasure.LIR,Average/5);}
    }

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
    lamp(1, false);
    beep=FALSE;
    lampstatus=-1;
    timer->stop();
    timer3->stop();
    SQLConnection->SqlCalculateStatistics(NewRulonForm->RulonId);
    //если поток
    //RFMeasures.setRunning(false);
    NewRulonForm->RulonId=-1;
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
    if (DCNT>0)
    {
    LL=(float)(DCNT-30000000)/1000;
    ui->LIRedit->setText(QString::number((float)(DCNT-30000000)/1000,'f',1));
    }
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

      if (UserDialogForm->CurrentUser=="")
            {
            ui->pushButtonStart->setEnabled(false);
            ui->StopBut->setEnabled(false);
            } else
                {
                ui->pushButtonStart->setEnabled(true);
                ui->StopBut->setEnabled(true);
                }
        if (UserDialogForm->CurrentisAdmin==1)
            {
                ui->FilterButton->setEnabled(true);
                ui->FilterButton_2->setEnabled(true);
                ui->SettingsBut->setEnabled(true);
            } else
            {
                ui->FilterButton->setEnabled(false);
                ui->FilterButton_2->setEnabled(false);
                ui->SettingsBut->setEnabled(false);
            }
            NewRulonForm->Rulon.username=UserDialogForm->CurrentUser;
}

void MainWindow::slotTimerAlarm()   // основной поток по работе с РИФТЭК
{
    float ThickValue;
    float ThickOffset;
    QVector<int> CurrentData;

    ui->lineProductType->setText(NewRulonForm->Rulon.rulontype);
    ui->lineRulonNumber->setText(NewRulonForm->Rulon.rulonnumber);
    ui->lineThickness->setText(QString::number(NewRulonForm->Rulon.nominal,'f',2));
    ThickOffset=NewRulonForm->Rulon.offset;

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

    if (NewRulonForm->RulonId<=0) { ThickOffset=0; }
    qDebug() << "Канал " << i << SensorTable[i] << SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]
             << INIFile.GetCalib(i,"Base")
             << Measures.data()[SensorTable[i]] << Measures.data()[SensorTable[i+INIFile.GetParam("Main/NumberOfPairs")]] << "ThickValue =" << ThickValue << "offset" << ThickOffset;

    if (ThickValue!=0) {ThickValue = ThickValue + ThickOffset*1000;}
    CurrentData.push_back(ThickValue);

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

    if (MainCounter>1)
    {    
    qDebug() << "SQL insert";
        SQLConnection->SqlPutMeasure2(NewRulonForm->RulonId,&CurrentData, LL, 0);
    lampstatus=lastLAMP;
    MainCounter=0;
    }
}

void MainWindow::slotTimerAlarm3()  // прорисовка графика медленная
{
// to add get all the rulon
    qDebug() << "RulonID " << NewRulonForm->RulonId;
    if (NewRulonForm->RulonId==-1) return;

    SQLConnection->SqlGetRulon(NewRulonForm->RulonId, &Top100Measures); // get last points
    //SQLConnection->SqlGetRulon(10062, &Top100Measures); // get last points

    qDebug() << "TESTGRAPH";
    RepaintRiftek(&Top100Measures);
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
FilterForm->UpdateTable();
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
UserDialogForm->UpdateAll();
UserDialogForm->showFullScreen();

//double asymmetry;
//double kurtosis;
//QVector <qint16> v1;

//            v1.clear();
//            v1.push_back(3);
//            v1.push_back(4);
//            v1.push_back(5);
//            v1.push_back(2);
//            v1.push_back(3);
//            v1.push_back(4);
//            v1.push_back(5);
//            v1.push_back(6);
//            v1.push_back(4);
//            v1.push_back(7);
//            Statistics *Stats =new Statistics;
//            try
//            {
//            Stats->GetKurtosisAndAsymmetry(v1,asymmetry,kurtosis);
//            qDebug() << "SUPERTEST" << asymmetry << kurtosis;
//            }
//            catch (...) {
//        qDebug() << "STTAT Error GetKurtosisAndAsymmetry function";
//            }
//            delete(Stats);
}

void MainWindow::on_FilterButton_2_clicked()
{
//
ReferenceDialogForm->UpdateAll();
ReferenceDialogForm->showMaximized();
}


void MainWindow::on_pushButton_2_clicked()
{

}

