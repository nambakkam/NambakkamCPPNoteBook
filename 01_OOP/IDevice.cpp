#include "IDevice.h"

IDevice::IDevice(const std::string& deviceName, PowerState powerState) : m_powerState(powerState), m_deviceName(deviceName)
{
    std::cout << "IDevice object created." << std::endl;
}
IDevice::~IDevice()
{
    std::cout << "IDevice object destroyed." << std::endl;
}
IDevice::PowerState IDevice::getPowerState()
{
    return m_powerState;
}
void IDevice::setPowerState(IDevice::PowerState value) {
    m_powerState = value;
}

std::string IDevice::getDeviceName() {
    return m_deviceName;
}
void IDevice::setDeviceName(std::string value) {
    m_deviceName = value;
}
