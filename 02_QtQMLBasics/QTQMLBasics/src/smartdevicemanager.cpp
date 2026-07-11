#include "smartdevicemanager.h"

SmartDeviceManager::SmartDeviceManager(QObject *parent)
    : QObject(parent)
    , m_roomsModel(new RoomsModel(this))
    , m_deviceModel(new DeviceListModel(this))
{
}

RoomsModel* SmartDeviceManager::roomsModel() const { return m_roomsModel; }
DeviceListModel* SmartDeviceManager::deviceModel() const { return m_deviceModel; }
Room* SmartDeviceManager::currentRoom() const { return m_currentRoom; }

void SmartDeviceManager::setCurrentRoom(Room* room)
{
    if (m_currentRoom == room)
        return;

    if (m_currentRoom) {
        disconnect(m_currentRoom, &Room::devicesChanged, this, &SmartDeviceManager::refreshDeviceModelData);
    }

    m_currentRoom = room;

    if (m_currentRoom) {
        connect(m_currentRoom, &Room::devicesChanged, this, &SmartDeviceManager::refreshDeviceModelData);
    }

    refreshDeviceModelData();
    emit currentRoomChanged();
}

void SmartDeviceManager::refreshDeviceModelData()
{
    if (m_currentRoom) {
        m_deviceModel->setDevices(m_currentRoom->getDevices());
    } else {
        m_deviceModel->setDevices(QVector<ISmartDevice*>());
    }
}

void SmartDeviceManager::addRoom(const QString &roomName)
{
    Room* newRoom = new Room(roomName, this);
    m_rooms.append(newRoom);

    // Update the room model using the shared memory layout of QList/QVector in Qt 6
    m_roomsModel->updateRooms(m_rooms.toVector());
    emit roomsChanged();
}

void SmartDeviceManager::removeRoom(int index)
{
    if (index >= 0 && index < m_rooms.size()) {
        Room* room = m_rooms.takeAt(index);
        if (m_currentRoom == room) {
            setCurrentRoom(nullptr);
        }
        room->deleteLater();

        m_roomsModel->updateRooms(m_rooms.toVector());
        emit roomsChanged();
    }
}

void SmartDeviceManager::addDeviceToCurrentRoom(int type, const QString& deviceName)
{
    if (m_currentRoom) {
        m_currentRoom->addDevice(static_cast<DeviceEnums::Type>(type), deviceName);
    }
}

void SmartDeviceManager::removeDeviceFromCurrentRoom(int index)
{
    if (m_currentRoom) {
        m_currentRoom->removeDevice(index);
    }
}
