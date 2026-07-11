#include "airconditioner.h"

AirConditioner::AirConditioner(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::AirConditioner, DeviceEnums::Off, parent)
    , m_targetTemperature(24) // Default pleasant startup temp
    , m_fanSpeed(DeviceEnums::Auto)
{
}

int AirConditioner::targetTemperature() const
{
    return m_targetTemperature;
}

void AirConditioner::setTargetTemperature(int temp)
{
    // Bound the temperature between realistic hardware constraints (16C - 30C)
    if (temp < 16) temp = 16;
    if (temp > 30) temp = 30;

    if (m_targetTemperature != temp) {
        m_targetTemperature = temp;
        emit targetTemperatureChanged(m_targetTemperature);
    }
}

DeviceEnums::FanSpeed AirConditioner::fanSpeed() const
{
    return m_fanSpeed;
}

void AirConditioner::setFanSpeed(DeviceEnums::FanSpeed speed)
{
    if (m_fanSpeed != speed) {
        m_fanSpeed = speed;
        emit fanSpeedChanged(m_fanSpeed);
    }
}

