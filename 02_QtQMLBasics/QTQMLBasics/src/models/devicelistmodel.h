#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "ismartdevice.h" // Assuming this header defines ISmartDevice and DeviceEnums

class DeviceListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DeviceRoles {
        DeviceNameRole = Qt::UserRole + 1,
        DeviceTypeRole,
        DeviceObjectRole // Exposes the actual QObject pointer to QML
    };

    explicit DeviceListModel(QObject *parent = nullptr);

    // Core model methods
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Method to populate or update the model's data from your Room
    void setDevices(const QVector<ISmartDevice*>& devices);

private:
    QVector<ISmartDevice*> m_devices;
};

#endif // DEVICELISTMODEL_H
