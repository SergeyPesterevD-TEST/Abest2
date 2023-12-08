#include "sqlfilter.h"
#include "ui_sqlfilter.h"

SQLFilter::SQLFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLFilter)
{
    ui->setupUi(this);
    FilterString="";
    ChartFromSQLForm = new ChartFromSQL;
}

SQLFilter::~SQLFilter()
{
    delete ui;
}


void SQLFilter::UpdateTable()
{
    //
    // types of materials

    ui->tableTypes->setColumnCount(13);
    ui->tableTypes->setColumnWidth(0,30);
    for (int i=1;i<13;i++) {ui->tableTypes->setColumnWidth(i,60);}
    for (int i=1;i<6;i++) {ui->tableTypes->setColumnWidth(i,110);}
    ui->tableTypes->setShowGrid(true);
    ui->tableTypes->setHorizontalHeaderLabels({"#","Дата","Пользователь","Рулон","Тип","Длина","Т1, мм","Т2, мм","Т3, мм","Т4, мм","Т5, мм","Tav,mm","STDEV"});

    IniSettings *INIFile =new IniSettings;
    QString ServerName=INIFile->GetParamStr("SQL/ServerName");
    QString dbName=INIFile->GetParamStr("SQL/DBName");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
    db.setDatabaseName(dsn);    

    if (db.open())
    {
    // to delete
    QString sQuery;
    QSqlQuery Qry;
    sQuery = "SELECT * FROM Rulons";


    SqlModule *SQLConnection=new SqlModule;
    QVector <int> ids;
    ids.clear();


    Qry.setForwardOnly(true);
    Qry.prepare(sQuery);

    if (Qry.exec(sQuery))
    {
        while (Qry.next())
        {
        //qDebug() << "SQLFiLTER" << Qry.value("rulonkey").toInt();
        ids.push_back(Qry.value("rulonkey").toInt());
        //SQLConnection->SqlCalculateStatistics(Qry.value("rulonkey").toInt());
        }
    }
    SQLConnection->deleteLater();
    // to delete

    int row=0;
    sQuery = "SELECT * FROM Rulons ";

    QString filter="";

    if (ui->filDate->text()!="") { filter+=" CONVERT(VARCHAR(10), currentdate, 103) LIKE '%"+ui->filDate->text()+"%' ";    }

    if (ui->filRulon->text()!="")
    {
        if (filter!="") { filter+=" AND ";}
        filter+=" rulonnumber LIKE '%"+ui->filRulon->text()+"%' ";
    }
    if (ui->filUser->text()!="")
    {
        if (filter!="") { filter+=" AND ";}
        filter+=" username LIKE '%"+ui->filUser->text()+"%' ";
    }
    if (filter!="")
    {
        sQuery += " WHERE "+filter;
    }
    if (filter!="") { FilterString=" WHERE "+filter+" ORDER BY rulonkey DESC"; } else
        { FilterString=""; }
    sQuery+=" ORDER BY rulonkey DESC";


    Qry.setForwardOnly(true);
    Qry.prepare(sQuery);

    if (Qry.exec(sQuery))
    {
        while (Qry.next())
        {
        ui->tableTypes->setRowCount(row+1);
        ui->tableTypes->setItem(row, 0, new QTableWidgetItem(Qry.value("rulonkey").toString()));
        ui->tableTypes->setItem(row, 1, new QTableWidgetItem(Qry.value("currentdate").toDateTime().toString("dd/MM/yyyy")));
        ui->tableTypes->setItem(row, 2, new QTableWidgetItem(Qry.value("username").toString()));
        ui->tableTypes->setItem(row, 3, new QTableWidgetItem(Qry.value("rulonnumber").toString()));
        ui->tableTypes->setItem(row, 4, new QTableWidgetItem(Qry.value("product").toString()));
        ui->tableTypes->setItem(row, 5, new QTableWidgetItem(QString::number((float)Qry.value("rulonlenght").toFloat()/1000,'f',0)));
        ui->tableTypes->setItem(row, 6, new QTableWidgetItem(QString::number((float)Qry.value("av1").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 7, new QTableWidgetItem(QString::number((float)Qry.value("av2").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 8, new QTableWidgetItem(QString::number((float)Qry.value("av3").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 9, new QTableWidgetItem(QString::number((float)Qry.value("av4").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 10, new QTableWidgetItem(QString::number((float)Qry.value("av5").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 11, new QTableWidgetItem(QString::number((float)Qry.value("av").toFloat()/1000000,'f',3)));
        ui->tableTypes->setItem(row, 12, new QTableWidgetItem(QString::number((float)Qry.value("stdev").toFloat()/1000000,'f',3)));
        row++;
        }
        if (row==0) {ui->tableTypes->setRowCount(0);}
    } else ui->tableTypes->setRowCount(0);
    }
}


void SQLFilter::on_pushButton_clicked()
{
    //
    SqlModule *SQLConnection=new SqlModule;
    IniSettings *INIFile =new IniSettings;
    SQLConnection->FormXlsReport(0, FilterString);
    SQLConnection->deleteLater();

    QProcess *process = new QProcess(this);
    QString file = INIFile->GetParamStr("ExcelPath");
    QStringList arguments;
    arguments << "c:\\xls\\output.xlsx";
    process->start(file, arguments);
    delete(INIFile);
}

void SQLFilter::on_pushButton_2_clicked()
{
    this->close();

}

void SQLFilter::on_pushButton_3_clicked()
{
    qDebug() << "RulonDI=" << RulonId;
    if (RulonId<=0) return;
    if (ui->tableTypes->item(GlobalcurrentRow,5)->text().toInt()<100) return;

    SqlModule *SQLConnection=new SqlModule;
    IniSettings *INIFile =new IniSettings;

    SQLConnection->SqlCalculateStatistics(RulonId);
    SQLConnection->FormXlsSingleReport(RulonId, INIFile->GetParam("IncReg"));

    QProcess *process = new QProcess(this);
    QString file = INIFile->GetParamStr("ExcelPath");
    QStringList arguments;
    arguments << "c:\\xls\\output2.xlsx";
    process->start(file, arguments);

    delete(INIFile);
    SQLConnection->deleteLater();
    UpdateTable();
}


void SQLFilter::on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    RulonId=ui->tableTypes->item(currentRow,0)->text().toInt();
    GlobalcurrentRow=currentRow;
    qDebug() << "RulonDI" << currentRow << ui->tableTypes->item(currentRow,0)->text().toInt();
}


void SQLFilter::on_FilterButton_clicked()
{
   // apply filter
   UpdateTable();
}


void SQLFilter::on_FilterReset_clicked()
{
    // reset filter
   ui->filDate->setText("");
   ui->filRulon->setText("");
   ui->filUser->setText("");
   UpdateTable();
}


void SQLFilter::on_pushButton_4_clicked()
{
   CDialog = new ConfirmationDialog;
   CDialog->SetMessage("Удалить данный протокол ?");
   CDialog->showNormal();
   CDialog->move(350,300);
   CDialog->setWindowFlags(Qt::FramelessWindowHint);

   QString mText;
   if(CDialog->exec() == QDialog::Accepted)
   {
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->DeleteSQL("Measures","RulonKey="+ui->tableTypes->item(GlobalcurrentRow,0)->text());
    SQLConnection->DeleteSQL("Rulons","RulonKey="+ui->tableTypes->item(GlobalcurrentRow,0)->text());

    SQLConnection->deleteLater();
    UpdateTable();
   }
   CDialog->deleteLater();
}


void SQLFilter::on_pushButton_5_clicked()
{
    //

   ui->filDate->setText(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
   UpdateTable();
}


void SQLFilter::on_ChartButton_clicked()
{
   ChartFromSQLForm->showFullScreen();
   ChartFromSQLForm->ShowChart(ui->tableTypes->item(GlobalcurrentRow,0)->text());
}

