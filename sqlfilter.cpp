#include "sqlfilter.h"
#include "ui_sqlfilter.h"

SQLFilter::SQLFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLFilter)
{
    ui->setupUi(this);

}

SQLFilter::~SQLFilter()
{
    delete ui;
}


void SQLFilter::UpdateTable()
{
    //
    // types of materials

    ui->tableTypes->setColumnCount(10);
    ui->tableTypes->setColumnWidth(0,30);
    for (int i=1;i<6;i++) {ui->tableTypes->setColumnWidth(i,120);}
    ui->tableTypes->setShowGrid(true);
    ui->tableTypes->setHorizontalHeaderLabels({"#","Дата","Пользователь","Рулон","Длина","Точка1, мм","Точка2, мм","Точка3, мм","Точка4, мм","Точка5, мм"});

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
    if (Qry.exec(sQuery))
    {
        while (Qry.next())
        {
        qDebug() << "SQLFiLTER" << Qry.value("rulonkey").toInt();
        ids.push_back(Qry.value("rulonkey").toInt());
        //SQLConnection->SqlCalculateStatistics(Qry.value("rulonkey").toInt());
        }
    }
    SQLConnection->deleteLater();
    // to delete

    int row=0;
    sQuery = "SELECT * FROM Rulons ORDER BY rulonkey DESC";
    if (Qry.exec(sQuery))
    {
        while (Qry.next())
        {
        ui->tableTypes->setRowCount(row+1);
        ui->tableTypes->setItem(row, 0, new QTableWidgetItem(Qry.value("rulonkey").toString()));
        ui->tableTypes->setItem(row, 1, new QTableWidgetItem(Qry.value("currentdate").toDateTime().toString("dd/MM/yyyy")));
        ui->tableTypes->setItem(row, 2, new QTableWidgetItem(Qry.value("username").toString()));
        ui->tableTypes->setItem(row, 3, new QTableWidgetItem(Qry.value("rulonnumber").toString()));
        ui->tableTypes->setItem(row, 4, new QTableWidgetItem(QString::number((float)Qry.value("rulonlenght").toFloat()/1000,'f',0)));
        ui->tableTypes->setItem(row, 5, new QTableWidgetItem(QString::number((float)Qry.value("av1").toFloat()/1000,'f',2)));
        ui->tableTypes->setItem(row, 6, new QTableWidgetItem(QString::number((float)Qry.value("av2").toFloat()/1000,'f',2)));
        ui->tableTypes->setItem(row, 7, new QTableWidgetItem(QString::number((float)Qry.value("av3").toFloat()/1000,'f',2)));
        ui->tableTypes->setItem(row, 8, new QTableWidgetItem(QString::number((float)Qry.value("av4").toFloat()/1000,'f',2)));
        ui->tableTypes->setItem(row, 9, new QTableWidgetItem(QString::number((float)Qry.value("av5").toFloat()/1000,'f',2)));
        row++;
        }
    }
    }
}


void SQLFilter::on_pushButton_clicked()
{
    //
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->FormXlsReport(0);
    SQLConnection->deleteLater();
}

void SQLFilter::on_pushButton_2_clicked()
{
    this->close();

}

void SQLFilter::on_pushButton_3_clicked()
{
    if (RulonId<=0) return;


    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->SqlCalculateStatistics(RulonId);
    SQLConnection->FormXlsSingleReport(RulonId, 200);
    SQLConnection->deleteLater();
    UpdateTable();
}


void SQLFilter::on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    RulonId=ui->tableTypes->item(currentRow,1)->text().toInt();
}

