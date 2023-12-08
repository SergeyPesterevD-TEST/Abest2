#include "chartfromsql.h"
#include "ui_chartfromsql.h"

ChartFromSQL::ChartFromSQL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartFromSQL)
{
    ui->setupUi(this);

    QPalette p = ui->ch01->palette();

    p.setColor(QPalette::Active, QPalette::WindowText, GetColorForChannel(0));
    ui->ch01->setPalette(p);
    p.setColor(QPalette::Active, QPalette::WindowText, GetColorForChannel(1));
    ui->ch02->setPalette(p);
    p.setColor(QPalette::Active, QPalette::WindowText, GetColorForChannel(2));
    ui->ch03->setPalette(p);
    p.setColor(QPalette::Active, QPalette::WindowText, GetColorForChannel(3));
    ui->ch04->setPalette(p);
    p.setColor(QPalette::Active, QPalette::WindowText, GetColorForChannel(4));
    ui->ch05->setPalette(p);
}

ChartFromSQL::~ChartFromSQL()
{
    delete ui;
}

QColor ChartFromSQL::GetColorForChannel(int i)
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

void ChartFromSQL::ShowChart(QString KeyAsString)
{
//
    LaserKey=KeyAsString;
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


    // cleaning
    for (int i=0;i<8;i++)
    {
        ui->customPlot->graph(i)->data()->clear();
    }
    ui->customPlot->replot();

    if (KeyAsString.toInt()==-1)
    {
        return;
    }

    SqlModule *SQLConnection=new SqlModule;

    qDebug() << "CHART key" << KeyAsString.toInt();

    SQLConnection->SqlGetRulon(KeyAsString.toInt(), &Top100Measures); // get last points

    if (Top100Measures.count()>5)
        {
        qDebug() << "CHART got point" << KeyAsString.toInt();

        QVector <QMap <QString,QString>> ResultVector;
        QMap <QString,QString> Record;
        if (!SQLConnection->DoSELECT(ResultVector, "SELECT * FROM [DTdatabase].[dbo].[Rulons] WHERE rulonkey="+KeyAsString,"SQL"))
        {
            qDebug() << "NO DATA for chart";
            return;
        }
        qDebug() << "CHART SELECT * FROM [DTdatabase].[dbo].[Rulons] WHERE rulonkey=" << KeyAsString.toInt();
        Record=ResultVector[0];
        int minY,maxY;

        minY=Record["min"].toInt();
        maxY=Record["max"].toInt();

        SQLConnection->deleteLater();
        RepaintRiftek(&Top100Measures,(float)minY/1000,(float)maxY/1000);
        qDebug() << "CHART RepaintRiftek" << minY << maxY;
        }
}

void ChartFromSQL::RepaintRiftek(QVector<SqlModule::Top100> *Top100Measures, float minY, float maxY)
{
    SqlModule::Top100 OneMeasure;

    // cleaning
    for (int i=0;i<8;i++)
    {
        ui->customPlot->graph(i)->data()->clear();
    }

    if (Top100Measures->count()<=5) return;

    float tBegin,tEnd;
    OneMeasure=Top100Measures->data()[0];
    tBegin=OneMeasure.LIR;
    OneMeasure=Top100Measures->data()[Top100Measures->count()-1];
    tEnd=OneMeasure.LIR;
    ui->customPlot->xAxis->setRange(tBegin, tEnd);
    ui->customPlot->yAxis->setRange(minY-0.1, maxY+0.1);

    qDebug() << "GRAPH tBegin" << tBegin;
    qDebug() << "GRAPH tEnd" << tEnd;

    // max and min
    ui->customPlot->graph(6)->addData(tBegin,maxY);
    ui->customPlot->graph(6)->addData(tEnd,maxY);
    ui->customPlot->graph(7)->addData(tBegin,minY);
    ui->customPlot->graph(7)->addData(tEnd,minY);
    //

    for (int j=0;j<Top100Measures->count();j++)
    {
        OneMeasure=Top100Measures->data()[j];
        float Average=0;
        int AverageMember=0;

        for (int i=0;i<5;i++)
        {
            if (OneMeasure.data.data()[i]>0 &&
               ((i==0 && ui->ch01->isChecked())     ||
                (i==1 && ui->ch02->isChecked())     ||
                (i==2 && ui->ch03->isChecked())     ||
                (i==3 && ui->ch04->isChecked())     ||
                 (i==4 && ui->ch05->isChecked())))
            {
                AverageMember++;
                Average+=(double)OneMeasure.data.data()[i]/1000;
                ui->customPlot->graph(i)->addData(OneMeasure.LIR,(double)OneMeasure.data.data()[i]/1000);
            }
        }

        if (ui->chAll->isChecked() && AverageMember!=0)  // Average
        ui->customPlot->graph(5)->addData(OneMeasure.LIR,Average/AverageMember);}


    ui->customPlot->replot();
}

void ChartFromSQL::on_ch05_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}


void ChartFromSQL::on_ch04_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}


void ChartFromSQL::on_ch03_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}


void ChartFromSQL::on_ch02_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}


void ChartFromSQL::on_ch01_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}


void ChartFromSQL::on_chAll_stateChanged(int arg1)
{
    ShowChart(LaserKey);
}

