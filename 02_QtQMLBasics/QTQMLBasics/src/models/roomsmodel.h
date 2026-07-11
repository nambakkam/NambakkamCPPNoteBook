#ifndef ROOMSMODEL_H
#define ROOMSMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "room.h" // Adjust path based on location

class RoomsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum RoomRoles {
        RoomNameRole = Qt::UserRole + 1,
        RoomObjectRole
    };

    explicit RoomsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void updateRooms(const QVector<Room*>& rooms);

private:
    QVector<Room*> m_rooms;
};

#endif // ROOMSMODEL_H
