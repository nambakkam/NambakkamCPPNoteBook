#include "Light.h"
#include <iostream>

Light::Light(const std::string& deviceName, PowerState powerState, BrightnessLevel brightnessLevel)
    : IDevice(deviceName, powerState), m_brightnessLevel(brightnessLevel)
{
    std::cout << "Light object created: " << getDeviceName() << '\n';
}

Light::~Light()
{
    std::cout << "Light object destroyed: " << getDeviceName() << '\n';
}

void Light::turnOn()
{
    // perform some hardware specific operations to turn on the light
    IDevice::turnOn();
    std::cout << "Light is turned on: " << getDeviceName() << '\n';
}

void Light::turnOff()
{
    // perform some hardware specific operations to turn off the light
    IDevice::turnOff();
    std::cout << "Light is turned off: " << getDeviceName() << '\n';
}

void Light::status() const
{
    // perform some hardware specific operations to get the status of the light
    std::cout << "Light [" << getDeviceName() << "] is "
               << (getPowerState() == PowerState::ON ? "on" : "off")
               << ", brightness: " << brightnessToString(m_brightnessLevel)
               << '\n';
}

std::string Light::brightnessToString(BrightnessLevel level) {
    switch (level) {
        case BrightnessLevel::LOW:
            return "Low";
        case BrightnessLevel::MEDIUM:
            return "Medium";
        case BrightnessLevel::HIGH:
            return "High";
        default:
            return "Unknown";
    }
}

Light::BrightnessLevel Light::getBrightnessLevel() const {
    return m_brightnessLevel;
}

void Light::setBrightnessLevel(BrightnessLevel value) {
    m_brightnessLevel = value;
}