#include "AirConditioner.h"
#include <iostream>

AirConditioner::AirConditioner(const std::string &deviceName, PowerState powerState) : IDevice(deviceName, powerState), m_temperature(24)
{
    std::cout << "AirConditioner object created: " << getDeviceName() << '\n';  
}

AirConditioner::~AirConditioner()
{
    std::cout << "AirConditioner object destroyed: " << getDeviceName() << '\n';  
}

void AirConditioner::turnOn()
{
    //perform some hardware specific operations to turn on the air conditioner
    IDevice::turnOn();
    std::cout << "AirConditioner is turned on: " << getDeviceName() << '\n';  
}

void AirConditioner::turnOff()
{
    //perform some hardware specific operations to turn off the air conditioner
    IDevice::turnOff();
    std::cout << "AirConditioner is turned off: " << getDeviceName() << '\n';  
}

void AirConditioner::status() const
{
    // perform some hardware specific operations to get the status of the air conditioner
    std::cout << "AirConditioner [" << getDeviceName() << "] is "
               << (getPowerState() == PowerState::ON ? "on" : "off")
               << ", temperature: " << m_temperature << "°C"
               << '\n';
}

int AirConditioner::getTemperature() const
{
    return m_temperature;
}

void AirConditioner::setTemperature(int value)
{
    m_temperature = value;
}
