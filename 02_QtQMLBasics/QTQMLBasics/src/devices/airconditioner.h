#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "ismartdevice.h"

class AirConditioner : public ISmartDevice
{
    Q_OBJECT

    // Exposed AC specific properties
    Q_PROPERTY(int targetTemperature READ targetTemperature WRITE setTargetTemperature NOTIFY targetTemperatureChanged)
    Q_PROPERTY(DeviceEnums::FanSpeed fanSpeed READ fanSpeed WRITE setFanSpeed NOTIFY fanSpeedChanged)

public:
    explicit AirConditioner(const QString &name, QObject *parent = nullptr);

    int targetTemperature() const;
    void setTargetTemperature(int temp);

    DeviceEnums::FanSpeed fanSpeed() const;
    void setFanSpeed(DeviceEnums::FanSpeed speed);

signals:
    void targetTemperatureChanged(int temp);
    void fanSpeedChanged(DeviceEnums::FanSpeed speed);

private:
    int m_targetTemperature;
    DeviceEnums::FanSpeed m_fanSpeed;
};

#endif // AIRCONDITIONER_H
