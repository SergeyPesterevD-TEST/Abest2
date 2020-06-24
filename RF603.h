#ifndef RF603_H
#define RF603_H
#include <QtDebug>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QThread>
#include "RFHeaders/RF603Device.h"
#include "RFHeaders/RFEthernetDetector.h"
#include "inisettings.h"

class RF603:public QObject
{
Q_OBJECT
private:
public:
    RF603();
    ~RF603()
    {
        qDebug()<<"delete object SqlModule";
    }
      int RF603_GETviaCOM(IniSettings *INIFile, QVector<int> *Measures);
      bool RF603_CheckSensors(IniSettings *INIFile, QVector<int> *Measures);

private slots:
signals:
};

#endif // RF603_H
