#ifndef SMARTDEVICEFACTORY_H
#define SMARTDEVICEFACTORY_H
#include "deviceenums.h"
#include "ismartdevice.h"
class SmartDeviceFactory
{
public:
    static SmartDeviceFactory& getInstance();
    ISmartDevice* createSmartDevice(DeviceEnums::Type type,const QString& name, QObject* parent = nullptr);
private:
    SmartDeviceFactory() = default;
    ~SmartDeviceFactory() = default;
    SmartDeviceFactory(const SmartDeviceFactory&) = delete;
    SmartDeviceFactory& operator=(const SmartDeviceFactory&) = delete;
    SmartDeviceFactory(SmartDeviceFactory&&) = delete;
    SmartDeviceFactory& operator=(SmartDeviceFactory&&) = delete;
};

#endif // SMARTDEVICEFACTORY_H
