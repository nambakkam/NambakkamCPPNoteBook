#ifndef FAN_H
#define FAN_H

#pragma once
#include "IDevice.h"
class Fan : public IDevice
{
public:
    enum class FanSpeed
    {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };
    Fan(const std::string& deviceName = "Unnamed Fan", PowerState powerState = PowerState::OFF, FanSpeed fanSpeed = FanSpeed::Level1);
    virtual ~Fan();
    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual void status() override;
    Fan::FanSpeed getFanSpeed();
    void setFanSpeed(Fan::FanSpeed value);

private:
    Fan::FanSpeed m_fanSpeed;
    

};

#endif