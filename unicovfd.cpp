#include "unicovfd.h"
#include <QVariant>

UnicoVFD::UnicoVFD(QObject *parent) : QObject(parent)
{
    m_configDialog = new UnicoVfdConfigDialog();
    m_state = iVFD::UnconnectedState;
}

UnicoVFD::~UnicoVFD()
{
    if(m_modbusDevice) m_modbusDevice->disconnectDevice();
    delete m_modbusDevice;

    delete m_configDialog;
}


void UnicoVFD::setSpeed(double speed)
{
    if(!m_modbusDevice) return;
    if(m_modbusDevice->state() !=QModbusDevice::ConnectedState) return;
    if(speed < 0) return;

    FixedPointNumber fp(10);
    int fixSpeed = fp.toFixedPointNumber(speed);

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                JOG_VEL_R,
                                QVector<quint16>() << fixSpeed);
    if(auto *reply = m_modbusDevice->sendWriteRequest(data, m_deviceID)) {
        reply->deleteLater();
    } else {
        //error occured
        emit m_modbusDevice->errorOccurred(m_modbusDevice->error());
    }
}

double UnicoVFD::speed()
{
    double speed = 0;

    if(!m_modbusDevice) return speed;
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState) return speed;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                MOTOR_RPM_R,
                                1);
    if(auto *reply = m_modbusDevice->sendReadRequest(data, m_deviceID)) {
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
        emit m_modbusDevice->errorOccurred(m_modbusDevice->error());
    }

    return speed;
}

void UnicoVFD::setDirection(int direction)
{
    if(!m_modbusDevice) return;
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState) return;

    //Direction should be positive and smaller or equals 2
    if(direction < 0 || direction > 2) return;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                SERIAL_MODE_R,
                                QVector<quint16>() << direction);

    if(auto *reply = m_modbusDevice->sendWriteRequest(data, m_deviceID)) {
        reply->deleteLater();
    } else {
        //TODO: error when sending write request. Do something about it
        emit m_modbusDevice->errorOccurred(m_modbusDevice->error());
    }
}

int UnicoVFD::direction()
{
    int direction = 0;

    if(!m_modbusDevice) return direction;
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState) return direction;

    auto data = QModbusDataUnit(QModbusDataUnit::HoldingRegisters,
                                FWD_MOTION_STS_R,
                                1);

    if(auto *reply = m_modbusDevice->sendReadRequest(data, m_deviceID)) {
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
        emit m_modbusDevice->errorOccurred(m_modbusDevice->error());
    }

    return direction;
}

void UnicoVFD::initDevice()
{
    if(m_modbusDevice) m_modbusDevice->disconnectDevice();
    delete m_modbusDevice;

    m_modbusDevice = new QModbusRtuSerialMaster(this);

    connect(m_modbusDevice, &QModbusDevice::errorOccurred, this, &UnicoVFD::errorOccured);
}

void UnicoVFD::configDevice()
{
    if(!m_configDialog) return;

    m_configDialog->show();
}


bool UnicoVFD::connectDevice()
{
    if(!m_modbusDevice) return false;
    if(!m_configDialog) return false;

    if(m_modbusDevice->state() != QModbusDevice::ConnectedState) {
        //setup connection params
        m_modbusDevice->setConnectionParameter(
                    QModbusDevice::SerialPortNameParameter,
                    m_configDialog->parameters().portName);
        m_modbusDevice->setConnectionParameter(
                    QModbusDevice::SerialParityParameter,
                    m_configDialog->parameters().parity);
        m_modbusDevice->setConnectionParameter(
                    QModbusDevice::SerialBaudRateParameter,
                    m_configDialog->parameters().baud);
        m_modbusDevice->setConnectionParameter(
                    QModbusDevice::SerialDataBitsParameter,
                    m_configDialog->parameters().databits);
        m_modbusDevice->setConnectionParameter(
                    QModbusDevice::SerialStopBitsParameter,
                    m_configDialog->parameters().stopbits);
        m_modbusDevice->setTimeout(m_configDialog->parameters().timeout);
        m_modbusDevice->setNumberOfRetries(m_configDialog->parameters().retry);

        m_deviceID = m_configDialog->parameters().deviceid;

        //try to connect to the modbus device
        if(m_modbusDevice->connectDevice()) {
            //connect successful
        } else {
            //error when connection

            return false;
        }
    }

    m_state = iVFD::ConnectedState;
    return true;
}

iVFD::State UnicoVFD::state()
{
    return m_state;
}

void UnicoVFD::errorOccured(QModbusDevice::Error error)
{
    if(!m_modbusDevice) return;

    m_state = iVFD::FaultState; //do i really to set the VFD state to fault??

    ErrorLogger logger;
    logger.write(QString("UnicoVfd, %1, %2").arg(QString::number(m_modbusDevice->error()), m_modbusDevice->errorString()));
}


void UnicoVFD::disconnectDevice()
{
    if(!m_modbusDevice) return;

    if(m_modbusDevice->state() == QModbusDevice::ConnectedState) {
        m_modbusDevice->disconnectDevice();
    }

    m_state = iVFD::UnconnectedState;
}
