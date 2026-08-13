#include "airconditioner.h"

AirConditioner::AirConditioner(const QString &deviceId,const QString &name, QObject *parent)
    : ISmartDevice(deviceId,name, DeviceEnums::AirConditioner, false, parent)
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
    if (temp < lowestTempSetting) temp = lowestTempSetting;
    if (temp > highestTempSetting) temp = highestTempSetting;

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

int AirConditioner::getLowestTempSetting() const
{
    return lowestTempSetting;
}

int AirConditioner::getHighestTempSetting() const
{
    return highestTempSetting;
}

void AirConditioner::updateState(const QJsonObject &state)
{
    qDebug() << "Published State " << state;
    if (state.contains("powerState")) {
        setPowerState(state["powerState"].toBool());
    }
    if (state.contains("targetTemperature")) {
        setTargetTemperature(state["targetTemperature"].toInt());
    }
    if (state.contains("fanSpeed")) {
        setFanSpeed(static_cast<DeviceEnums::FanSpeed>(state["fanSpeed"].toInt()));
    }
}

QJsonObject AirConditioner::currentState() const
{
    QJsonObject state;
    state["powerState"] = getPowerState();
    state["targetTemperature"] = m_targetTemperature;
    state["fanSpeed"] = static_cast<int>(m_fanSpeed);
    return state;
}
