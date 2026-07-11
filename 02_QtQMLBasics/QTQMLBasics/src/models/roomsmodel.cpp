#include "roomsmodel.h"

RoomsModel::RoomsModel(QObject *parent) : QAbstractListModel(parent) {}

int RoomsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_rooms.size();
}

QVariant RoomsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_rooms.size())
        return QVariant();

    Room* room = m_rooms.at(index.row());
    if (!room) return QVariant();

    switch (role) {
    case RoomNameRole:
        return room->getRoomName();
    case RoomObjectRole:
        return QVariant::fromValue(room);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> RoomsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoomNameRole] = "roomName";
    roles[RoomObjectRole] = "roomObject";
    return roles;
}

void RoomsModel::updateRooms(const QVector<Room*>& rooms)
{
    beginResetModel();
    m_rooms = rooms;
    endResetModel();
}
