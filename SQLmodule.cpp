#include "SQLmodule.h"
#include "inisettings.h"

SqlModule::SqlModule()
{
    ///
}

int SqlModule::SqlConnect()
{
//
}

//SQLConnection->SqlGetRulon(NewRulonForm->RulonId, &Top100Measures); // get last points
int SqlModule::SqlGetRulon(int RulonId, QVector<Top100> *Top100Measures)
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
        //sQuery = "SELECT MAX(LIR) as MAXLIR FROM ["+dbName+"].[dbo].[Measures] WHERE rulonkey="+QString::number(RulonId);
        sQuery = "SELECT TOP 1 LIR as MAXLIR FROM ["+dbName+"].[dbo].[Measures] WHERE rulonkey="+QString::number(RulonId)+" order by MeasureKey desc";
        QSqlQuery Qry;
        float MAXLIR;

        Qry.setForwardOnly(true);
        Qry.prepare(sQuery);

        if (Qry.exec(sQuery))
        {
        Qry.first();
        MAXLIR=Qry.value("MAXLIR").toFloat();
        }
        qDebug() << "CuttingEdges" << MAXLIR;

        sQuery =  "SELECT * FROM ["+dbName+"].[dbo].[Measures] ";
        sQuery += "WHERE rulonkey="+QString::number(RulonId)+" AND LIR>"+INIFile->GetParamStr("Plot/cutBegin");
        sQuery += " AND LIR<"+QString::number(MAXLIR-INIFile->GetParam("Plot/cutEnd"))+" ORDER BY cdatetime DESC;";
        qDebug() << "CuttingEdges" << sQuery;

        Qry.setForwardOnly(true);
        Qry.prepare(sQuery);

        if (Qry.exec(sQuery))
        {
            //Qry.last();
            Top100Measures->clear();
            float OLDLIR=1000000;
            while (Qry.next())
            {
                Top100 OneMeasure;
                OneMeasure.rulon=Qry.value("RulonKey").toString();
                OneMeasure.cdatetime=Qry.value("cdatetime").toDateTime();
                OneMeasure.data.clear();
                for (int i=1;i<INIFile->GetParam("Main/NumberOfPairs")+1;i++)
                {
                    OneMeasure.data.push_back(Qry.value("c"+QString::number(i)).toReal());
                    //qDebug() << "ADDPOINT" << "c"+QString::number(i) << Qry.value("c"+QString::number(i)).toReal();
                }
                OneMeasure.LIR=Qry.value("LIR").toReal();
                OneMeasure.SPEED=60*Qry.value("SPEED").toReal();
                if (OneMeasure.LIR<OLDLIR)
                Top100Measures->push_back(OneMeasure);
                OLDLIR=OneMeasure.LIR;
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

          Qry.setForwardOnly(true);
          Qry.prepare(sQuery);

          if (Qry.exec(sQuery))
          {
              Qry.last();
              Top100Measures->clear();
              while (Qry.previous())
              {
                  Top100 OneMeasure;
                  OneMeasure.rulon=Qry.value("RulonKey").toString();
                  OneMeasure.cdatetime=Qry.value("cdatetime").toDateTime();
                  OneMeasure.data.clear();
                  for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
                        {
                        OneMeasure.data.push_back(Qry.value("c"+QString::number(i)).toReal());
                        }
                  Top100Measures->push_back(OneMeasure);
                  //Top100Measures->push_front(OneMeasure);
                  OneMeasure.LIR=Qry.value("LIR").toReal();
                  OneMeasure.SPEED=60*Qry.value("SPEED").toReal();
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

          Qry.setForwardOnly(true);
          Qry.prepare(sQuery);

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
                        if (Qry.value("c"+QString::number(i)).toReal()!=0)
                            {
                            AverageRowMeasures->data()[i]=AverageRowMeasures->data()[i]+Qry.value("c"+QString::number(i)).toReal()/1000;
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

int SqlModule::SqlPutMeasure2(int rulon, QVector<int> *CurrentData,
                              float LIR, float SPEED)
{
    if (rulon==-1) return -1;
    if (LIR==0) return 0;

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
          sQuery = sQuery + " ([RulonKey],[cdatetime],[c1],[c2],[c3],[c4],[c5],[LIR],[SPEED])";
          sQuery = sQuery + " VALUES (";
          sQuery = sQuery + QString::number(rulon)+",";
          QDateTime CurrentDateTime=QDateTime::currentDateTime();
          sQuery = sQuery + "'"+CurrentDateTime.toString(Qt::ISODate)+"',";

          int TotalThick=0;
          for (int i=0; i<INIFile->GetParam("Main/NumberOfPairs"); i++)
          {
          ThickValue=CurrentData->data()[i];
          TotalThick=TotalThick+CurrentData->data()[i];
          sQuery = sQuery + "'"+QString::number(ThickValue,'f',3)+"'";
          sQuery = sQuery + ",";
          }
          sQuery = sQuery + "'"+QString::number(LIR,'f',3)+"'";
          sQuery = sQuery + ",";
          sQuery = sQuery + "'"+QString::number(SPEED,'f',3)+"'";
          sQuery = sQuery + ");";

          delete(INIFile);
          qDebug() << sQuery;
          QSqlQuery Qry;
          if (TotalThick>0)
            {

            Qry.setForwardOnly(true);
            Qry.prepare(sQuery);

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
        Qry.setForwardOnly(true);
        Qry.prepare(sQuery);

        if (Qry.exec(sQuery))
          {
          //qDebug() << "INSERT OK ";
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


int SqlModule::SqlGetTypes(QVector <CartonTypes> &TypesList)
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
      sQuery = "SELECT * FROM Products ORDER BY productName";
      QSqlQuery Qry;
      TypesList.clear();

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          while (Qry.next())
          {
          CartonTypes OneRecord;
          OneRecord.key=Qry.value("ProductKey").toInt();
          OneRecord.name=Qry.value("ProductName").toString();
          OneRecord.target=Qry.value("NominalThickness").toInt();
          OneRecord.max=Qry.value("ToleranceUp").toInt();
          OneRecord.min=Qry.value("ToleranceDown").toInt();
          OneRecord.offset=Qry.value("Offset").toInt();
          OneRecord.interval=Qry.value("Interval").toInt();
          TypesList.push_back(OneRecord);
          }
      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
      db.close();
      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}
}


// SqlGetUsers(UsersList);
int SqlModule::SqlGetUsers(QVector <UsersTypes> &UsersList, QString ifs)
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
      sQuery = "SELECT * FROM Users WHERE isactive=1 ";
      if (ifs!="") {sQuery=sQuery+" AND "+ifs;}
      sQuery= sQuery+" ORDER BY username";

      QSqlQuery Qry;
      UsersList.clear();

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          while (Qry.next())
          {
          UsersTypes OneRecord;
          OneRecord.key=Qry.value("namekey").toInt();
          OneRecord.username=Qry.value("username").toString();
          OneRecord.password=Qry.value("password").toString();
          OneRecord.shiftnumber=Qry.value("shiftnumber").toInt();
          OneRecord.isadmin=Qry.value("isadmin").toInt();
          OneRecord.isactive=Qry.value("isactive").toInt();
          OneRecord.fingerprint=Qry.value("fingerprint").toInt();
          UsersList.push_back(OneRecord);
          }
      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
      db.close();
      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}
}

// SqlAddNewRulon
int SqlModule::SqlAddNewRulon(CurrentRulon &rulon)
{
IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr("SQL/ServerName");
QString dbName=INIFile->GetParamStr("SQL/DBName");
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setConnectOptions();
QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);
int result=-1;

if (db.open())
{
      //insert
      QString sQuery;
      sQuery = "set dateformat ymd \n INSERT INTO Rulons ([currentdate],[username],[rulonnumber],[product],[max],[min],[nominal])";
      sQuery +=" VALUES ('"+rulon.currentdate+"','"+rulon.username+"','"+rulon.rulonnumber;
      sQuery +=" ','"+rulon.rulontype+"',"+QString::number(rulon.max*1000)+","+QString::number(rulon.min*1000)+","+QString::number(rulon.nominal*1000)+")";
      qDebug() << "complicated INSERT" << sQuery;

      QSqlQuery Qry;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      Qry.exec(sQuery);

      //get id
      sQuery = "SELECT * FROM Rulons order by rulonkey desc";

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          if (Qry.next())
          {
          result=Qry.value("rulonkey").toInt();
          }
      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
      db.close();
      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}
return result;
}

int SqlModule::SqlCalculateStatistics(int RulonId)
{
QVector<float> Averages;
Averages.clear();

double allaverage;
double stdev;
double variable;
double asymmetry;
double kurtosis;
double length;

QVector <qint16> v1;

IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr("SQL/ServerName");
QString dbName=INIFile->GetParamStr("SQL/DBName");
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setConnectOptions();
QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);
if (db.open())
{
      QString sQuery, sLIRQuery;
      sQuery = "SELECT MAX(LIR) as MAXLIR FROM ["+dbName+"].[dbo].[Measures] WHERE rulonkey="+QString::number(RulonId);

      qDebug() << "STTAT" << sQuery;

      QSqlQuery Qry;
      float MAXLIR;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          Qry.first();
          MAXLIR=Qry.value("MAXLIR").toFloat();
      }

      sLIRQuery =  " AND LIR>"+INIFile->GetParamStr("Plot/cutBegin")+" AND LIR<"+QString::number(MAXLIR-INIFile->GetParam("Plot/cutEnd"));

      sQuery = "SELECT AVG(c1) as 'ac1',AVG(c2) as 'ac2',AVG(c3) as 'ac3',AVG(c4) as 'ac4',AVG(c5) as 'ac5',";
      //sQuery += "STDEV((c1+c2+c3+c4+c5)/5) as 'stdev', MAX(LIR) as 'LIR', AVG((c1+c2+c3+c4+c5)/5) as AllAverage FROM Measures WHERE c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;
      sQuery += "STDEV((c1+c2+c3+c4+c5)/5) as 'stdev', MAX(LIR) as 'LIR', AVG((c1+c2+c3+c4+c5)/5) as AllAverage FROM Measures WHERE c1+c2+c3+c4+c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;

      qDebug() << "STTAT" << sQuery;

      int Counter=0;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          while (Qry.next())
          {
          Counter++;
          for (int i=1;i<6;i++)
            {
            float value=Qry.value("ac"+QString::number(i)).toReal();
            Averages.push_back(value);
            }
          allaverage=Qry.value("AllAverage").toReal();
          stdev=Qry.value("stdev").toReal();
          length=MAXLIR;
          qDebug() << "STTAT STEP1" << allaverage << stdev << length;
          if (allaverage!=0) { variable=stdev/allaverage;} else { variable=0; }
          }
          qDebug() << "STTAT STEP1" << Counter;
          if (Counter<=0) return -1;

      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";

      // next stage
      sQuery = "SELECT (c1+c2+c3+c4+c5)/5 AS c FROM Measures WHERE  c1+c2+c3+c4+c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;
      v1.clear();
      Counter=0;

      qDebug() << "STTAT" << sQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          //          double asymmetry;
          //          double kurtosis;
          //          QVector <qint16> v1;
          while (Qry.next())
          {
          Counter++;
          v1.push_back(Qry.value("c").toReal());
          }
          qDebug() << "STTAT STEP2" << Counter;
          if (Counter<=0) return -1;

      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";

      Statistics *Stats =new Statistics;
      asymmetry=0;
      kurtosis=0;

      try
      {
      Stats->GetKurtosisAndAsymmetry(v1,asymmetry,kurtosis);
      }
      catch (...) {
      qDebug() << "STTAT Error GetKurtosisAndAsymmetry function";
      }
      delete(Stats);

      if (QString::number(asymmetry)=="nan") {asymmetry=0;}
      if (QString::number(kurtosis)=="nan") {kurtosis=0;}

      qDebug() << "STTAT Averages" << Averages;
      qDebug() << "STTAT AllAverages" <<  allaverage;
      qDebug() << "STTAT STDEV" << stdev;
      qDebug() << "STTAT VAR " << variable;
      qDebug() << "STTAT Asym" << asymmetry;
      qDebug() << "STTAT Kurtosis" << kurtosis;
      qDebug() << "STTAT Length" << length;

      sQuery = "UPDATE Rulons SET ";
      sQuery += "[av1] = "+QString::number(Averages[0]*1000);
      sQuery += ",[av2] = "+QString::number(Averages[1]*1000);
      sQuery += ",[av3] = "+QString::number(Averages[2]*1000);
      sQuery += ",[av4] = "+QString::number(Averages[3]*1000);
      sQuery += ",[av5] = "+QString::number(Averages[4]*1000);
      sQuery += ",[av] = "+QString::number(allaverage*1000);
      sQuery += ",[stdev] = "+QString::number(stdev*1000);
      sQuery += ",[variablity] = "+QString::number(variable*1000);
      sQuery += ",[assymetria] = "+QString::number(asymmetry*1000);
      sQuery += ",[excess] = "+QString::number(kurtosis*1000);
      sQuery += ",[rulonlenght] = "+QString::number(length*1000);
      sQuery += " WHERE rulonkey="+QString::number(RulonId);
      qDebug() << "STTAT " <<  sQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      Qry.exec(sQuery);
      qDebug() << sQuery;

      db.close();
      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}

}

void SqlModule::FormXlsReport(int RulonId, QString FilterString)
{
//![0]
QXlsx::Document xlsx("C:\\XLS\\report1.xlsx");
//![0]

IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr("SQL/ServerName");
QString dbName=INIFile->GetParamStr("SQL/DBName");
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setConnectOptions();
QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);

QXlsx::Format format, format0;
format.setNumberFormat("0.000");
format0.setNumberFormat("0");

int row=3;
if (db.open())
{     
      //insert      
      QString sQuery;
      sQuery = "SELECT * FROM Rulons "+FilterString;
      QSqlQuery Qry;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          while (Qry.next())
          {
          xlsx.write("A"+QString::number(row),Qry.value("currentdate").toString().mid(0,10));
          xlsx.write("B"+QString::number(row),Qry.value("username").toString());
          xlsx.write("C"+QString::number(row),Qry.value("rulonnumber").toString());
          xlsx.write("D"+QString::number(row),CutFloat(Qry.value("av1").toFloat()/1000000),format);
          xlsx.write("E"+QString::number(row),CutFloat(Qry.value("av2").toFloat()/1000000),format);
          xlsx.write("F"+QString::number(row),CutFloat(Qry.value("av3").toFloat()/1000000),format);
          xlsx.write("G"+QString::number(row),CutFloat(Qry.value("av4").toFloat()/1000000),format);
          xlsx.write("H"+QString::number(row),CutFloat(Qry.value("av5").toFloat()/1000000),format);
          xlsx.write("I"+QString::number(row),CutFloat(Qry.value("av").toFloat()/1000000),format);
          xlsx.write("J"+QString::number(row),CutFloat(Qry.value("stdev").toFloat()/1000000),format);
          xlsx.write("K"+QString::number(row),CutFloat(Qry.value("variablity").toFloat()/1000),format);
          xlsx.write("L"+QString::number(row),CutFloat(Qry.value("assymetria").toFloat()/1000),format);
          xlsx.write("M"+QString::number(row),CutFloat(Qry.value("excess").toFloat()/1000),format);

          row++;
          }
      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
      db.close();
      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}
xlsx.saveAs("c:\\XLS\\output.xlsx");

}


