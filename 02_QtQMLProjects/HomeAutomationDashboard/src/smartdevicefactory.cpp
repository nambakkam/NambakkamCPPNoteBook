#include "smartdevicefactory.h"
#include "light.h"
#include "airconditioner.h"
#include "fridge.h"
#include "washingmachine.h"
#include "television.h"
#include "smartplug.h"
#include "securitycamera.h"
#include "deviceidgenerator.h"
#include <QDebug>
SmartDeviceFactory &SmartDeviceFactory::getInstance()
{
    static SmartDeviceFactory smartDeviceFactory;
    return smartDeviceFactory;
}

ISmartDevice* SmartDeviceFactory::createSmartDevice(DeviceEnums::Type type, const QString &name, QObject *parent)
{
    QString deviceId = DeviceIdGenerator::generateUniqueId(type);
    qDebug() << "Unique ID is " << deviceId;
    switch (type) {
    case DeviceEnums::Light:
        return new Light(deviceId,name, parent);

    case DeviceEnums::AirConditioner:
        return new AirConditioner(deviceId,name, parent);

    case DeviceEnums::Fridge:
        return new Fridge(deviceId,name, parent);

    case DeviceEnums::WashingMachine:
        return new WashingMachine(deviceId,name, parent);

    case DeviceEnums::Television:
        return new Television(deviceId,name, parent);

    case DeviceEnums::SmartPlug:
        return new SmartPlug(deviceId,name, parent);

    case DeviceEnums::SecurityCamera:
        return new SecurityCamera(deviceId,name, parent);

    case DeviceEnums::Unknown:
    default:
        return nullptr;
    }
}

