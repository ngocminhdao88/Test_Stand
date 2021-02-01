#include "unicovfd.h"

UnicoVFD::UnicoVFD(QObject *parent) : QObject(parent)
{
}


void UnicoVFD::setSpeed(double speed)
{
    //TODO: write speed to JOG_VEL_R register
}

double UnicoVFD::speed()
{
    double speed = 0;
    //TODO: read speed from MOTOR_RPM_R register
    return speed;
}

void UnicoVFD::setDirection(int direction)
{
    //TODO: write direction to SERIAL_MODE_R register
}

int UnicoVFD::direction()
{
    int direction = 0;
    //TODO: read direction from FWD_MOTION_R register
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
