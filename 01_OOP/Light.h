#pragma once
#include "IDevice.h"

class Light final : public IDevice
{
public:
    enum class BrightnessLevel { LOW, MEDIUM, HIGH };

    explicit Light(const std::string& deviceName = "Unnamed Light",
                    PowerState powerState = PowerState::OFF,
                    BrightnessLevel brightnessLevel = BrightnessLevel::MEDIUM);

    ~Light() override;

    void turnOn() override;
    void turnOff() override;
    void status() const override;

    BrightnessLevel getBrightnessLevel() const;
    void setBrightnessLevel(BrightnessLevel value);

private:
    BrightnessLevel m_brightnessLevel;
    static std::string brightnessToString(BrightnessLevel level);
};