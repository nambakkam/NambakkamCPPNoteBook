#include "devicecontroller.h"

DeviceController::DeviceController(QObject *parent)
    : QObject(parent)
    , m_deviceModel(new DeviceListModel(this)) // Lifecycle managed automatically
{
}

DeviceListModel* DeviceController::deviceModel() const
{
    return m_deviceModel;
}

Room* DeviceController::currentRoom() const
{
    return m_currentRoom;
}

void DeviceController::setCurrentRoom(Room* room)
{
    if (m_currentRoom == room)
        return;

    // Disconnect signals from the old room if one was active
    if (m_currentRoom) {
        disconnect(m_currentRoom, &Room::devicesChanged, this, &DeviceController::refreshModelData);
    }

    m_currentRoom = room;

    // Connect to the new room so the UI updates when devices are added or deleted
    if (m_currentRoom) {
        connect(m_currentRoom, &Room::devicesChanged, this, &DeviceController::refreshModelData);
    }

    refreshModelData();
    emit currentRoomChanged();
}

void DeviceController::refreshModelData()
{
    if (m_currentRoom) {
        m_deviceModel->setDevices(m_currentRoom->getDevices());
    } else {
        m_deviceModel->setDevices(QVector<ISmartDevice*>()); // Clear if no room selected
    }
}

void DeviceController::addDeviceToCurrentRoom(int type, const QString& name)
{
    if (m_currentRoom) {
        // Cast int safely back to your enum type
        m_currentRoom->addDevice(static_cast<DeviceEnums::Type>(type), name);
    }
}

void DeviceController::removeDeviceFromCurrentRoom(int index)
{
    if (m_currentRoom) {
        m_currentRoom->removeDevice(index);
    }
}
