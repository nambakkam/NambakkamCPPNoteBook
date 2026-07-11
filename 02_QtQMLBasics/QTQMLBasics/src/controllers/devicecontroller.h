#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include "room.h"
#include "devicelistmodel.h"

class DeviceController : public QObject
{
    Q_OBJECT
    QML_ELEMENT // Makes the controller available to QML

    Q_PROPERTY(DeviceListModel* deviceModel READ deviceModel CONSTANT)
    Q_PROPERTY(Room* currentRoom READ currentRoom WRITE setCurrentRoom NOTIFY currentRoomChanged)

public:
    explicit DeviceController(QObject *parent = nullptr);

    DeviceListModel* deviceModel() const;
    Room* currentRoom() const;
    void setCurrentRoom(Room* room);

    // Methods exposed to QML to modify devices through the model/room layer
    Q_INVOKABLE void addDeviceToCurrentRoom(int type, const QString& name);
    Q_INVOKABLE void removeDeviceFromCurrentRoom(int index);

signals:
    void currentRoomChanged();

private slots:
    // Syncs the model whenever the active room updates its internal device list
    void refreshModelData();

private:
    DeviceListModel* m_deviceModel;
    Room* m_currentRoom = nullptr;
};

#endif // DEVICECONTROLLER_H
