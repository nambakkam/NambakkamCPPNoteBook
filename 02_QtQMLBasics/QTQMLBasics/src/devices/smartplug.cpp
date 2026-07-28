#include "smartplug.h"

SmartPlug::SmartPlug(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::SmartPlug, DeviceEnums::Off, parent)
    , m_currentPowerWatts(0.0)
    , m_totalEnergyKWh(0.0)
    , m_countdownSeconds(0)
    , m_overloadThresholdWatts(3680.0) // Standard 16A / 230V ceiling limit (~3680W)
    , m_isOverloaded(false)
{
}

double SmartPlug::currentPowerWatts() const
{
    return m_currentPowerWatts;
}

double SmartPlug::totalEnergyKWh() const
{
    return m_totalEnergyKWh;
}

int SmartPlug::countdownSeconds() const
{
    return m_countdownSeconds;
}

void SmartPlug::setCountdownSeconds(int seconds)
{
    const int validSeconds = qMax(0, seconds);
    if (m_countdownSeconds != validSeconds) {
        m_countdownSeconds = validSeconds;
        emit countdownSecondsChanged(m_countdownSeconds);
    }
}

double SmartPlug::overloadThresholdWatts() const
{
    return m_overloadThresholdWatts;
}

void SmartPlug::setOverloadThresholdWatts(double watts)
{
    if (watts > 0.0 && !qFuzzyCompare(m_overloadThresholdWatts, watts)) {
        m_overloadThresholdWatts = watts;
        emit overloadThresholdWattsChanged(m_overloadThresholdWatts);
    }
}

bool SmartPlug::isOverloaded() const
{
    return m_isOverloaded;
}

void SmartPlug::updatePowerUsage(double watts, double additionalKWh)
{
    if (getDeviceState() == DeviceEnums::Off) {
        watts = 0.0;
    }

    if (!qFuzzyCompare(m_currentPowerWatts, watts)) {
        m_currentPowerWatts = watts;
        emit currentPowerWattsChanged(m_currentPowerWatts);
    }

    if (additionalKWh > 0.0) {
        m_totalEnergyKWh += additionalKWh;
        emit totalEnergyKWhChanged(m_totalEnergyKWh);
    }

    // Safety check for overload
    if (m_currentPowerWatts > m_overloadThresholdWatts) {
        setOverloaded(true);
        setDeviceState(DeviceEnums::Error);
    }
}

void SmartPlug::resetTotalEnergy()
{
    if (!qFuzzyIsNull(m_totalEnergyKWh)) {
        m_totalEnergyKWh = 0.0;
        emit totalEnergyKWhChanged(m_totalEnergyKWh);
    }
}

void SmartPlug::setOverloaded(bool overloaded)
{
    if (m_isOverloaded != overloaded) {
        m_isOverloaded = overloaded;
        emit overloadedStateChanged(m_isOverloaded);
    }
}

void SmartPlug::togglePower()
{
    // If overloaded/error state, clear overload when turning off
    if (m_isOverloaded) {
        setOverloaded(false);
        setDeviceState(DeviceEnums::Off);
        m_currentPowerWatts = 0.0;
        emit currentPowerWattsChanged(m_currentPowerWatts);
        return;
    }

    auto newState = (getDeviceState() == DeviceEnums::On) 
                    ? DeviceEnums::Off 
                    : DeviceEnums::On;

    if (newState == DeviceEnums::Off) {
        m_currentPowerWatts = 0.0;
        emit currentPowerWattsChanged(m_currentPowerWatts);
    }

    setDeviceState(newState);
}