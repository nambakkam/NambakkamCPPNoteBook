#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <qqmllist.h>
#include <QVector>
#include <QPointer>
#include "ismartdevice.h"
#include "deviceenums.h"

class Room : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomName READ getRoomName CONSTANT)
public:
    explicit Room(const QString &roomNameVal = "Unknown",QObject *parent = nullptr);

    Q_INVOKABLE void addDevice(DeviceEnums::Type deviceType, const QString& deviceName);
    Q_INVOKABLE void removeDevice(int index);

    QVector<QPointer<ISmartDevice>> getDevices() const;
    QString getRoomName() const;

signals:
    void devicesChanged();

private:
    QString m_RoomName;
    QVector<ISmartDevice*> m_devices;
};

#endif // ROOM_H
