#ifndef SMARTDEVICEMANAGER_H
#define SMARTDEVICEMANAGER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QPointer>
#include <QVector>

#include "room.h"
#include "roomsmodel.h"
#include "devicelistmodel.h"
#include "thememanager.h"

class SmartDeviceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(RoomsModel* roomsModel READ roomsModel CONSTANT)
    Q_PROPERTY(DeviceListModel* deviceModel READ deviceModel CONSTANT)
    Q_PROPERTY(ThemeManager* themeManager READ themeManager CONSTANT)
    Q_PROPERTY(int currentRoomIndex READ currentRoomIndex NOTIFY currentRoomIndexChanged)
    Q_PROPERTY(QVariantList deviceTypeModel READ deviceTypeModel CONSTANT)

public:
    explicit SmartDeviceManager(QObject *parent = nullptr);

    RoomsModel* roomsModel() const;
    DeviceListModel* deviceModel() const;
    ThemeManager* themeManager() const;

    // Dynamic index getter
    int currentRoomIndex() const;

    Q_INVOKABLE void addRoom(const QString &roomName);
    Q_INVOKABLE void removeRoom(int index);
    Q_INVOKABLE void addDeviceToCurrentRoom(int type, const QString& deviceName);
    Q_INVOKABLE void removeDeviceFromCurrentRoom(int index);
    Q_INVOKABLE void setCurrentRoomIndex(int index);
    QVariantList deviceTypeModel() const;

signals:
    void roomsChanged();
    void currentRoomIndexChanged(int newIndex);

private slots:
    void refreshDeviceModelData();

private:
    void setCurrentRoom(QPointer<Room> room);

    QVector<QPointer<Room>> m_rooms;
    QPointer<Room> m_currentRoom; // <-- ONLY state variable you need!

    RoomsModel* m_roomsModel;
    DeviceListModel* m_deviceModel;
    ThemeManager* m_themeManager;
};

#endif // SMARTDEVICEMANAGER_H
