#ifndef DEVICESYNCMANAGER_H
#define DEVICESYNCMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <QPointer>
#include <QVector>

class SmartDeviceManager;
class MqttService;
class Room;
class ISmartDevice;

class DeviceSyncManager : public QObject {
    Q_OBJECT

public:
    explicit DeviceSyncManager(SmartDeviceManager *deviceManager = nullptr,
                               MqttService *mqttService = nullptr,
                               QObject *parent = nullptr);

    void setDeviceManager(SmartDeviceManager *deviceManager);
    SmartDeviceManager* deviceManager() const;

    void setMqttService(MqttService *mqttService);
    MqttService* mqttService() const;

    // State Serialization
    QJsonObject exportFullState() const;
    bool importFullState(const QJsonObject &json);

signals:
    void syncCompleted();
    void deviceStateChanged(const QString &roomName, const QString &deviceName, const QJsonObject &state);

public slots:
    void rebuildConnections();

private slots:
    void onRoomsChanged();
    void onRoomDevicesChanged();
    void onDeviceChanged();

    // Inbound handler from MqttService
    void onMqttDeviceStateReceived(const QString &deviceId, const QJsonObject &state);

private:
    void connectDeviceSignals(ISmartDevice *device);
    ISmartDevice* findDeviceById(const QString &deviceId) const;

    SmartDeviceManager *m_deviceManager{nullptr};
    MqttService *m_mqttService{nullptr};
    QVector<QPointer<Room>> m_trackedRooms;
};

#endif // DEVICESYNCMANAGER_H
