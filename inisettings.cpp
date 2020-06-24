#include "inisettings.h"
#include <QSettings>
#include <QTextStream>
#include <QVector>
#include <QDebug>

IniSettings::IniSettings()
{
}

QString IniSettings::GetParamStr(QString param)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    QString temp;
    temp=Settings->value(param,0).toString();
    delete (Settings);
    return(temp);
}

void IniSettings::SetParamStr(QString param, QString value)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    Settings->setValue(param,value);
    Settings->sync();
    delete (Settings);
}

void IniSettings::SetParam(QString param, int value)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    Settings->setValue(param,value);
    Settings->sync();
    delete (Settings);
}


int IniSettings::GetParam(QString param)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    int temp;
    temp=Settings->value(param,0).toInt();
    delete (Settings);
    return(temp);
}

int IniSettings::GetCalib(int Pair, QString param)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    int temp;
    temp=Settings->value("Calibration/"+QString::number(Pair)+"/"+param,0).toInt();

    delete (Settings);
    return(temp);
}

QString IniSettings::GetSensor(int Sensor, QString param)
{
    QSettings* Settings = new QSettings("D-TEST","Thickness");
    QString temp;
    temp=Settings->value("Sensors/"+QString::number(Sensor)+"/"+param,0).toString();

    delete (Settings);
    return(temp);
}



