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

QVector<QPointer<ISmartDevice>> Room::getDevices() const
{
    QVector<QPointer<ISmartDevice>> result;
    result.reserve(m_devices.size());
    for (ISmartDevice* device : m_devices)
        result.append(device); // ISmartDevice* -> QPointer<ISmartDevice>, implicit
    return result;
}

QString Room::getRoomName() const
{
    return m_RoomName;
}
