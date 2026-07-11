#include "room.h"
#include "smartdevicefactory.h"

Room::Room(const QString &roomNameVal, QObject *parent)
    : m_RoomName(roomNameVal),QObject{parent}
{}


void Room::addDevice(DeviceEnums::Type deviceType, const QString& deviceName)
{
    ISmartDevice* newDevice = SmartDeviceFactory::getInstance().createSmartDevice(deviceType, deviceName,this);
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

QVector<ISmartDevice*> Room::getDevices()
{
    return m_devices;
}

QString Room::getRoomName() const
{
    return m_RoomName;
}
