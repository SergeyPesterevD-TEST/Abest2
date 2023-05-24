#include "ModBusMaster.h"


ModBusMaster::ModBusMaster(QObject *parent):
    modbusDevice(nullptr)
{
    modbusDevice = new QModbusTcpClient(this);

    QObject::connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        qDebug() << servername << "1 MODBUS ERROR " << modbusDevice->errorString(); ReConnectModbus(); });

   QObject::connect(modbusDevice, &QModbusClient::stateChanged, this, &ModBusMaster::StateChanged);

   DIVector.clear();
   for (int i=0;i<50;i++) DIVector.push_back(0);

}

void ModBusMaster::StateChanged(QModbusClient::State state)
{
    switch (state) {
    case QModbusClient::ConnectedState:
        startReadRequests();
        break;
    case QModbusClient::UnconnectedState:
        stopReadRequests();
        ReConnectModbus();
        break;

    default:
        break;
    }
}

ModBusMaster::~ModBusMaster()
{
    stopReadRequests();
    if(modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;

}

void ModBusMaster::init() {
}

void ModBusMaster::readReady()
{
    auto lastRequest = qobject_cast<QModbusReply *>(sender());
    if (!lastRequest)
        return;

    if (lastRequest->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = lastRequest->result();
        QString entry = "DI ";
        //qDebug() << "DI total" << unit.valueCount();
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            DIVector.data()[i]=unit.value(i);
            entry = entry + QString::number(unit.value(i))+ " ";
        }
            //qDebug() << servername << entry;
    }
    else
        if(modbusDevice->ConnectedState==QModbusDevice::ConnectedState)
        {
            if (lastRequest->error() == QModbusDevice::ProtocolError) {
                qDebug() << servername << "2 MODBUS Read response error: (Modbus exception)" << lastRequest->errorString() << lastRequest->rawResult().exceptionCode();
            } else {
                qDebug() << servername << "3 MODBUS Read response error: (code: )" << lastRequest->errorString() << lastRequest->error();
                //reconnectModbus();
            }
        }

    lastRequest->deleteLater();
}


void ModBusMaster::WriteCoils(int channel, bool channelstate)
{
qDebug() << servername << "4 MODBUS DO Coils " << channel << channelstate;
// WriteRegisters(int channel, int channelstate, int servernum, int startadress, int writesize)
if (channelstate) { ModbusWrite(QModbusDataUnit::Coils, channel,0x01,1,0x00,1); } else
            ModbusWrite(QModbusDataUnit::Coils, channel,0x00,1,0x00,1);
}

void ModBusMaster::WriteMultipleCoils(int channel, int state, int writesize)
{
ModbusWrite(QModbusDataUnit::Coils, channel,state,1,0x00,writesize);
}


void ModBusMaster::WriteHoldingRegisters(int channel, int channelstate)
{
qDebug() << servername << "5 MODBUS DO HoldingRegisters " << channel << channelstate;
ModbusWrite(QModbusDataUnit::HoldingRegisters, channel, quint16(channelstate), 1, 0x00, 1);
}


void ModBusMaster::ModbusReadDiscreteInputs(int serveraddress)
{
    if (!modbusDevice)
        return;    

    qDebug() << servername << "6 MODBUS RC " << QVariant::fromValue(modbusDevice->ConnectedState).value<QString>();

    if (auto *lastRequest = modbusDevice->sendReadRequest(readRequest(0x00, 8, QModbusDataUnit::DiscreteInputs), serveraddress)) {
        if (!lastRequest->isFinished())
            connect(lastRequest, &QModbusReply::finished, this, &ModBusMaster::readReady);
        else
            delete lastRequest; // broadcast replies return immediately
    } else {
        qDebug() << servername << "7 Read error: " << modbusDevice->errorString();
    }
}


void ModBusMaster::ModbusReadInputRegisters(int serveraddress)
{
    if (!modbusDevice)
        return;

    qDebug() << servername << "8 MODBUS RC " << QVariant::fromValue(modbusDevice->ConnectedState).value<QString>();

    if (auto *lastRequest = modbusDevice->sendReadRequest(readRequest(0x00, 5, QModbusDataUnit::InputRegisters), serveraddress)) {
        if (!lastRequest->isFinished())
            connect(lastRequest, &QModbusReply::finished, this, &ModBusMaster::readReady);
        else
            delete lastRequest; // broadcast replies return immediately
    } else {
        qDebug() << servername << "9 Read error: " << modbusDevice->errorString();
    }
}


