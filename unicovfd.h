#ifndef UNICOVFD_H
#define UNICOVFD_H

#include <QObject>
#include "interfaces/ivfd.h"


class UnicoVFD : public QObject, public iVFD
{
    Q_OBJECT
public:
    explicit UnicoVFD(QObject *parent = nullptr);

    //Unico 805244 register
    const int JOG_VEL_R = 84; //set speed
    const int MOTOR_RPM_R = 222; //current speed
    const int HARDWARE_FAULTS_R = 249;
    const int SOFTWARE_FAULTS_R = 255;
    const int USER_FAULTS_R = 261;
    const int FWD_MOTION_STS_R = 415; //0->CCW, 1->CW
    const int SERIAL_MODE_R = 427; //0->Hold, 1->CW, 2->CCW

signals:

    // iVFD interface
private:
    void setSpeed(double speed) override;
    double speed() override;
    void setDirection(int direction) override;
    int direction() override;
    void initDevice() override;
    void configDevice() override;

    //Calculate a fixed point number for Unico VFD
    //do i need a seperate class for this conversion?
    int calFixNumber(double value);
};

#endif // UNICOVFD_H
