#include "unicovfd.h"

UnicoVFD::UnicoVFD(QObject *parent) : QObject(parent)
{
}

UnicoVFD::~UnicoVFD()
{
}


void UnicoVFD::setSpeed(double speed)
{
    if(!modbusClient()) return;

    if(modbusClient()->state() !=QModbusDevice::ConnectedState) return;

    if(speed < 0) return;

    FixedPointNumber fp(10);
    int fixSpeed = fp.toFixedPointNumber(speed);

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                JOG_VEL_R,
                                QVector<quint16>() << fixSpeed);
    if(auto *reply = modbusClient()->sendWriteRequest(data, 1)) {
        reply->deleteLater();
    } else {
        //error occured
        emit modbusClient()->errorOccurred(modbusClient()->error());
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
            FixedPointNumber fp(10);
            speed = fp.fromFixedPointNumber(speed);
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
                                QVector<quint16>() << direction);

    if(auto *reply = modbusClient()->sendWriteRequest(data, 1)) {
        reply->deleteLater();
    } else {
        //TODO: error when sending write request. Do something about it
        emit modbusClient()->errorOccurred(modbusClient()->error());
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
        while(!reply->isFinished());

        auto result = reply->result();
        if(result.isValid()) {
            auto temp = result.value(0);
            FixedPointNumber fp(10);
            direction = (int)(fp.fromFixedPointNumber(temp));
        }

        reply->deleteLater();
    } else {
        //error occured
        emit modbusClient()->errorOccurred(modbusClient()->error());
    }

    return direction;
}

void UnicoVFD::initDevice()
{
}

void UnicoVFD::configDevice()
{
}

QModbusClient *UnicoVFD::modbusClient() const
{
    return m_modbusClient;
}

void UnicoVFD::setModbusClient(QModbusClient *modbusClient)
{
    m_modbusClient = modbusClient;
}
