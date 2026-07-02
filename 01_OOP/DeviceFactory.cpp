#include "DeviceFactory.h"
#include "IDevice.h"
#include "Light.h"
#include "Fan.h"
#include "AirConditioner.h"
#include <iostream>

std::unique_ptr<IDevice> DeviceFactory::createDevice(DeviceType type)
{
    switch (type)
    {
        case DeviceType::LIGHT:
        {
            static int lightCount = 0;
            ++lightCount;
            return std::make_unique<Light>("Light" + std::to_string(lightCount),
                                            IDevice::PowerState::OFF,
                                            Light::BrightnessLevel::MEDIUM);
        }
        case DeviceType::FAN:
        {
            static int fanCount = 0;
            ++fanCount;
            return std::make_unique<Fan>("Fan" + std::to_string(fanCount),
                                          IDevice::PowerState::OFF,
                                          Fan::FanSpeed::Level1);
        }
        case DeviceType::AIR_CONDITIONER:
        {
            static int acCount = 0;
            ++acCount;
            return std::make_unique<AirConditioner>("AirConditioner" + std::to_string(acCount),
                                                    IDevice::PowerState::OFF);
        }
        default:
            std::cout << "Invalid device type.\n";
            return nullptr;
    }
}