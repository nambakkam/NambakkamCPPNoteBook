#include "fridge.h"

Fridge::Fridge(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::Fridge, DeviceEnums::On, parent) // Fridges default to On
    , m_fridgeTemperature(3)    // Default pleasant fridge temp (3°C)
    , m_freezerTemperature(-18) // Standard freezer temp (-18°C)
    , m_rapidCool(false)
    , m_superFreeze(false)
    , m_isDoorOpen(false)
{
}

int Fridge::fridgeTemperature() const
{
    return m_fridgeTemperature;
}

void Fridge::setFridgeTemperature(int temp)
{
    const int clampedTemp = qBound(lowestFridgeTemp, temp, highestFridgeTemp);
    if (m_fridgeTemperature != clampedTemp) {
        m_fridgeTemperature = clampedTemp;
        emit fridgeTemperatureChanged(m_fridgeTemperature);
    }
}

int Fridge::freezerTemperature() const
{
    return m_freezerTemperature;
}

void Fridge::setFreezerTemperature(int temp)
{
    const int clampedTemp = qBound(lowestFreezerTemp, temp, highestFreezerTemp);
    if (m_freezerTemperature != clampedTemp) {
        m_freezerTemperature = clampedTemp;
        emit freezerTemperatureChanged(m_freezerTemperature);
    }
}

bool Fridge::rapidCool() const
{
    return m_rapidCool;
}

void Fridge::setRapidCool(bool enabled)
{
    if (m_rapidCool != enabled) {
        m_rapidCool = enabled;
        emit rapidCoolChanged(m_rapidCool);
    }
}

bool Fridge::superFreeze() const
{
    return m_superFreeze;
}

void Fridge::setSuperFreeze(bool enabled)
{
    if (m_superFreeze != enabled) {
        m_superFreeze = enabled;
        emit superFreezeChanged(m_superFreeze);
    }
}

bool Fridge::isDoorOpen() const
{
    return m_isDoorOpen;
}

void Fridge::setDoorOpen(bool open)
{
    if (m_isDoorOpen != open) {
        m_isDoorOpen = open;
        emit doorStateChanged(m_isDoorOpen);
    }
}

void Fridge::togglePower()
{
    auto newState = (getDeviceState() == DeviceEnums::On) 
                    ? DeviceEnums::Off 
                    : DeviceEnums::On;
    setDeviceState(newState);
}