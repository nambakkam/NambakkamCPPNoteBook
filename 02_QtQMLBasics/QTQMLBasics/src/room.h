#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <qqmllist.h>
#include <QList>
#include "ismartdevice.h"
#include "deviceenums.h"

class Room : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ISmartDevice> devices READ getDevices NOTIFY devicesChanged)
    Q_PROPERTY(QString roomName READ getRoomName CONSTANT)
public:
    explicit Room(const QString &roomNameVal = "Unknown",QObject *parent = nullptr);
    ~Room(); // Added destructor to clean up devices

    Q_INVOKABLE void addDevice(DeviceEnums::Type deviceType, const QString& deviceName);
    Q_INVOKABLE void removeDevice(int index);

    QQmlListProperty<ISmartDevice> getDevices();
    QString getRoomName() const;

signals:
    void devicesChanged();

private:
    QString m_RoomName;
    QList<ISmartDevice*> m_devices;
};

#endif // ROOM_H
