#include "Fan.h"
#include <iostream>

Fan::Fan(const std::string& deviceName, PowerState powerState, FanSpeed fanSpeed)
    : IDevice(deviceName, powerState), m_fanSpeed(fanSpeed)
{
    std::cout << "Fan object created: " << getDeviceName() << '\n';
}

Fan::~Fan()
{
    std::cout << "Fan object destroyed: " << getDeviceName() << '\n';
}

void Fan::turnOn()
{
    // perform some hardware specific operations to turn on the fan
    IDevice::turnOn();
    std::cout << "Fan is turned on: " << getDeviceName() << '\n';
}

void Fan::turnOff()
{
    // perform some hardware specific operations to turn off the fan
    IDevice::turnOff();
    std::cout << "Fan is turned off: " << getDeviceName() << '\n';
}

void Fan::status() const
{
    // perform some hardware specific operations to get the fan status
    std::cout << "Fan [" << getDeviceName() << "] is "
               << (getPowerState() == PowerState::ON ? "on" : "off")
               << ", speed: " << fanSpeedToString(m_fanSpeed)
               << '\n';
}

Fan::FanSpeed Fan::getFanSpeed() const {
    return m_fanSpeed;
}

void Fan::setFanSpeed(FanSpeed value) {
    m_fanSpeed = value;
}

std::string Fan::fanSpeedToString(FanSpeed level)
{
    switch (level) {
        case FanSpeed::Level1: return "Level1";
        case FanSpeed::Level2: return "Level2";
        case FanSpeed::Level3: return "Level3";
        case FanSpeed::Level4: return "Level4";
        case FanSpeed::Level5: return "Level5";
    }
    return "Unknown";  // safety net for future enum values not yet handled
}