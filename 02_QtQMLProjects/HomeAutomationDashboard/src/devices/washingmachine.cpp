#include "washingmachine.h"

WashingMachine::WashingMachine(const QString &name, QObject *parent)
    : ISmartDevice(name, DeviceEnums::WashingMachine, DeviceEnums::Off, parent)
    , m_spinSpeed(1000)
    , m_waterTemperature(40)
    , m_washCycle(DeviceEnums::Cotton)
    , m_isRunning(false)
    , m_childLock(false)
    , m_timeRemainingMinutes(0)
{
}

int WashingMachine::spinSpeed() const
{
    return m_spinSpeed;
}

void WashingMachine::setSpinSpeed(int rpm)
{
    if (m_isRunning) return; // Prevent changing configuration during active wash cycle

    const int clampedSpeed = qBound(minSpinSpeed, rpm, maxSpinSpeed);
    if (m_spinSpeed != clampedSpeed) {
        m_spinSpeed = clampedSpeed;
        emit spinSpeedChanged(m_spinSpeed);
    }
}

int WashingMachine::waterTemperature() const
{
    return m_waterTemperature;
}

void WashingMachine::setWaterTemperature(int temp)
{
    if (m_isRunning) return;

    const int clampedTemp = qBound(minWaterTemp, temp, maxWaterTemp);
    if (m_waterTemperature != clampedTemp) {
        m_waterTemperature = clampedTemp;
        emit waterTemperatureChanged(m_waterTemperature);
    }
}

DeviceEnums::WashCycle WashingMachine::washCycle() const
{
    return m_washCycle;
}

void WashingMachine::setWashCycle(DeviceEnums::WashCycle cycle)
{
    if (m_isRunning) return;

    if (m_washCycle != cycle) {
        m_washCycle = cycle;
        emit washCycleChanged(m_washCycle);
    }
}

bool WashingMachine::isRunning() const
{
    return m_isRunning;
}

bool WashingMachine::childLock() const
{
    return m_childLock;
}

void WashingMachine::setChildLock(bool locked)
{
    if (m_childLock != locked) {
        m_childLock = locked;
        emit childLockChanged(m_childLock);
    }
}

int WashingMachine::timeRemainingMinutes() const
{
    return m_timeRemainingMinutes;
}

void WashingMachine::startCycle()
{
    if (getDeviceState() == DeviceEnums::Off || m_isRunning) return;

    m_isRunning = true;
    emit isRunningChanged(m_isRunning);
    updateTimeRemaining(45); // Standard cycle duration mock value
}

void WashingMachine::pauseCycle()
{
    if (!m_isRunning) return;

    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
}

void WashingMachine::stopCycle()
{
    m_isRunning = false;
    emit isRunningChanged(m_isRunning);
    updateTimeRemaining(0);
}

void WashingMachine::togglePower()
{
    auto newState = (getDeviceState() == DeviceEnums::On) 
                    ? DeviceEnums::Off 
                    : DeviceEnums::On;

    if (newState == DeviceEnums::Off && m_isRunning) {
        stopCycle();
    }

    setDeviceState(newState);
}

void WashingMachine::updateTimeRemaining(int minutes)
{
    if (m_timeRemainingMinutes != minutes) {
        m_timeRemainingMinutes = minutes;
        emit timeRemainingMinutesChanged(m_timeRemainingMinutes);
    }
}