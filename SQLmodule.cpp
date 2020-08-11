#include "SQLmodule.h"
#include "inisettings.h"

SqlModule::SqlModule()
{
    ///
}

int SqlModule::SqlConnect()
{
// to delete
}

int SqlModule::SqlGetLast(int GetCount, int GetHours, QVector<Top100> *Top100Measures)
{
    IniSettings *INIFile =new IniSettings;
    QString ServerName=INIFile->GetParamStr("SQL/ServerName");
    QString dbName=INIFile->GetParamStr("SQL/DBName");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
    db.setDatabaseName(dsn);
    if (db.open())
    {
          QString sQuery;
          if (GetHours==0)
          {
          if (GetCount>0)
              {
              sQuery = "SELECT TOP ("+QString::number(GetCount)+") * FROM ["+dbName+"].[dbo].[Measures] ORDER BY cdatetime DESC;";
              } else
              {
              sQuery = "SELECT * FROM ["+dbName+"].[dbo].[Measures] WHERE cdatetime>='"+INIFile->GetParamStr("FilterSQL/From")+"' AND cdatetime<='"+INIFile->GetParamStr("FilterSQL/To")+"' ORDER BY cdatetime DESC;";
              }
          } else
          {
          sQuery = "SELECT * FROM ["+dbName+"].[dbo].[Measures] WHERE cdatetime>='"+QDateTime::currentDateTime().addSecs(-60*60*GetHours).toString(Qt::ISODate)
                  +"' AND cdatetime<='"+QDateTime::currentDateTime().toString(Qt::ISODate)+"' ORDER BY cdatetime DESC;";
          }
          //qDebug() << sQuery;
          QSqlQuery Qry;
          if (Qry.exec(sQuery))
          {
              Qry.last();
              Top100Measures->clear();
              while (Qry.previous())
              {
                  Top100 OneMeasure;
                  OneMeasure.rulon=Qry.value(0).toString();
                  OneMeasure.cdatetime=Qry.value(1).toDateTime();
                  OneMeasure.data.clear();
                  for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
                        {
                        OneMeasure.data.push_back(Qry.value(2+i).toReal());
                        }
                  Top100Measures->push_back(OneMeasure);
                  //Top100Measures->push_front(OneMeasure);
                  OneMeasure.LIR=Qry.value(8).toReal();
                  OneMeasure.SPEED=60*Qry.value(9).toReal();
              }
          } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
          //qDebug() << sQuery;
          db.close();
          delete(INIFile);
    } else
    {
          delete(INIFile);
          qDebug() << "ERROR: " << db.lastError().text();
    }

}

int SqlModule::SqlGetAverageRow(int Minutes,  QVector<float> *AverageRowMeasures)
{
    IniSettings *INIFile =new IniSettings;
    QVector <int> CountVector;
    QString ServerName=INIFile->GetParamStr("SQL/ServerName");
    QString dbName=INIFile->GetParamStr("SQL/DBName");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
    db.setDatabaseName(dsn);
    if (db.open())
    {
          QString sQuery;
          sQuery = "SELECT * FROM ["+dbName+"].[dbo].[Measures] WHERE cdatetime>='"+QDateTime::currentDateTime().addSecs(-60*Minutes).toString(Qt::ISODate)
                  +"' AND cdatetime<='"+QDateTime::currentDateTime().toString(Qt::ISODate)+"' ORDER BY cdatetime DESC;";
          //qDebug() << sQuery;
          QSqlQuery Qry;
          if (Qry.exec(sQuery))
          {
              Qry.last();
              AverageRowMeasures->clear();
              CountVector.clear();
              for (int i=0; i<INIFile->GetParam("Main/NumberOfPairs");i++)
              {
              AverageRowMeasures->push_back(0);
              CountVector.push_back(0);
              }

              while (Qry.previous())
              {
                  for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
                        {
                        if (Qry.value(2+i).toReal()!=0)
                            {
                            AverageRowMeasures->data()[i]=AverageRowMeasures->data()[i]+Qry.value(2+i).toReal()/1000;
                            CountVector.data()[i]++;
                            }
                        }
              }
          } else qDebug() << "SELECT SQL Query is _NOT_ OK ";

          for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
                {
                if (CountVector.data()[i]!=0)
                    {
                    AverageRowMeasures->data()[i]=AverageRowMeasures->data()[i]/CountVector.data()[i];
                    } else { AverageRowMeasures->data()[i]=0; }
                }
          //qDebug() << sQuery;
          db.close();
          delete(INIFile);
    } else
    {
          delete(INIFile);
          qDebug() << "ERROR: " << db.lastError().text();
    }

}

