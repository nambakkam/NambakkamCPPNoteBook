#include "Light.h"

Light::Light(const std::string& deviceName, PowerState powerState, BrightnessLevel brightnessLevel) : IDevice(deviceName, powerState), m_brightnessLevel(brightnessLevel)
{
    std::cout << "Light object created." << getDeviceName() << std::endl;
}

Light::~Light()
{
    std::cout << "Light object destroyed." << getDeviceName() << std::endl;
}

void Light::turnOn()
{
    //perform some hardware specific operations to turn on the light
    setPowerState(IDevice::PowerState::ON);
    std::cout << "Light is turned on." << getDeviceName() << std::endl;
}

void Light::turnOff()
{
    //perform some hardware specific operations to turn off the light
    setPowerState(IDevice::PowerState::OFF);
    std::cout << "Light is turned off." << getDeviceName() << std::endl;
}

void Light::status()
{
    //perform some hardware specific operations to get the status of the light
    if (getPowerState() == IDevice::PowerState::ON) {
        std::cout << "Light is on." << getDeviceName() << std::endl;
    } else {
        std::cout << "Light is off." << getDeviceName() << std::endl;
    }
}

Light::BrightnessLevel Light::getBrightnessLevel() {
    return m_brightnessLevel;
}
void Light::setBrightnessLevel(Light::BrightnessLevel value) {
    m_brightnessLevel = value;
}
