#ifndef IDEVICE_H
#define IDEVICE_H

#pragma once
#include <iostream>
#include <string>
class IDevice
{
public:
    enum class PowerState 
    {
        ON,
        OFF
    };

    IDevice(const std::string& deviceName = "Unnamed Device",PowerState powerState = PowerState::OFF);
    virtual ~IDevice();

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void status() = 0;
    IDevice::PowerState getPowerState();
    void setPowerState(IDevice::PowerState value);
    std::string getDeviceName();
    void setDeviceName(std::string value); 

protected:
    IDevice::PowerState m_powerState;
    std::string m_deviceName;


};





#endif