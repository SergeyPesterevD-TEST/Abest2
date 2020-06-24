#include "rfthread.h"

using namespace std;

#define GETRESULT_ERROR_VALUE ((USHORT)0xffff)
#define MIN(a,b) (a<b ? a : b)
#define MEASURES_TO_DO 5
#define VALUES_TO_PRINT 4+

RFThread::RFThread()
{

}

bool RFThread::running() const
{
    return m_running;
}


void RFThread::run()
{
qDebug() << "THREAD Starting RF603_GETviaCOM";

IniSettings *INIFile = new IniSettings;
QVector<int> OutputMeasures;

RFDevice::Initialize();
RFDevice::RF603Device *dev = new RFDevice::RF603Device();
RFDevice::RFCOMHELLOANSWER hello;
BOOL bConn = FALSE;

qDebug() << "THREAD Opening " << INIFile->GetParamStr("Main/ComPortNumber") << INIFile->GetParamStr("Main/SensorSpeed") << "...";

QByteArray temp_data;
QString temp_str;
temp_str=INIFile->GetParam("Main/ComPortNumber");
temp_data = temp_str.toLocal8Bit();

LPCSTR s = temp_data.constData();  // casting shouldn't be needed

if (INIFile->GetParamStr("Main/SensorSpeed")=="9600") {bConn = dev->OpenPort(s,RFDevice::Baud9600);}
if (INIFile->GetParamStr("Main/SensorSpeed")=="19200") {bConn = dev->OpenPort(s,RFDevice::Baud19200);}
if (INIFile->GetParamStr("Main/SensorSpeed")=="115200") {bConn = dev->OpenPort(s,RFDevice::Baud115200);}

//if (!bConn)
if (2==1)
    {
        qDebug() << "THREAD Failed";

        if (INIFile->GetParam("NoPort")==1)
        {
        qDebug() << "THREAD NoPort - Emulation starts\n";
        // when working without sensors. just to check algorhytms.
        QRandomGenerator *generator=new QRandomGenerator;

        while (m_running)
        {
        OutputMeasures.clear();
        for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
        {
            OutputMeasures.push_back(generator->generateDouble()*5000);
            OutputMeasures.push_back(generator->generateDouble()*5000);
        }
        emit EmitMeasures(OutputMeasures);
        Sleep(2000);
        //qDebug() << "Emulation done";
        }
        delete(generator);
        }

    }
    else
    {
    while (m_running)
    {
    OutputMeasures.clear();
    dev->LockResult(0);
    for (int i=1; i<=INIFile->GetParam("Main/NumberOfSensors"); i++)
    {
        qDebug() << "THREAD Check " << i;
        dev->BindNetworkAddress(i);

        qDebug() << "THREAD HelloCmd()";
        if (!dev->HelloCmd())
        {
            qDebug() << "THREAD Failed\n";
        }
        else
        {
            qDebug() << "THREAD Detected\n";
            dev->GetHelloAnswer(&hello);
            qDebug() << "THREAD S/N " << hello.wDeviceSerial;

            USHORT x;
            dev->GetSingleMeasure(&x);
            x=1000*x*10/0x4000;
            qDebug() << "THREAD Measure " << i << " = " << x;
            OutputMeasures.push_back(x);
            Sleep(1000);
        }
      }
   emit EmitMeasures(OutputMeasures);
   }
   }
qDebug() << "THREAD Ends RF603_GETviaCOM...";

dev->ClosePort();

RFDevice::Cleanup();
}

void RFThread::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}
