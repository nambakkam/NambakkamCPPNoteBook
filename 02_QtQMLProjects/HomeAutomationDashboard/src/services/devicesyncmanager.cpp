#include "devicesyncmanager.h"
#include "smartdevicemanager.h"
#include "mqttservice.h"
#include "room.h"
#include "ismartdevice.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

DeviceSyncManager::DeviceSyncManager(SmartDeviceManager *deviceManager, MqttService *mqttService, QObject *parent)
    : QObject(parent)
    ,m_deviceManager(nullptr)
    , m_mqttService(nullptr)
{
    if (deviceManager) {
        setDeviceManager(deviceManager);
    }
    if (mqttService) {
        setMqttService(mqttService);
    }
}

void DeviceSyncManager::setDeviceManager(SmartDeviceManager *deviceManager)
{
    if (m_deviceManager == deviceManager)
        return;

    if (m_deviceManager) {
        disconnect(m_deviceManager, &SmartDeviceManager::roomsChanged, this, &DeviceSyncManager::onRoomsChanged);
    }

    m_deviceManager = deviceManager;

    if (m_deviceManager) {
        connect(m_deviceManager, &SmartDeviceManager::roomsChanged, this, &DeviceSyncManager::onRoomsChanged);
        rebuildConnections();
    }
}

SmartDeviceManager* DeviceSyncManager::deviceManager() const
{
    return m_deviceManager;
}

void DeviceSyncManager::setMqttService(MqttService *mqttService)
{
    if (m_mqttService == mqttService)
        return;

    if (m_mqttService) {
        disconnect(m_mqttService, &MqttService::deviceStateReceived, this, &DeviceSyncManager::onMqttDeviceStateReceived);
    }

    m_mqttService = mqttService;

    if (m_mqttService) {
        // Connect inbound MQTT messages to update local domain objects
        connect(m_mqttService, &MqttService::deviceStateReceived,
                this, &DeviceSyncManager::onMqttDeviceStateReceived);
    }
}

MqttService* DeviceSyncManager::mqttService() const
{
    return m_mqttService;
}

// Re-wires dynamic connections to every room and device in the system
void DeviceSyncManager::rebuildConnections()
{
    if (!m_deviceManager)
        return;

    // Disconnect old tracked rooms
    for (const auto &room : m_trackedRooms) {
        if (room) {
            disconnect(room, &Room::devicesChanged, this, &DeviceSyncManager::onRoomDevicesChanged);
        }
    }
    m_trackedRooms.clear();

    // Iterate through all rooms and track them
    const QVector<QPointer<Room>>& rooms = m_deviceManager->rooms();
    for (const auto &room : rooms) {
        if (!room) continue;

        m_trackedRooms.append(room);
        connect(room, &Room::devicesChanged, this, &DeviceSyncManager::onRoomDevicesChanged);

        // Connect to each device inside this room
        const auto devices = room->getDevices();
        for (const auto &devicePointer : devices) {
            if (ISmartDevice *device = devicePointer.data()) {
                connectDeviceSignals(device);
            }
        }
    }
}

void DeviceSyncManager::connectDeviceSignals(ISmartDevice *device)
{
    if (!device) return;

    // Connect device state changes to trigger MQTT outbound sync
    connect(device, &ISmartDevice::stateChanged, this, &DeviceSyncManager::onDeviceChanged, Qt::UniqueConnection);
}

void DeviceSyncManager::onRoomsChanged()
{
    rebuildConnections();
    emit syncCompleted();
}

void DeviceSyncManager::onRoomDevicesChanged()
{
    rebuildConnections();
    emit syncCompleted();
}

// Triggered when a local device property changes (e.g. from UI or backend action)
void DeviceSyncManager::onDeviceChanged()
{
    auto *device = qobject_cast<ISmartDevice*>(sender());
    if (!device) return;

    // 1. Outbound MQTT Publish
    if (m_mqttService) {
        m_mqttService->publishDeviceState(device->getDeviceId(), device->currentState());
    }

    // 2. Local UI / Listener notification
    if (m_deviceManager) {
        for (Room* room : m_deviceManager->rooms()) {
            if (!room) continue;

            const auto devices = room->getDevices();
            for (const auto &devPtr : devices) {
                if (devPtr.data() == device) {
                    emit deviceStateChanged(room->getRoomName(), device->getDeviceName(), device->currentState());
                    return;
                }
            }
        }
    }
}

// Triggered when MQTT broker receives an inbound message from physical device
void DeviceSyncManager::onMqttDeviceStateReceived(const QString &deviceId, const QJsonObject &state)
{
    ISmartDevice *device = findDeviceById(deviceId);
    if (device) {
        // Ingest state into the device without triggering infinite stateChanged feedback loops
        device->updateState(state);
    } else {
        qWarning() << "[DeviceSyncManager] Received MQTT state for unknown device ID:" << deviceId;
    }
}

// Helper to look up a device across all rooms by ID
ISmartDevice* DeviceSyncManager::findDeviceById(const QString &deviceId) const
{
    if (!m_deviceManager) return nullptr;

    for (Room *room : m_deviceManager->rooms()) {
        if (!room) continue;

        for (const auto &devPtr : room->getDevices()) {
            if (ISmartDevice *device = devPtr.data()) {
                if (device->getDeviceId() == deviceId) {
                    return device;
                }
            }
        }
    }
    return nullptr;
}

// Export the complete room & device tree to JSON
QJsonObject DeviceSyncManager::exportFullState() const
{
    QJsonObject rootJson;
    QJsonArray roomsArray;

    if (!m_deviceManager)
        return rootJson;

    for (Room *room : m_deviceManager->rooms()) {
        if (!room) continue;

        QJsonObject roomJson;
        roomJson["name"] = room->getRoomName();

        QJsonArray devicesArray;
        const auto devices = room->getDevices();
        for (const auto &devPtr : devices) {
            if (ISmartDevice *device = devPtr.data()) {
                QJsonObject devJson;
                devJson["id"] = device->getDeviceId();
                devJson["name"] = device->getDeviceName();
                devJson["type"] = static_cast<int>(device->getDeviceType());
                devJson["state"] = device->currentState();

                devicesArray.append(devJson);
            }
        }

        roomJson["devices"] = devicesArray;
        roomsArray.append(roomJson);
    }

    rootJson["rooms"] = roomsArray;
    return rootJson;
}

// Restore state from JSON payload
bool DeviceSyncManager::importFullState(const QJsonObject &json)
{
    if (!m_deviceManager || !json.contains("rooms"))
        return false;

    QJsonArray roomsArray = json["rooms"].toArray();

    for (const QJsonValue &roomValue : roomsArray) {
        QJsonObject roomObj = roomValue.toObject();
        QString roomName = roomObj["name"].toString();

        if (roomName.isEmpty()) continue;

        m_deviceManager->addRoom(roomName);

        Room* currentRoom = m_deviceManager->rooms().last();
        if (!currentRoom) continue;

        QJsonArray devicesArray = roomObj["devices"].toArray();
        for (const QJsonValue &devValue : devicesArray) {
            QJsonObject devObj = devValue.toObject();
            int type = devObj["type"].toInt();
            QString devName = devObj["name"].toString();

            currentRoom->addDevice(static_cast<DeviceEnums::Type>(type), devName);

            if (devObj.contains("state")) {
                auto lastDevPtr = currentRoom->getDevices().last();
                if (ISmartDevice *dev = lastDevPtr.data()) {
                    dev->updateState(devObj["state"].toObject());
                }
            }
        }
    }

    rebuildConnections();
    emit syncCompleted();
    return true;
}
