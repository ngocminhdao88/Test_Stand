#include "unicovfd.h"
#include <QEventLoop>

UnicoVFD::UnicoVFD(QObject *parent) : QObject(parent)
{
}


void UnicoVFD::setSpeed(double speed)
{
    if(!modbusClient()) return;

    if(modbusClient()->state() !=QModbusDevice::ConnectedState) return;

    if(speed < 0) return;

    int fixSpeed = calFixNumber(speed);

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                JOG_VEL_R,
                                QVector<quint16>() << fixSpeed);
    if(auto *reply = modbusClient()->sendWriteRequest(data, 1)) {
        if(reply->isFinished()) {
            //TODO: do something with reply;
            //connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //reply return immediately
            reply->deleteLater();
        }
    } else {
        //TODO: error when sending write request. Do something about it
        //modbusClient()->error();
        //modbusClient()->errorString();
    }
}

double UnicoVFD::speed()
{
    double speed = 0;

    if(!modbusClient()) return speed;

    if(modbusClient()->state() != QModbusDevice::ConnectedState) return speed;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                MOTOR_RPM_R,
                                1);
    if(auto *reply = modbusClient()->sendReadRequest(data, 1)) {
        while(!reply->isFinished());

        auto result = reply->result();
        if(result.isValid()) {
            speed = result.value(0);
            speed = speed / 10;
        }

        reply->deleteLater();
    } else {
        //error occured
        emit modbusClient()->errorOccurred(modbusClient()->error());
    }

    return speed;
}

void UnicoVFD::setDirection(int direction)
{
    if(!modbusClient()) return;

    if(modbusClient()->state() != QModbusDevice::ConnectedState) return;

    //Direction should be positive and smaller or equals 2
    if(direction < 0 || direction > 2) return;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                SERIAL_MODE_R,
                                QVector<quint16>() << direction
                                );

    if(auto *reply = modbusClient()->sendWriteRequest(data, 1)) {
        if(reply->isFinished()) {
            //TODO: do something with reply;
            //connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //reply return immediately
            reply->deleteLater();
        }
    } else {
        //TODO: error when sending write request. Do something about it
    }
}

int UnicoVFD::direction()
{
    int direction = 0;

    if(!modbusClient()) return direction;

    if(modbusClient()->state() != QModbusDevice::ConnectedState) return direction;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                FWD_MOTION_STS_R,
                                1);

    if(auto *reply = modbusClient()->sendReadRequest(data, 1)) {
        if(reply->isFinished()) {
            //TODO: do something with reply;
            //connect(reply, &QModbusReply::finished, this, &UnicoVFD::onReadReady);
        } else {
            //reply return immediately
            reply->deleteLater();
        }
    } else {
        //TODO: error when sending write request. Do something about it
    }

    return direction;
}

void UnicoVFD::initDevice()
{
}

void UnicoVFD::configDevice()
{
}

int UnicoVFD::calFixNumber(double value)
{
    return (int)(value * 10);
}

QModbusClient *UnicoVFD::modbusClient() const
{
    return m_modbusClient;
}

void UnicoVFD::setModbusClient(QModbusClient *modbusClient)
{
    m_modbusClient = modbusClient;
}
