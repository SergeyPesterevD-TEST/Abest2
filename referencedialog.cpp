#include "referencedialog.h"
#include "ui_referencedialog.h"

ReferenceDialog::ReferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReferenceDialog)
{
    ui->setupUi(this);
}

ReferenceDialog::~ReferenceDialog()
{
    delete ui;
}

ReferenceDialog::UpdateAll()
{
    // types of materials
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->SqlGetTypes(TypesList);

    ui->tableTypes->setColumnCount(6);

    ui->tableTypes->setColumnWidth(0,30);
    for (int i=1;i<6;i++) {ui->tableTypes->setColumnWidth(i,130);}
    ui->tableTypes->setColumnWidth(1,250);

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

//    struct UsersTypes
//    {
//        int key, shiftnumber, isadmin, isactive;
//        QString username, password, fingerprint;
//    };

    SQLConnection->SqlGetUsers(UsersList);

    ui->UserTypes->setColumnCount(6);
    ui->UserTypes->setColumnWidth(0,30);
    for (int i=1;i<6;i++) {ui->UserTypes->setColumnWidth(i,130);}
    ui->UserTypes->setColumnWidth(1,250);
    ui->UserTypes->setRowCount(UsersList.count());
    ui->UserTypes->setShowGrid(true);

    ui->UserTypes->setHorizontalHeaderLabels({"#","Фамилия ИО","Номер смены","Админ","Активный","Пароль"});


    for (int i=0;i<UsersList.count();i++)
    {
        ui->UserTypes->setItem(i, 0, new QTableWidgetItem(QString::number(UsersList[i].key)));
        ui->UserTypes->setItem(i, 1, new QTableWidgetItem(UsersList[i].username));
        ui->UserTypes->setItem(i, 2, new QTableWidgetItem(QString::number(UsersList[i].shiftnumber)));
        ui->UserTypes->setItem(i, 3, new QTableWidgetItem(QString::number(UsersList[i].isadmin)));
        ui->UserTypes->setItem(i, 4, new QTableWidgetItem(QString::number(UsersList[i].isactive)));
        ui->UserTypes->setItem(i, 5, new QTableWidgetItem(UsersList[i].password));
    }

    SQLConnection->deleteLater();
}

void ReferenceDialog::on_UserTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //
    ui->lineFIO->setText(ui->UserTypes->item(currentRow,1)->text());
    ui->linePSW->setText(ui->UserTypes->item(currentRow,5)->text());
    ui->Shift->setValue(ui->UserTypes->item(currentRow,2)->text().toInt());
    ui->isActive->setChecked(ui->UserTypes->item(currentRow,4)->text().toInt());
    ui->isAdmin->setChecked(ui->UserTypes->item(currentRow,3)->text().toInt());
    GlobalcurrentRow=currentRow;

}


void ReferenceDialog::on_pushButton_2_clicked()
{
    //
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->UpdateSQL("Users", "namekey="+ui->UserTypes->item(GlobalcurrentRow,0)->text(),
        {"username", "password", "shiftnumber", "isactive", "isadmin"},
        {ui->lineFIO->text(), ui->linePSW->text(), QString::number(ui->Shift->value()),
        QString::number(ui->isActive->isChecked()),QString::number(ui->isAdmin->isChecked())});
    SQLConnection->deleteLater();
    UpdateAll();
}


void ReferenceDialog::on_pushButton_clicked()
{
    //
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->InsertSQL("Users",
                             {"username", "password", "shiftnumber", "isactive", "isadmin"},
                             {ui->lineFIO->text(), ui->linePSW->text(), QString::number(ui->Shift->value()),
                              QString::number(ui->isActive->isChecked()),QString::number(ui->isAdmin->isChecked())});
    SQLConnection->deleteLater();
    UpdateAll();
}


void ReferenceDialog::on_pushButton_3_clicked()
{
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->DeleteSQL("Users", "namekey="+ui->UserTypes->item(GlobalcurrentRow,0)->text());
    SQLConnection->deleteLater();
    UpdateAll();
}


void ReferenceDialog::on_tableTypes_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //
    ui->lineProduct->setText(ui->tableTypes->item(currentRow,1)->text());
    ui->NominalThickness->setValue(ui->tableTypes->item(currentRow,3)->text().toFloat());
    ui->ToleranceUp->setValue(ui->tableTypes->item(currentRow,4)->text().toFloat());
    ui->ToleranceDown->setValue(ui->tableTypes->item(currentRow,2)->text().toFloat());
    ui->Offset->setValue(ui->tableTypes->item(currentRow,5)->text().toFloat());
    GlobalcurrentRow2=currentRow;
}


void ReferenceDialog::on_pushButton_4_clicked()
{
    // edit
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->UpdateSQL("Products", "ProductKey="+ui->tableTypes->item(GlobalcurrentRow2,0)->text(),
                             {"ProductName", "NominalThickness", "ToleranceUp", "ToleranceDown", "Offset"},
                             {ui->lineProduct->text(), QString::number(ui->NominalThickness->value()*100),
                             QString::number(ui->ToleranceUp->value()*100),
                             QString::number(ui->ToleranceDown->value()*100),
                             QString::number(ui->Offset->value()*100)});

    SQLConnection->deleteLater();
    UpdateAll();
}


void ReferenceDialog::on_pushButton_6_clicked()
{
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->InsertSQL("Products",
                             {"ProductName", "NominalThickness", "ToleranceUp", "ToleranceDown", "Offset"},
                             {ui->lineProduct->text(), QString::number(ui->NominalThickness->value()*100),
                              QString::number(ui->ToleranceUp->value()*100),
                              QString::number(ui->ToleranceDown->value()*100),
                              QString::number(ui->Offset->value()*100)});

    SQLConnection->deleteLater();
    UpdateAll();
}


void ReferenceDialog::on_pushButton_5_clicked()
{
    SqlModule *SQLConnection=new SqlModule;
    SQLConnection->DeleteSQL("Products", "ProductKey="+ui->tableTypes->item(GlobalcurrentRow2,0)->text());
    SQLConnection->deleteLater();
    UpdateAll();
}

