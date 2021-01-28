#ifndef ABSTRACTVFD_H
#define ABSTRACTVFD_H

class AbstractVFD
{
    /**
     * @brief Set the VFD speed
     * @param speed
     */
    virtual void setSpeed(double speed);

    /**
     * @brief Get the VFD speed
     */
    virtual double speed();

    /**
     * @brief Set VFD turn direction
     * @param direction
     */
    virtual void setDirection(int direction);

    /**
     * @brief Get the VFD turn direction
     * @return
     */
    virtual int direction();

    /**
     * @brief Connect to the VFD
     * @return True if connection to VFD was successful
     */
    virtual bool connectDevice();

    /**
     * @brief Configure the VFD
     */
    virtual void configDevice();

    /**
     * @brief Initiate the VFD
     */
    virtual void initiateDevice();
};

#endif // ABSTRACTVFD_H
