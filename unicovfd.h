#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include <QModbusClient>
#include <QModbusRtuSerialMaster>
#include "interfaces/ivfd.h"
#include "fixedpointnumber.h"
#include "unicovfdconfigdialog.h"
#include "errorlogger.h"


class UnicoVFD : public QObject, public iVFD
{
    Q_OBJECT
public:
    explicit UnicoVFD(QObject *parent = nullptr);
    ~UnicoVFD();

    //Unico 805244 register
    const int JOG_VEL_R = 84; //set speed
    const int MOTOR_RPM_R = 222; //current speed
    const int HARDWARE_FAULTS_R = 249;
    const int SOFTWARE_FAULTS_R = 255;
    const int USER_FAULTS_R = 261;
    const int FWD_MOTION_STS_R = 415; //0->CCW, 1->CW
    const int SERIAL_MODE_R = 427; //0->Hold, 1->CW, 2->CCW

    // iVFD interface
    void setSpeed(double speed) override;
    double speed() override;
    void setDirection(int direction) override;
    int direction() override;
    void initDevice() override;
    void configDevice() override;
    bool connectDevice() override;
    void disconnectDevice() override;
    iVFD::State state() override;

    //TODO: using modbus async api

private slots:
    void errorOccured(QModbusDevice::Error error);

private:
    UnicoVfdConfigDialog *m_configDialog = 0;
    QModbusClient *m_modbusDevice = 0;
    iVFD::State m_state;
    int m_deviceID;


};

#endif // UNICOVFD_H
