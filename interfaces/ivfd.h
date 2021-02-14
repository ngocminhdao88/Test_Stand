#ifndef IVFD_H
#define IVFD_H

class iVFD
{
public:
    enum State : unsigned char
    {
        UnconnectedState,
        ConnectedState,
        FaultState
    };

    virtual ~iVFD(){};
    virtual void setSpeed(double speed) = 0;
    virtual double speed() = 0;

    /*!
     * \brief Set the VFD turn direction
     * \param direction: 0->Hold, 1->CW, 2->CCW
     */
    virtual void setDirection(int direction) = 0;
    virtual int direction() = 0;
    virtual void initDevice() = 0;
    virtual void configDevice() = 0;
    virtual bool connectDevice() = 0; //return bool?
    virtual void disconnectDevice() = 0;
    virtual iVFD::State state() = 0;
};

#endif // IVFD_H
