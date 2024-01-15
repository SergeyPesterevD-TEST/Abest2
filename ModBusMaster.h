#ifndef ModBusMaster_H
#define ModBusMaster_H

#include <QObject>
#include <QMainWindow>
#include <QModbusDataUnit>
#include <QModbusRtuSerialMaster>
#include <QModbusDevice>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusClient>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QUrl>
#include <QThread>

QT_BEGIN_NAMESPACE

class QModbusClient;
class QModbusReply;

QT_END_NAMESPACE

class ModBusMaster : public QObject
{

public:
    enum State {
        UnconnectedState,
        ConnectingState,
        ConnectedState,
        ClosingState
    };
    Q_ENUM(State)

    explicit ModBusMaster(QObject *parent = nullptr);
    ~ModBusMaster();
    QVector<int> DIVector;

signals:
    void StateChanged(QModbusClient::State);
    void stateChanged(QModbusClient::State);

public slots:

    QModbusDataUnit readRequest(int StartAdress, int Amount, QModbusDataUnit::RegisterType Type) const;
    QModbusDataUnit writeRequest(int StartAdress, int WriteSize) const;
    void WriteCoils(int channel, bool channelstate);
    void WriteMultipleCoils(int channel, int state, int writesize);
    void WriteHoldingRegisters(int channel, int channelstate);
    void ModbusReadDiscreteInputs(int serveraddress);
    void ModbusReadInputRegisters(int serveraddress);
    void ModbusWrite(QModbusDataUnit::RegisterType type, int channel, int channelstate, int servernum, int startadress, int writesize);
    QVector<int>i7055;
    QVector<double>i7017;
    void ConnectModbus(QString MBServer);
    void ReConnectModbus();


private slots:
    void readReady();
    void startReadRequests();
    void stopReadRequests();
    void errorHandler(QModbusDevice::Error errorCode);
    void statusHandler(QModbusDevice::State status);



private:
    bool checkConnection();
    void init();
    QModbusClient *modbusDevice = nullptr;
    static const int m_NumberOfDI = 8;
    const int RESPONSE_TIME = 300;
    const int NUMBER_OF_RETRIES = 5;
    QString servername;
    QTimer *m_reconnectTimer;

protected:



};

#endif // ModBusMaster_H

