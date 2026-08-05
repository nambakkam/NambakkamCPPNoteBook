#include "smartdevicemanager.h"
#include <QDebug>

SmartDeviceManager::SmartDeviceManager(QObject *parent)
    : QObject(parent)
    , m_roomsModel(new RoomsModel(this))
    , m_deviceModel(new DeviceListModel(this))
    , m_currentRoom(nullptr)
    , m_themeManager(new ThemeManager(this))
{
}

RoomsModel* SmartDeviceManager::roomsModel() const { return m_roomsModel; }
DeviceListModel* SmartDeviceManager::deviceModel() const { return m_deviceModel; }

ThemeManager *SmartDeviceManager::themeManager() const
{
    return m_themeManager;
}

// Dynamically compute index from m_currentRoom pointer
int SmartDeviceManager::currentRoomIndex() const
{
    return m_currentRoom ? m_rooms.indexOf(m_currentRoom) : -1;
}

void SmartDeviceManager::setCurrentRoom(QPointer<Room> room)
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

    // Emit the new index derived directly from m_currentRoom
    emit currentRoomIndexChanged(currentRoomIndex());
}

void SmartDeviceManager::setCurrentRoomIndex(int index)
{
    if (index < 0 || index >= m_rooms.size()) {
        qWarning() << "setCurrentRoomIndex: Index out of bounds:" << index;
        setCurrentRoom(nullptr);
        return;
    }

    // Setting room via pointer automatically updates index and emits signal
    setCurrentRoom(m_rooms.at(index));
}

QVariantList SmartDeviceManager::deviceTypeModel() const
{
    return QVariantList{
        QVariantMap{{"name", "Light"},           {"type", DeviceEnums::Light},          {"prefix", "Smart Light"}},
        QVariantMap{{"name", "Air Conditioner"}, {"type", DeviceEnums::AirConditioner}, {"prefix", "AC Unit"}},
        QVariantMap{{"name", "Refrigerator"},    {"type", DeviceEnums::Fridge},         {"prefix", "Fridge"}},
        QVariantMap{{"name", "Washing Machine"}, {"type", DeviceEnums::WashingMachine}, {"prefix", "Washing Machine"}},
        QVariantMap{{"name", "Television"},      {"type", DeviceEnums::Television},     {"prefix", "Smart TV"}},
        QVariantMap{{"name", "Smart Plug"},      {"type", DeviceEnums::SmartPlug},      {"prefix", "Smart Plug"}},
        QVariantMap{{"name", "Security Camera"}, {"type", DeviceEnums::SecurityCamera}, {"prefix", "Camera"}}
    };
}

void SmartDeviceManager::addRoom(const QString &roomName)
{
    Room* newRoom = new Room(roomName, this);
    m_rooms.append(newRoom);

    m_roomsModel->updateRooms(m_rooms);
    emit roomsChanged();

    setCurrentRoom(newRoom);
}

void SmartDeviceManager::removeRoom(int index)
{
    if (index < 0 || index >= m_rooms.size()) {
        qWarning() << "removeRoom: Index out of bounds:" << index;
        return;
    }

    QPointer<Room> roomToRemove = m_rooms.takeAt(index);

    if (m_currentRoom == roomToRemove) {
        // If we removed active room, select adjacent room or nullptr
        if (!m_rooms.isEmpty()) {
            int newIndex = qMin(index, static_cast<int>(m_rooms.size()) - 1);
            setCurrentRoom(m_rooms.at(newIndex));
        } else {
            setCurrentRoom(nullptr);
        }
    } else {
        // Active room didn't change, BUT its index position might have shifted!
        emit currentRoomIndexChanged(currentRoomIndex());
    }

    if (roomToRemove) {
        roomToRemove->deleteLater();
    }

    m_roomsModel->updateRooms(m_rooms);
    emit roomsChanged();
}

void SmartDeviceManager::refreshDeviceModelData()
{
    if (m_currentRoom) {
        m_deviceModel->setDevices(m_currentRoom->getDevices());
    } else {
        m_deviceModel->setDevices(QVector<QPointer<ISmartDevice>>());
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
