#ifndef SMARTDEVICEMANAGER_H
#define SMARTDEVICEMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QtQml/qqmlregistration.h>
#include <QPointer>

#include "room.h"
#include "roomsmodel.h"
#include "devicelistmodel.h"

class SmartDeviceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    // Models exposed directly through the manager
    Q_PROPERTY(RoomsModel* roomsModel READ roomsModel CONSTANT)
    Q_PROPERTY(DeviceListModel* deviceModel READ deviceModel CONSTANT)

    // The currently active room in the UI
    Q_PROPERTY(Room* currentRoom READ currentRoom WRITE setCurrentRoom NOTIFY currentRoomChanged)

public:
    explicit SmartDeviceManager(QObject *parent = nullptr);

    RoomsModel* roomsModel() const;
    DeviceListModel* deviceModel() const;
    Room* currentRoom() const;
    void setCurrentRoom(Room* room);

    // Single unified interface for UI actions
    Q_INVOKABLE void addRoom(const QString &roomName);
    Q_INVOKABLE void removeRoom(int index);
    Q_INVOKABLE void addDeviceToCurrentRoom(int type, const QString& deviceName);
    Q_INVOKABLE void removeDeviceFromCurrentRoom(int index);

signals:
    void roomsChanged();
    void currentRoomChanged();

private slots:
    void refreshDeviceModelData();

private:
    QVector<QPointer<Room>> m_rooms;
    QPointer<Room> m_currentRoom = nullptr;

    // The models are now managed internally
    RoomsModel* m_roomsModel;
    DeviceListModel* m_deviceModel;
};

#endif // SMARTDEVICEMANAGER_H
