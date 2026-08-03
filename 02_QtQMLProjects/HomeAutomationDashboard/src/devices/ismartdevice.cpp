#include "ismartdevice.h"


ISmartDevice::ISmartDevice(const QString& deviceNameVal, DeviceEnums::Type deviceTypeVal,DeviceEnums::DeviceStates stateVal, QObject *parent) : m_deviceName(deviceNameVal), m_deviceType(deviceTypeVal),m_deviceState(stateVal),QObject(parent)
{

}

QString ISmartDevice::getDeviceName() const
{
    return m_deviceName;
}

DeviceEnums::Type ISmartDevice::getDeviceType() const
{
    return m_deviceType;
}

DeviceEnums::DeviceStates ISmartDevice::getDeviceState() const
{
    return m_deviceState;
}

void ISmartDevice::togglePower(){
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
        if (getDeviceState() == DeviceEnums::On) {
            setDeviceState(DeviceEnums::Off);
        } else {
            // If it was Off, Error, or Undefined, turning it on resets/toggles it to On
            setDeviceState(DeviceEnums::On);
        }
    }
    else if (roll > 85 && roll <= 95) {
        // Device Glitch: Error State (10% of the time)
        setDeviceState(DeviceEnums::Error);
    }
    else {
        // Hardware/Network Drop: Undefined State (5% of the time)
        setDeviceState(DeviceEnums::Undefined);
    }

}

void ISmartDevice::setDeviceState(const DeviceEnums::DeviceStates &state)
{
    if(m_deviceState != state){
        m_deviceState = state;
        emit deviceStateChanged(m_deviceState);
    }
}
