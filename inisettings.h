#ifndef INISETTINGS_H
#define INISETTINGS_H
#include <QVector>
#include <QSettings>


class IniSettings
{
public:
    IniSettings();
    int GetCalib(int Pair, QString param);
    int GetParam(QString param);
    QString GetParamStr(QString param);
    QString GetSensor(int Sensor, QString param);
    void SetParamStr(QString param, QString value);
    void SetParam(QString param, int value);
private:

};

#endif // INISETTINGS_H
