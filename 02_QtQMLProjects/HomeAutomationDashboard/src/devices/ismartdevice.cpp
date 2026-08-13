#include "ismartdevice.h"


ISmartDevice::ISmartDevice(const QString& deviceNameVal, DeviceEnums::Type deviceTypeVal,bool stateVal, QObject *parent) : m_deviceName(deviceNameVal), m_deviceType(deviceTypeVal),m_powerState(stateVal),QObject(parent)
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

bool ISmartDevice::getPowerState() const
{
    return m_powerState;
}


void ISmartDevice::setPowerState(bool state)
{
    if(m_powerState != state){
        m_powerState = state;
        emit powerStateChanged(m_powerState);
    }
}
