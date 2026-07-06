#include "light.h"
#include "deviceenums.h"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()

Light::Light(QString deviceNameVal,QObject *parent) : ISmartDevice(deviceNameVal,DeviceEnums::Light,DeviceEnums::Off,parent),m_brightnessLevel(50)
{

}

void Light::togglePower() // Adding some randomness
{
    // Seed random once if you haven't done it elsewhere in main.cpp
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }

    // Roll a 100-sided die (1 to 100)
    int roll = (std::rand() % 100) + 1;

    if (roll <= 85) {
        // Normal Toggling Behavior (85% of the time)
        if (m_deviceState == DeviceEnums::On) {
            m_deviceState = DeviceEnums::Off;
        } else {
            // If it was Off, Error, or Undefined, turning it on resets/toggles it to On
            m_deviceState = DeviceEnums::On;
        }
    }
    else if (roll > 85 && roll <= 95) {
        // Device Glitch: Error State (10% of the time)
        m_deviceState = DeviceEnums::Error;
    }
    else {
        // Hardware/Network Drop: Undefined State (5% of the time)
        m_deviceState = DeviceEnums::Undefined;
    }

    // Optional: Emit a signal here if you have a stateChanged signal!
    emit deviceStateChanged(m_deviceState);
}

void Light::setBrightness(int level)
{
    if(m_brightnessLevel != level){
        m_brightnessLevel = level;
        emit brightnessChanged(m_brightnessLevel);
    }
}

int Light::getBrightness()
{
    return m_brightnessLevel;
}