void SqlModule::FormXlsSingleReport(int RulonId, float delta)
{
//![0]
QXlsx::Document xlsx("C:\\XLS\\report2.xlsx");
//![0]

IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr("SQL/ServerName");
QString dbName=INIFile->GetParamStr("SQL/DBName");
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setConnectOptions();
QString dsn=INIFile->GetParamStr("SQL/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);

QXlsx::Format format, format0;
format.setNumberFormat("0.000");
format0.setNumberFormat("0");

int row=6;
float oldposition=0;
if (db.open())
{
      QString sQuery, sLIRQuery;
      QSqlQuery Qry;

      sQuery = "SELECT * FROM Rulons WHERE rulonkey="+QString::number(RulonId);

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          Qry.next();
          QString product=Qry.value("product").toString();
          sQuery = "SELECT * FROM Products WHERE ProductName='"+product+"'";

          Qry.setForwardOnly(true);
          Qry.prepare(sQuery);

          if (Qry.exec(sQuery))
          {
          Qry.next();
          delta=Qry.value("Interval").toFloat()/100;
          }
      }

      //insert


      sQuery = "SELECT MAX(LIR) as MAXLIR FROM ["+dbName+"].[dbo].[Measures] WHERE rulonkey="+QString::number(RulonId);
      float MAXLIR;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          Qry.first();
          MAXLIR=Qry.value("MAXLIR").toFloat();
      }
      sLIRQuery =  " AND LIR>"+INIFile->GetParamStr("Plot/cutBegin")+" AND LIR<"+QString::number(MAXLIR-INIFile->GetParam("Plot/cutEnd"));

      sQuery = "SELECT *  FROM Measures WHERE  c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          while (Qry.next())
          {
          if (oldposition==0 || Qry.value("LIR").toFloat()-oldposition>delta)
            {
            oldposition=Qry.value("LIR").toFloat();
            xlsx.write("A"+QString::number(row),"Толщина на длине "+QString::number(Qry.value("LIR").toFloat(),'f',0),format0);
            xlsx.write("B"+QString::number(row),Qry.value("c1").toFloat()/1000,format);
            xlsx.write("C"+QString::number(row),Qry.value("c2").toFloat()/1000,format);
            xlsx.write("D"+QString::number(row),Qry.value("c3").toFloat()/1000,format);
            xlsx.write("E"+QString::number(row),Qry.value("c4").toFloat()/1000,format);
            xlsx.write("F"+QString::number(row),Qry.value("c5").toFloat()/1000,format);
            row++;
            }
          }
      }

      QVector <float> Averages;
      Averages.clear();

      sQuery = "SELECT * FROM Rulons WHERE rulonkey="+QString::number(RulonId);

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          if (Qry.next())
          {
          xlsx.write("B1",Qry.value("currentdate").toString().mid(0,10));
          xlsx.write("B3",Qry.value("username").toString());
          xlsx.write("B2",Qry.value("rulonnumber").toString());
          xlsx.write("F1",Qry.value("product").toString());
          xlsx.write("F2",Qry.value("rulonlenght").toFloat()/1000,format0);

          xlsx.write("A"+QString::number(row),"Средняя толщина по каждому каналу, мм");
          xlsx.write("A"+QString::number(row+1),"Максимальное значение, мм");
          xlsx.write("A"+QString::number(row+2),"Минимальное значение, мм");
          xlsx.write("A"+QString::number(row+3),"Среднеквадратичное отклонение");
          xlsx.write("A"+QString::number(row+4),"Коэффициент вариации");
          xlsx.write("A"+QString::number(row+5),"Показатель асимметрии");
          xlsx.write("A"+QString::number(row+6),"Показатель эксцесса");

          xlsx.write("B"+QString::number(row),CutFloat(Qry.value("av1").toFloat()/1000000),format);
          xlsx.write("C"+QString::number(row),CutFloat(Qry.value("av2").toFloat()/1000000),format);
          xlsx.write("D"+QString::number(row),CutFloat(Qry.value("av3").toFloat()/1000000),format);
          xlsx.write("E"+QString::number(row),CutFloat(Qry.value("av4").toFloat()/1000000),format);
          xlsx.write("F"+QString::number(row),CutFloat(Qry.value("av5").toFloat()/1000000),format);

          Averages.push_back(Qry.value("av1").toFloat()/1000000);
          Averages.push_back(Qry.value("av2").toFloat()/1000000);
          Averages.push_back(Qry.value("av3").toFloat()/1000000);
          Averages.push_back(Qry.value("av4").toFloat()/1000000);
          Averages.push_back(Qry.value("av5").toFloat()/1000000);
          }
      } else qDebug() << "SELECT SQL Query is _NOT_ OK ";


      sQuery = "SELECT MAX(c1) as c1, MAX(c2) as c2, MAX(c3) as c3, MAX(c4) as c4, MAX(c5) as c5 FROM Measures WHERE  c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          if (Qry.next())
          {
          xlsx.write("B"+QString::number(row+1),CutFloat(Qry.value("c1").toFloat()/1000),format);
          xlsx.write("C"+QString::number(row+1),CutFloat(Qry.value("c2").toFloat()/1000),format);
          xlsx.write("D"+QString::number(row+1),CutFloat(Qry.value("c3").toFloat()/1000),format);
          xlsx.write("E"+QString::number(row+1),CutFloat(Qry.value("c4").toFloat()/1000),format);
          xlsx.write("F"+QString::number(row+1),CutFloat(Qry.value("c5").toFloat()/1000),format);
          }
      }

      sQuery = "SELECT MIN(c1) as c1, MIN(c2) as c2, MIN(c3) as c3, MIN(c4) as c4, MIN(c5) as c5 FROM Measures WHERE  c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          if (Qry.next())
          {
          xlsx.write("B"+QString::number(row+2),CutFloat(Qry.value("c1").toFloat()/1000),format);
          xlsx.write("C"+QString::number(row+2),CutFloat(Qry.value("c2").toFloat()/1000),format);
          xlsx.write("D"+QString::number(row+2),CutFloat(Qry.value("c3").toFloat()/1000),format);
          xlsx.write("E"+QString::number(row+2),CutFloat(Qry.value("c4").toFloat()/1000),format);
          xlsx.write("F"+QString::number(row+2),CutFloat(Qry.value("c5").toFloat()/1000),format);
          }
      }

      sQuery = "SELECT STDEV(c1) as c1, STDEV(c2) as c2, STDEV(c3) as c3, STDEV(c4) as c4, STDEV(c5) as c5 FROM Measures WHERE  c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and rulonkey="+QString::number(RulonId)+sLIRQuery;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      if (Qry.exec(sQuery))
      {
          if (Qry.next())
          {
          xlsx.write("B"+QString::number(row+3),CutFloat(Qry.value("c1").toFloat()/1000),format);
          xlsx.write("C"+QString::number(row+3),CutFloat(Qry.value("c2").toFloat()/1000),format);
          xlsx.write("D"+QString::number(row+3),CutFloat(Qry.value("c3").toFloat()/1000),format);
          xlsx.write("E"+QString::number(row+3),CutFloat(Qry.value("c4").toFloat()/1000),format);
          xlsx.write("F"+QString::number(row+3),CutFloat(Qry.value("c5").toFloat()/1000),format);

          if (Averages[0]!=0) xlsx.write("B"+QString::number(row+4),CutFloat(Qry.value("c1").toFloat()/1000/Averages[0]),format);
          if (Averages[1]!=0) xlsx.write("C"+QString::number(row+4),CutFloat(Qry.value("c2").toFloat()/1000/Averages[1]),format);
          if (Averages[2]!=0) xlsx.write("D"+QString::number(row+4),CutFloat(Qry.value("c3").toFloat()/1000/Averages[2]),format);
          if (Averages[3]!=0) xlsx.write("E"+QString::number(row+4),CutFloat(Qry.value("c4").toFloat()/1000/Averages[3]),format);
          if (Averages[4]!=0) xlsx.write("F"+QString::number(row+4),CutFloat(Qry.value("c5").toFloat()/1000/Averages[4]),format);
          }
      }

      sQuery = "SELECT * FROM Measures WHERE  c1<>0 and c2<>0 and c3<>0 and c4<>0 and c5<>0 and  rulonkey="+QString::number(RulonId)+sLIRQuery;
      double asymmetry;
      double kurtosis;
      QVector <qint16> v1;

      for (int i=1;i<6;i++)
        {
        v1.clear();
        Qry.setForwardOnly(true);
        Qry.prepare(sQuery);

        if (Qry.exec(sQuery))
                {
                  while (Qry.next())
                    {
                    v1.push_back(Qry.value("c"+QString::number(i)).toReal());
                    }
                } else qDebug() << "SELECT SQL Query is _NOT_ OK ";

        Statistics *Stats =new Statistics;
                try
                {
                    Stats->GetKurtosisAndAsymmetry(v1,asymmetry,kurtosis);
                }
                catch (...) {
                    qDebug() << "STTAT Error GetKurtosisAndAsymmetry function";
                }
        delete(Stats);

        QString Column;
        if (i==1) Column="B";
        if (i==2) Column="C";
        if (i==3) Column="D";
        if (i==4) Column="E";
        if (i==5) Column="F";

        xlsx.write(Column+QString::number(row+5),asymmetry,format);
        xlsx.write(Column+QString::number(row+6),kurtosis,format);

      }

      delete(INIFile);
} else
{
      delete(INIFile);
      qDebug() << "ERROR: " << db.lastError().text();
}
xlsx.saveAs("c:\\XLS\\output2.xlsx");

}

