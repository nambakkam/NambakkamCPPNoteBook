#include "DeviceFactory.h"
#include "IDevice.h"
#include "Light.h"
#include "Fan.h"    


std::unique_ptr<IDevice> DeviceFactory::createDevice(DeviceFactory::DeviceType type)
{
    switch (type)
    {
    case DeviceType::LIGHT:
        return std::make_unique<Light>("Light"+std::to_string(referenceCount+1), IDevice::PowerState::OFF, Light::BrightnessLevel::MEDIUM);
    case DeviceType::FAN:
        return std::make_unique<Fan>("Fan"+std::to_string(referenceCount+1), IDevice::PowerState::OFF, Fan::FanSpeed::Level1);
    case DeviceType::AirConditioner:
        // Assuming AirConditioner class is defined elsewhere
        // return std::make_unique<AirConditioner>();
        std::cout << "AirConditioner creation not implemented yet." << std::endl;
        return nullptr;
    default:
        std::cout << "Invalid device type." << std::endl;
        return nullptr;
    }
    referenceCount++;

}

DeviceFactory &DeviceFactory::getInstance()
{
    static DeviceFactory instance;
    return instance;
}
