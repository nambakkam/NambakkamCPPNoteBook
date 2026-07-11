#ifndef SMARTDEVICEMANAGER_H
#define SMARTDEVICEMANAGER_H

#include <QObject>
#include <room.h>
#include <qqmllist.h>
#include <QtQml/qqmlregistration.h>
class SmartDeviceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QQmlListProperty<Room> rooms READ getRooms NOTIFY roomsChanged)
public:
    explicit SmartDeviceManager(QObject *parent = nullptr);
    ~SmartDeviceManager();
    Q_INVOKABLE void addRoom(const QString &roomName);
    Q_INVOKABLE void removeRoom(int index);
    Q_INVOKABLE QString getTestString();
    QQmlListProperty<Room> getRooms();
private:
    QList<Room*> m_rooms;
signals:
    void roomsChanged();
};

#endif // SMARTDEVICEMANAGER_H
