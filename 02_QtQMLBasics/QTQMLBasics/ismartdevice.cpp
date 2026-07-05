#include "ismartdevice.h"


ISmartDevice::ISmartDevice(QString deviceNameVal, DeviceEnums::Type deviceTypeVal, QObject *parent) : m_deviceName(deviceNameVal), m_deviceType(deviceTypeVal),QObject(parent)
{

}

QString ISmartDevice::getDeviceName() const
{
    return m_deviceName;
}

DeviceEnums::Type ISmartDevice::getDeviceType() const
{
    return m_deviceType;
}
