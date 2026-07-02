#pragma once
#include "IDevice.h"

class AirConditioner final : public IDevice
{
public:

    explicit AirConditioner(const std::string& deviceName = "Unnamed Air Conditioner",
                            PowerState powerState = PowerState::OFF);
    ~AirConditioner() override;

    void turnOn() override;
    void turnOff() override;
    void status() const override;

    int getTemperature() const;
    void setTemperature(int value);

private:
    int m_temperature;
};