float SqlModule::CutFloat(float in)
{
int in2;
in2=(int)(in*1000);
return (float)in2/1000;
}

int SqlModule::UpdateSQL(QString table, QString where, QStringList columns, QStringList values)
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
      sQuery = "UPDATE "+table+" SET ";
      for (int i=0;i<columns.count();i++)
      {
        sQuery += columns[i] +" = '"+values[i]+"' ";
        if (i!=columns.count()-1) { sQuery += ", "; }
      }
      sQuery += " WHERE "+where;
      qDebug() << "SqlModule::UpdateSQL" << sQuery;
      QSqlQuery Qry;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      return Qry.exec(sQuery);
}
}

int SqlModule::InsertSQL(QString table, QStringList columns, QStringList values)
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
      sQuery = "INSERT INTO "+table+" ( ";
      for (int i=0;i<columns.count();i++)
      {
        sQuery += columns[i];
        if (i!=columns.count()-1) { sQuery += ", "; }
      }
      sQuery += ") VALUES (";
      for (int i=0;i<columns.count();i++)
      {
        sQuery += "'"+values[i]+"'";
        if (i!=columns.count()-1) { sQuery += ", "; }
      }
      sQuery += ")";

      qDebug() << "SqlModule::InsertSQL" << sQuery;
      QSqlQuery Qry;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      return Qry.exec(sQuery);
}
}

