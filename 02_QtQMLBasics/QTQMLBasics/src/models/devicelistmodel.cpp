#include "devicelistmodel.h"

DeviceListModel::DeviceListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DeviceListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_devices.size();
}

QVariant DeviceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_devices.size())
        return QVariant();

    ISmartDevice* device = m_devices.at(index.row());
    if (!device)
        return QVariant();

    switch (role) {
    case DeviceNameRole:
        // Assumes your ISmartDevice interface provides a name property or method
        return device->getDeviceName();
    case DeviceTypeRole:
        // Assumes your ISmartDevice interface provides its DeviceEnums::Type
        return device->getDeviceType();
    case DeviceObjectRole:
        // QVariant automatically wraps QObject* pointers for QML engine
        return QVariant::fromValue(device);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DeviceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DeviceNameRole] = "deviceName";
    roles[DeviceTypeRole] = "deviceType";
    roles[DeviceObjectRole] = "deviceObject";
    return roles;
}

void DeviceListModel::setDevices(const QVector<ISmartDevice*>& devices)
{
    beginResetModel();
    m_devices = devices;
    endResetModel();
}