int SqlModule::SqlPutMeasure2(QString rulon, QVector<int> *CurrentData,
                              float LIR, float SPEED)
{
    float ThickValue;
    IniSettings *INIFile =new IniSettings;
    QString ServerName=INIFile->GetParamStr("SQL/ServerName");
    QString dbName=INIFile->GetParamStr("SQL/DBName");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
    db.setDatabaseName(dsn);
    if (db.open())
    {
          QString sQuery;
          sQuery = "INSERT INTO ["+dbName+"].[dbo].[Measures]";
          sQuery = sQuery + " ([rulon],[cdatetime],[c1],[c2],[c3],[c4],[c5],[c6],[LIR],[SPEED])";
          sQuery = sQuery + " VALUES (";
          sQuery = sQuery + "'"+rulon+"',";
          QDateTime CurrentDateTime=QDateTime::currentDateTime();
          sQuery = sQuery + "'"+CurrentDateTime.toString(Qt::ISODate)+"',";

          for (int i=0; i<INIFile->GetParam("Main/NumberOfPairs"); i++)
          {
          ThickValue=CurrentData->data()[i];
          sQuery = sQuery + "'"+QString::number(ThickValue,'f',3)+"'";
          sQuery = sQuery + ",";
          }
          sQuery = sQuery + "'"+QString::number(LIR,'f',3)+"'";
          sQuery = sQuery + ",";
          sQuery = sQuery + "'"+QString::number(SPEED,'f',3)+"'";
          sQuery = sQuery + ");";

          delete(INIFile);
          QSqlQuery Qry;
          //if (ThickValue>0)
            {
            if (Qry.exec(sQuery))
              {
    //            qDebug() << "INSERT OK ";
              } else qDebug() << "INSERT SQL Query is _NOT_ OK ";
          //qDebug() << sQuery;
            }
          db.close();
    } else
    {
          delete(INIFile);
          qDebug() << "ERROR: " << db.lastError().text();
    }
}

int SqlModule::SqlPutMeasure(QString rulon, QVector<int> *Measures)
{
float ThickValue;
IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr("SQL/ServerName");
QString dbName=INIFile->GetParamStr("SQL/DBName");
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setConnectOptions();
QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);
if (db.open())
{    
      QString sQuery;
      sQuery = "INSERT INTO ["+dbName+"].[dbo].[Measures]";
      sQuery = sQuery + " ([rulon],[cdatetime],[c1],[c2],[c3],[c4],[c5],[c6])";
      sQuery = sQuery + " VALUES (";
      sQuery = sQuery + "'"+rulon+"',";
      QDateTime CurrentDateTime=QDateTime::currentDateTime();
      sQuery = sQuery + "'"+CurrentDateTime.toString(Qt::ISODate)+"',";

      for (int i=0; i<INIFile->GetParam("Main/NumberOfPairs"); i++)
      {
      ThickValue=INIFile->GetCalib(i,"Base")-Measures->data()[i]-Measures->data()[i+INIFile->GetParam("Main/NumberOfPairs")];
//      qDebug() << "A" << ThickValue;
      if (Measures->data()[i]==0 || Measures->data()[i+INIFile->GetParam("Main/NumberOfPairs")]==0)
      {
      ThickValue=0;
      }
//      qDebug() << "B" << ThickValue;
      sQuery = sQuery + "'"+QString::number(ThickValue,'f',3)+"'";
      if (i<INIFile->GetParam("Main/NumberOfPairs")-1) { sQuery = sQuery + ","; }
      }
      sQuery = sQuery + ");";
      delete(INIFile);
      QSqlQuery Qry;
      //if (ThickValue>0)
        {
        if (Qry.exec(sQuery))
          {
//            qDebug() << "INSERT OK ";
          } else qDebug() << "INSERT SQL Query is _NOT_ OK ";
      //qDebug() << sQuery;
        }
      db.close();
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}

}

