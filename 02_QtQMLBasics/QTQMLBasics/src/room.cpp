#include "room.h"
#include "smartdevicefactory.h"

Room::Room(QObject *parent)
    : QObject{parent}
{}

Room::~Room()
{
    // Clean up allocated devices when the room is destroyed
    qDeleteAll(m_devices);
    m_devices.clear();
}

void Room::addDevice(DeviceEnums::Type deviceType, const QString& deviceName)
{
    ISmartDevice* newDevice = SmartDeviceFactory::getInstance().createSmartDevice(deviceType, deviceName);
    if (newDevice) {
        m_devices.append(newDevice);
        emit devicesChanged();
    }
}

void Room::removeDevice(int index)
{
    if (index >= 0 && index < m_devices.size()) {
        ISmartDevice* device = m_devices.takeAt(index);
        device->deleteLater(); // Safely delete the QObject
        emit devicesChanged();
    }
}

QQmlListProperty<ISmartDevice> Room::getDevices()
{
    return QQmlListProperty<ISmartDevice>(this,&m_devices);
}
