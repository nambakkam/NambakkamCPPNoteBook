#include "smartdevicefactory.h"
#include "light.h"
#include "airconditioner.h"
#include "fridge.h"
#include "washingmachine.h"
#include "television.h"
#include "smartplug.h"
#include "securitycamera.h"

SmartDeviceFactory &SmartDeviceFactory::getInstance()
{
    static SmartDeviceFactory smartDeviceFactory;
    return smartDeviceFactory;
}

ISmartDevice* SmartDeviceFactory::createSmartDevice(DeviceEnums::Type type, const QString &name, QObject *parent)
{
    switch (type) {
    case DeviceEnums::Light:
        return new Light(name, parent);

    case DeviceEnums::AirConditioner:
        return new AirConditioner(name, parent);

    case DeviceEnums::Fridge:
        return new Fridge(name, parent);

    case DeviceEnums::WashingMachine:
        return new WashingMachine(name, parent);

    case DeviceEnums::Television:
        return new Television(name, parent);

    case DeviceEnums::SmartPlug:
        return new SmartPlug(name, parent);

    case DeviceEnums::SecurityCamera:
        return new SecurityCamera(name, parent);

    case DeviceEnums::Unknown:
    default:
        return nullptr;
    }
}

