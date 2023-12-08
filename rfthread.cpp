#include "rfthread.h"

using namespace std;

#define GETRESULT_ERROR_VALUE ((USHORT)0xffff)
#define MIN(a,b) (a<b ? a : b)
#define MEASURES_TO_DO 5
#define VALUES_TO_PRINT 4+

RFThread::RFThread(QObject *parent)
    : QObject{parent},
    m_message("")
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

QString ComPortNumber=INIFile->GetParamStr("Main/ComPortNumber");
QString ComPortSpeed=INIFile->GetParamStr("Main/SensorSpeed");
qDebug() << "THREAD Opening " << ComPortNumber << ComPortSpeed << "...";

QByteArray temp_data;
QString temp_str;
temp_str=ComPortNumber;
temp_data = temp_str.toLocal8Bit();

LPCSTR s = temp_data.constData();  // casting shouldn't be needed

if (ComPortSpeed=="9600") {bConn = dev->OpenPort(s,RFDevice::Baud9600);}
if (ComPortSpeed=="19200") {bConn = dev->OpenPort(s,RFDevice::Baud19200);}
if (ComPortSpeed=="115200") {bConn = dev->OpenPort(s,RFDevice::Baud115200);}

qDebug() << "Bcon=   " << bConn << ComPortNumber << ComPortSpeed;

if (!bConn)
    {
        qDebug() << "THREAD Port Opening Failed";
//        if (INIFile->GetParam("NoPort")==1)
//        {
//        qDebug() << "THREAD NoPort - Emulation starts\n";
//        // when working without sensors. just to check algorhytms.
//        QRandomGenerator *generator=new QRandomGenerator;
//            while (m_running)
//            {
//            OutputMeasures.clear();
//            for (int i=0;i<INIFile->GetParam("Main/NumberOfPairs");i++)
//                {
//                OutputMeasures.push_back(generator->generateDouble()*5000);
//                OutputMeasures.push_back(generator->generateDouble()*5000);
//                }
//            //emit sendMessage(OutputMeasures);
//            Sleep(2000);
//            }
//        delete(generator);
//        }
    }
    else
    {
    while (m_running)
        {
        OutputMeasures.clear();
        OutputMeasures.push_back(0); // put 0 pos
        OutputMeasures.push_back(0); // put 1 pos
        int NeedToRestart=0;
        dev->LockResult(0);
        for (int i=2; i<INIFile->GetParam("Main/NumberOfSensors")+2; i++)
            {
            //qDebug() << "THREAD Check " << i;
            dev->BindNetworkAddress(i);

            //qDebug() << "THREAD HelloCmd()";
            if (!dev->HelloCmd())
                {
                qDebug() << "THREAD Failed" << i;
                NeedToRestart++;
                OutputMeasures.push_back(0);
                }
                else
                    {
                    //qDebug() << "THREAD Detected\n";
                    dev->GetHelloAnswer(&hello);
                    //qDebug() << "THREAD S/N " << hello.wDeviceSerial;

                    USHORT x;
                    dev->GetSingleMeasure(&x);
                    x=1000*x*10/0x4000;
                    //Debug() << "THREAD Measure " << i << " = " << x;
                    OutputMeasures.push_back(x);

                    }
            }
        if (NeedToRestart>=10)
            {
            emit watchDog();
            }

        qDebug() << "THREAD Measure Count" << OutputMeasures;
        emit sendMessage(OutputMeasures);
        //Sleep(300);
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
