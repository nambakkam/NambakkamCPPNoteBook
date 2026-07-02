#pragma once
#include "IDevice.h"
#include <string>

class Fan final : public IDevice
{
public:
    enum class FanSpeed
    {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };

    explicit Fan(const std::string& deviceName = "Unnamed Fan",
                  PowerState powerState = PowerState::OFF,
                  FanSpeed fanSpeed = FanSpeed::Level1);

    ~Fan() override;

    void turnOn() override;
    void turnOff() override;
    void status() const override;

    FanSpeed getFanSpeed() const;
    void setFanSpeed(FanSpeed value);

private:
    FanSpeed m_fanSpeed;

    static std::string fanSpeedToString(FanSpeed level);
};