void ModBusMaster::ModbusWrite(QModbusDataUnit::RegisterType type, int channel, int channelstate, int servernum, int startadress, int writesize)
{
    if (!modbusDevice)
        return;


    if(modbusDevice->ConnectedState!=QModbusDevice::ConnectedState)
    {
        qCritical() << "MODBUS DO Error. Device is not connected.";
    }

    QModbusDataUnit writeUnit;

    if (type==QModbusDataUnit::Coils)
    {
        QVector<quint16> registers;
        for (int j=0;j<writesize;j++)
        {
            registers.push_back(int((1 << j)  &  channelstate));
        }

        writeUnit = QModbusDataUnit(QModbusDataUnit::Coils, startadress+channel, registers);
    //writeUnit = QModbusDataUnit(QModbusDataUnit::Coils, startadress+channel, QVector<quint16>(1, channelstate));
    } else
        if (type==QModbusDataUnit::HoldingRegisters)
        {
        //writeUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, startadress+channel, channelstate);
            writeUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, startadress+channel, QVector<quint16>(1, channelstate));
        }

    if (auto *lastRequest = modbusDevice->sendWriteRequest(writeUnit, servernum)) {
        if (!lastRequest->isFinished())
        {
            connect(lastRequest, &QModbusReply::finished, this, [this, lastRequest]()
            {
                if(modbusDevice->ConnectedState==QModbusDevice::ConnectedState)
                {
                    if (lastRequest->error() == QModbusDevice::ProtocolError)
                    {
                        qCritical() << servername << "10 MODBUS ошибка протокола";
                        qDebug() << servername << "10 Write response error: (Mobus exception: )" <<
                                    lastRequest->errorString() << lastRequest->rawResult().exceptionCode();
                    }
                    else
                        if (lastRequest->error() != QModbusDevice::NoError)
                        {
                            qDebug() << servername << "11 Write response error: (code: )" <<
                                        lastRequest->errorString() << lastRequest->error();
                            qCritical() << "MODBUS ошибка при записи: " << lastRequest->error();;
                            //reconnectModbus();
                        }
                }
                lastRequest->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            lastRequest->deleteLater();
        }
    } else {
        ReConnectModbus();
        qCritical() << servername << "12 MODBUS ошибка записи " << modbusDevice->errorString();
        qDebug() << servername << "12 Write error: " << modbusDevice->errorString();
    }
}

QModbusDataUnit ModBusMaster::readRequest(int StartAdress, int Amount, QModbusDataUnit::RegisterType Type) const
{
  return QModbusDataUnit(Type, StartAdress, Amount);
}

QModbusDataUnit ModBusMaster::writeRequest(int StartAdress, int WriteSize) const
{
    return QModbusDataUnit(QModbusDataUnit::Coils, StartAdress, WriteSize);
}


void ModBusMaster::ReConnectModbus()
{
    if (!modbusDevice)
        return;
    qDebug() << servername << "13 MODBUS ReConnecting ";
    if (modbusDevice->ConnectedState==QModbusDevice::ConnectedState) { modbusDevice->disconnectDevice(); }

    if (modbusDevice->connectDevice())

        qDebug() << servername << "14 MODBUS" << QVariant::fromValue(modbusDevice->ConnectedState).value<QString>();
    else
        qDebug() << servername << "15 MODBUS ERROR Not Connected: " << modbusDevice->errorString();
}


void ModBusMaster::ConnectModbus(QString MBServer)
{
    servername=MBServer;
    if (!modbusDevice)
    {
        emit StateChanged(QModbusClient::UnconnectedState);
        return;
    }
    qDebug() << servername << "16 MODBUS Connecting " << MBServer;
    //if (modbusDevice->ConnectedState==QModbusDevice::ConnectedState) { modbusDevice->disconnectDevice(); }

    const QUrl url = QUrl::fromUserInput(MBServer);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());

    modbusDevice->setTimeout(RESPONSE_TIME);
    modbusDevice->setNumberOfRetries(NUMBER_OF_RETRIES);

    if (modbusDevice->connectDevice())
        qDebug() << servername << "17 MODBUS" << QVariant::fromValue(modbusDevice->ConnectedState).value<QString>();
    else
        qDebug() << servername << "18 MODBUS ERROR Not Connected: " << modbusDevice->errorString();
}

void ModBusMaster::startReadRequests()
{
    qDebug() << servername << "19 startReadRequests()";
}

void ModBusMaster::stopReadRequests()
{
    qDebug() << servername << "20 stopReadRequests()";
}
