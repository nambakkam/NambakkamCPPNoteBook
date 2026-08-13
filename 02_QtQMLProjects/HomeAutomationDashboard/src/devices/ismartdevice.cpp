#include "ismartdevice.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QTimer>

ISmartDevice::ISmartDevice(const QString& deviceId,const QString& deviceNameVal, DeviceEnums::Type deviceTypeVal,bool stateVal, QObject *parent) : m_deviceId(deviceId),m_deviceName(deviceNameVal), m_deviceType(deviceTypeVal),m_powerState(stateVal),QObject(parent)
{
    QTimer::singleShot(0, this, &ISmartDevice::autoConnectStateSignals);
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

QString ISmartDevice::getDeviceId() const
{
    return m_deviceId;
}

void ISmartDevice::autoConnectStateSignals() {
    const QMetaObject *meta = metaObject();
    QMetaMethod stateSignal = QMetaMethod::fromSignal(&ISmartDevice::stateChanged);

    // Iterate through all properties defined in derived classes
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        if (prop.hasNotifySignal()) {
            connect(this, prop.notifySignal(), this, stateSignal, Qt::UniqueConnection);
        }
    }
}
