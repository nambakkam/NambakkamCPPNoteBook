#include "ismartdevice.h"


ISmartDevice::ISmartDevice(QString deviceNameVal, DeviceEnums::Type deviceTypeVal,DeviceEnums::DeviceStates stateVal, QObject *parent) : m_deviceName(deviceNameVal), m_deviceType(deviceTypeVal),m_deviceState(stateVal),QObject(parent)
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

DeviceEnums::DeviceStates ISmartDevice::getDeviceState() const
{
    return m_deviceState;
}
