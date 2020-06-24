#include "RF603.h"

using namespace std;

#define GETRESULT_ERROR_VALUE ((USHORT)0xffff)
#define MIN(a,b) (a<b ? a : b)
#define MEASURES_TO_DO 5
#define VALUES_TO_PRINT 4

RF603::RF603()
{
    ///
}


bool RF603::RF603_CheckSensors(IniSettings *INIFile, QVector<int> *Measures)
{
///qDebug() << "Checking sensors";

RFDevice::Initialize();
RFDevice::RF603Device *dev = new RFDevice::RF603Device();
RFDevice::RFCOMHELLOANSWER hello;
BOOL bConn = FALSE;

//qDebug() << "Opening " << INIFile->GetParamStr("Main/ComPortNumber") << INIFile->GetParamStr("Main/SensorSpeed") << "...";

QByteArray temp_data;
QString temp_str;
temp_str=INIFile->GetParamStr("Main/ComPortNumber");
temp_data = temp_str.toLocal8Bit();
bool CheckResult;
int average;
CheckResult=TRUE;

LPCSTR s = temp_data.constData();  // casting shouldn't be needed

if (INIFile->GetParamStr("Main/SensorSpeed")=="9600") {bConn = dev->OpenPort(s,RFDevice::Baud9600);}
if (INIFile->GetParamStr("Main/SensorSpeed")=="19200") {bConn = dev->OpenPort(s,RFDevice::Baud19200);}
if (INIFile->GetParamStr("Main/SensorSpeed")=="115200") {bConn = dev->OpenPort(s,RFDevice::Baud115200);}

if (!bConn)
    {
        qDebug() << "Failed\n";
        CheckResult=FALSE;
    }
    else
    {
    Measures->clear();
    dev->LockResult(0);
        for (int i=1; i<=INIFile->GetParam("Main/NumberOfSensors"); i++)
            {
            //qDebug() << "Check " << i;
            dev->BindNetworkAddress(i);
            /*qDebug() << "HelloCmd()";
            if (!dev->HelloCmd())
                {
                qDebug() << "Failed\n";
                CheckResult=FALSE;
                }
            else*/
                {
    //          qDebug() << "Detected\n";

                USHORT x;
                dev->GetSingleMeasure(&x);
                x=1000*x*10/0x4000;
    //            qDebug() << "Measure " << i << " = " << x;
                Measures->push_back(x);
                }
       }
   }
//qDebug() << "Ends CheckSensors...";

dev->ClosePort();
RFDevice::Cleanup();
return(CheckResult);
}

int RF603::RF603_GETviaCOM(IniSettings *INIFile, QVector<int> *Measures)
{
    qDebug() << "Starting RF603_GETviaCOM";

    RFDevice::Initialize();
    RFDevice::RF603Device *dev = new RFDevice::RF603Device();
    RFDevice::RFCOMHELLOANSWER hello;
    BOOL bConn = FALSE;

    qDebug() << "Opening " << INIFile->GetParamStr("Main/ComPortNumber") << INIFile->GetParamStr("Main/SensorSpeed") << "...";

    QByteArray temp_data;
    QString temp_str;
    temp_str=INIFile->GetParam("Main/ComPortNumber");
    temp_data = temp_str.toLocal8Bit();

    LPCSTR s = temp_data.constData();  // casting shouldn't be needed

    if (INIFile->GetParamStr("Main/SensorSpeed")=="9600") {bConn = dev->OpenPort(s,RFDevice::Baud9600);}
    if (INIFile->GetParamStr("Main/SensorSpeed")=="19200") {bConn = dev->OpenPort(s,RFDevice::Baud19200);}
    if (INIFile->GetParamStr("Main/SensorSpeed")=="115200") {bConn = dev->OpenPort(s,RFDevice::Baud115200);}

    if (!bConn)
        {
            qDebug() << "Failed\n";        
        }
        else
        {
        dev->LockResult(0);
        for (int i=1; i<=INIFile->GetParam("Main/NumberOfSensors"); i++)
        {
            qDebug() << "Check " << i;
            dev->BindNetworkAddress(i);

            qDebug() << "HelloCmd()";
            if (!dev->HelloCmd())
            {
                qDebug() << "Failed\n";
            }
            else
            {
                qDebug() << "Detected\n";
                dev->GetHelloAnswer(&hello);
                qDebug() << "S/N " << hello.wDeviceSerial;

                USHORT x;
                dev->GetSingleMeasure(&x);
                x=1000*x*10/0x4000;
                qDebug() << "Measure " << i << " = " << x;
                Measures->push_back(x);

//                if (dev->EnableEth (TRUE)==FALSE) { qDebug() << "Ethernet Stream Failed\n"; }
            }
       }
       }
    qDebug() << "Ends RF603_GETviaCOM...";

    dev->ClosePort();

    RFDevice::Cleanup();

    }
