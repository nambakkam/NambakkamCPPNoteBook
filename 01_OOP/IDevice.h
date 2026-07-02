#pragma once
#include <string>

class IDevice
{
public:
    enum class PowerState { ON, OFF };

    explicit IDevice(const std::string& deviceName = "Unnamed Device",
                      PowerState powerState = PowerState::OFF);
    virtual ~IDevice();

    IDevice(const IDevice&) = delete;
    IDevice& operator=(const IDevice&) = delete;
    IDevice(IDevice&&) = delete;
    IDevice& operator=(IDevice&&) = delete;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void status() const = 0;

    PowerState getPowerState() const;
    void setPowerState(PowerState value);

    const std::string& getDeviceName() const;
    void setDeviceName(const std::string& value);

protected:
    PowerState m_powerState;
    std::string m_deviceName;
};