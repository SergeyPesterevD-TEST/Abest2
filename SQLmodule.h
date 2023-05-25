#ifndef SQLMODULE_H
#define SQLMODULE_H
#include <QDebug>
#include <QtSql>
#include <QTime>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "SQLmodule.h"

class SqlModule:public QObject
{
Q_OBJECT
private:
public:
    SqlModule();
    ~SqlModule()
    {
        qDebug()<<"delete object SqlModule";
    }

    struct Top100
    {
    QDateTime    cdatetime;
    QString      rulon;
    QVector<int> data;
    float LIR;
    float SPEED;
    };

    struct CartonTypes
    {
    QString name;
    int key, target, max, min, offset;
    };

    struct UsersTypes
    {
    int key, shiftnumber, isadmin, isactive;
    QString username, password, fingerprint;
    };

    struct CurrentRulon
    {
    QString rulontype, currentdate, username, rulonnumber;
    float nominal, min, max, offset;
    };

    int SqlConnect();
    int SqlGetLast(int GetCount, int GetHours, QVector<Top100> *Top100Measures);
    int SqlGetAverageRow(int Minutes,  QVector<float> *AverageRowMeasures);
    int SqlPutMeasure(QString rulon, QVector<int> *Measures);
    int SqlPutMeasure2(QString rulon, QVector<int> *CurrentData, float LIR, float SPEED);

    // 2023
    int SqlGetTypes(QVector <CartonTypes> &TypesList);
    int SqlGetUsers(QVector <UsersTypes> &UsersList);
    int SqlAddNewRulon(CurrentRulon &rulon);

private slots:
signals:
};

#endif // SQLMODULE_H
