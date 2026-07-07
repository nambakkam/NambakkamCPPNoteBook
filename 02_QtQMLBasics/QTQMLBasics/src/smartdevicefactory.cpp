#include "smartdevicefactory.h"
#include "light.h"
SmartDeviceFactory &SmartDeviceFactory::getInstance()
{
    static SmartDeviceFactory smartDeviceFactory;
    return smartDeviceFactory;
}

ISmartDevice *SmartDeviceFactory::createSmartDevice(DeviceEnums::Type type,const QString& name, QObject *parent)
{
    ISmartDevice* device = new Light(name,parent);
    return device;
}

SmartDeviceFactory::SmartDeviceFactory() {}
