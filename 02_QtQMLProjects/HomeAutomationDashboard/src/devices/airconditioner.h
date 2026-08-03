#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "ismartdevice.h"

class AirConditioner : public ISmartDevice
{
    Q_OBJECT

    // Exposed AC specific properties
    Q_PROPERTY(int targetTemperature READ targetTemperature WRITE setTargetTemperature NOTIFY targetTemperatureChanged)
    Q_PROPERTY(DeviceEnums::FanSpeed fanSpeed READ fanSpeed WRITE setFanSpeed NOTIFY fanSpeedChanged)

    Q_PROPERTY(int lowestTempSetting READ getLowestTempSetting CONSTANT)
    Q_PROPERTY(int highestTempSetting READ getHighestTempSetting CONSTANT)

public:
    explicit AirConditioner(const QString &name, QObject *parent = nullptr);

    int targetTemperature() const;
    DeviceEnums::FanSpeed fanSpeed() const;
    static constexpr int lowestTempSetting{16};
    static constexpr int highestTempSetting{30};

    int getLowestTempSetting() const;
    int getHighestTempSetting() const;

public slots:
    void togglePower() override;
    void setTargetTemperature(int temp);
    void setFanSpeed(DeviceEnums::FanSpeed speed);

signals:
    void targetTemperatureChanged(int temp);
    void fanSpeedChanged(DeviceEnums::FanSpeed speed);

private:
    int m_targetTemperature;
    DeviceEnums::FanSpeed m_fanSpeed;

};

#endif // AIRCONDITIONER_H
