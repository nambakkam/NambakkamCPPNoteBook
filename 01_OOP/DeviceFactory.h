#pragma once
#include <memory>

class IDevice;

class DeviceFactory
{
public:
    enum class DeviceType
    {
        LIGHT,
        FAN,
        AIR_CONDITIONER
    };

    static std::unique_ptr<IDevice> createDevice(DeviceType type);

    DeviceFactory() = delete;  // purely static utility class — never instantiated
};