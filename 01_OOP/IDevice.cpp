#include "IDevice.h"
#include <iostream>
#include <utility>

IDevice::IDevice(const std::string& deviceName, PowerState powerState)
    : m_powerState(powerState), m_deviceName(deviceName)
{
    std::cout << "IDevice object created with " << m_deviceName << '\n';
}

IDevice::~IDevice()
{
    std::cout << "IDevice object destroyed with " << m_deviceName << '\n';
}

void IDevice::turnOn()
{
    setPowerState(PowerState::ON);
}

void IDevice::turnOff()
{
    setPowerState(PowerState::OFF);
}

IDevice::PowerState IDevice::getPowerState() const
{
    return m_powerState;
}

void IDevice::setPowerState(PowerState value) {
    m_powerState = value;
}

const std::string& IDevice::getDeviceName() const {
    return m_deviceName;
}

void IDevice::setDeviceName(const std::string& value) {
    m_deviceName = value;
}