int SqlModule::DeleteSQL(QString table, QString where)
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
      sQuery = "DELETE FROM "+table+" WHERE "+where;
      qDebug() << "SqlModule::DeleteSQL" << sQuery;
      QSqlQuery Qry;

      Qry.setForwardOnly(true);
      Qry.prepare(sQuery);

      return Qry.exec(sQuery);
}
}


bool SqlModule::ConnectDB(QSqlDatabase &db, QString RegistryThread)
{
IniSettings *INIFile =new IniSettings;
QString ServerName=INIFile->GetParamStr(RegistryThread+"/ServerName");
QString dbName=INIFile->GetParamStr(RegistryThread+"/DBName");


if (QSqlDatabase::contains("QODBC"))
{ db = QSqlDatabase::database("QODBC"); }
else
{ db = QSqlDatabase::addDatabase("QODBC"); }

db.setConnectOptions();
QString dsn=INIFile->GetParamStr(RegistryThread+"/DSN").arg(ServerName).arg(dbName);
db.setDatabaseName(dsn);
delete(INIFile);

return db.isOpen();
}


bool SqlModule::DoSELECT(QVector <QMap <QString,QString>> &ResultVector, QString query, QString dbname)
{
    QSqlDatabase db;
    ConnectDB(db, dbname);
    IniSettings *INIFile =new IniSettings;
    delete(INIFile);
    QMap <QString,QString> ResultMap;
    bool Result=false;

    ResultMap.clear();
    ResultVector.clear();

    qDebug() << "DOSELECT" << query;

    if (db.open())
    {
          QString sQuery;
          sQuery = query;
          QSqlQuery Qry;
          Qry.setForwardOnly(true);
          Qry.prepare(sQuery);

          if (Qry.exec(sQuery))
          {
              qDebug() << "found users " << Qry.size();
              while (Qry.next())
              {
              Result=true;
              QSqlRecord localRecord = Qry.record();
              for (int i=0;i<Qry.record().count();i++)
                {
                bool ok;
                QString str=localRecord.value(i).toString();
                float num = str.toFloat(&ok);
                //if (ok && localRecord.fieldName(i)!="Nest" && localRecord.fieldName(i)!="SiemensID") ResultMap.insert(localRecord.fieldName(i),QString::number(num,'f',3)); else
                ResultMap.insert(localRecord.fieldName(i),localRecord.value(i).toString());
                }
              ResultVector.push_back(ResultMap);
              }
          return(Result);
          } else qDebug() << "SELECT SQL Query is _NOT_ OK ";
          qDebug() << sQuery;
          db.close();
    } else
    {
        qDebug() << "SQL ERROR: " << db.lastError().text();
        //SetErrorEx(0,201,"Нет соединения к SQL локальному серверу : "+db.lastError().text(),"ВыхПульт");
    }
    return(false);
}
