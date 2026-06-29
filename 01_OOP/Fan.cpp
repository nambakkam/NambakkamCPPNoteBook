#include "Fan.h"

Fan::Fan(const std::string& deviceName, PowerState powerState, FanSpeed fanSpeed) : IDevice(deviceName, powerState), m_fanSpeed(fanSpeed)
{
    std::cout << "Fan object created." << std::endl;
}

Fan::~Fan()
{
    std::cout << "Fan object destroyed." << std::endl;
}

void Fan::turnOn()
{
    //perform some hardware specific operations to turn on the fan
    setPowerState(IDevice::PowerState::ON);
    std::cout << "Fan is turned on." << std::endl;
}

void Fan::turnOff()
{
    //perform some hardware specific operations to turn off the fan
    setPowerState(IDevice::PowerState::OFF);
    std::cout << "Fan is turned off." << std::endl;
}

void Fan::status()
{
    //perform some hardware specific operations to get the fan status
    if (getPowerState() == PowerState::ON) {
        std::cout << "Fan is on." << std::endl;
    } else {
        std::cout << "Fan is off." << std::endl;
    }
}

Fan::FanSpeed Fan::getFanSpeed() {
    return m_fanSpeed;
}
void Fan::setFanSpeed(Fan::FanSpeed value) {
    m_fanSpeed = value;
}
