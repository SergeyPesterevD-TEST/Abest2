#include "newrulondialog.h"
#include "ui_newrulondialog.h"

NewRulonDialog::NewRulonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRulonDialog)
{
    ui->setupUi(this);
}

NewRulonDialog::~NewRulonDialog()
{
    delete ui;
}


void NewRulonDialog::updateAll()
{
    // types of materials
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->SqlGetTypes(TypesList);

    ui->tableTypes->setColumnCount(6);

    ui->tableTypes->setColumnWidth(0,30);
    for (int i=1;i<6;i++) {ui->tableTypes->setColumnWidth(i,130);}

    ui->tableTypes->setRowCount(TypesList.count());
    ui->tableTypes->setShowGrid(true);

    ui->tableTypes->setHorizontalHeaderLabels({"#","Тип картона","Мин, мм","Номинал, мм","Макс, мм","Смещение, мм"});

    for (int i=0;i<TypesList.count();i++)
    {
        ui->tableTypes->setItem(i, 0, new QTableWidgetItem(QString::number(TypesList[i].key)));
        ui->tableTypes->setItem(i, 1, new QTableWidgetItem(TypesList[i].name));
        ui->tableTypes->setItem(i, 2, new QTableWidgetItem(QString::number((float)TypesList[i].min/100,'f',2)));
        ui->tableTypes->setItem(i, 3, new QTableWidgetItem(QString::number((float)TypesList[i].target/100,'f',2)));
        ui->tableTypes->setItem(i, 4, new QTableWidgetItem(QString::number((float)TypesList[i].max/100,'f',2)));
        ui->tableTypes->setItem(i, 5, new QTableWidgetItem(QString::number((float)TypesList[i].offset/100,'f',2)));
    }

    // users
    // UsersComboBox
//    SQLConnection->SqlGetUsers(UsersList);
//    for (int i=0;i<UsersList.count();i++)
//    {
//        ui->UsersComboBox->addItem(UsersList[i].username,UsersList[i].key);
//    }
    ui->UsersComboBox->clear();
    ui->UsersComboBox->addItem(Rulon.username);

    // other field

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    ui->lineDate->setText(current_date);

    SQLConnection->deleteLater();
}


void NewRulonDialog::on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //
    ui->lineType->setText(ui->tableTypes->item(currentRow,1)->text());
    min=ui->tableTypes->item(currentRow,2)->text().toFloat();
    nominal=ui->tableTypes->item(currentRow,3)->text().toFloat();
    max=ui->tableTypes->item(currentRow,4)->text().toFloat();
    offset=ui->tableTypes->item(currentRow,5)->text().toFloat();
}


void NewRulonDialog::on_buttonBox_accepted()
{
    //Rulon.username=ui->UsersComboBox->currentText();
    Rulon.min=min;
    Rulon.nominal=nominal;
    Rulon.max=max;
    Rulon.offset=offset;
    Rulon.currentdate=ui->lineDate->text();
    Rulon.rulontype=ui->lineType->text();
    Rulon.rulonnumber=ui->lineRulon->text();

    SqlModule *SQLConnection=new SqlModule;
    RulonId=SQLConnection->SqlAddNewRulon(Rulon);
    SQLConnection->deleteLater();
    qDebug() << "RulonID=" << RulonId;

}


void NewRulonDialog::on_buttonBox_rejected()
{
    //
}

