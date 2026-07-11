#include "smartdevicemanager.h"

SmartDeviceManager::SmartDeviceManager(QObject *parent)
    : QObject{parent}
{}

SmartDeviceManager::~SmartDeviceManager()
{
    qDeleteAll(m_rooms);
    m_rooms.clear();

}

void SmartDeviceManager::addRoom(const QString& roomName)
{
    Room *newRoom = new Room(roomName,this);
    if(newRoom){
        m_rooms.append(newRoom);
        emit roomsChanged();
    }
}

void SmartDeviceManager::removeRoom(int index)
{
    if (index >= 0 && index < m_rooms.size()) {
        Room* room = m_rooms.takeAt(index);
        room->deleteLater(); // Safely delete the QObject
        emit roomsChanged();
    }
}

QString SmartDeviceManager::getTestString()
{
    return "TestString";
}

QQmlListProperty<Room> SmartDeviceManager::getRooms()
{
    return QQmlListProperty<Room>(this,&m_rooms);
}
