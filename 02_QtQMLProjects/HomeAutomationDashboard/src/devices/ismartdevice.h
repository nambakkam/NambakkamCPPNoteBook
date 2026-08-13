#ifndef ISMARTDEVICE_H
#define ISMARTDEVICE_H

#include <QObject>
#include "deviceenums.h"
class ISmartDevice : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ISmartDevice)

    Q_PROPERTY(QString deviceName READ getDeviceName CONSTANT)
    Q_PROPERTY(DeviceEnums::Type deviceType READ getDeviceType CONSTANT)
    Q_PROPERTY(bool powerState READ getPowerState WRITE setPowerState NOTIFY powerStateChanged)
public:
    virtual ~ISmartDevice() = default;
    explicit ISmartDevice(const QString& deviceNameVal = "",DeviceEnums::Type deviceTypeVal = DeviceEnums::Unknown,bool stateVal = false,QObject *parent = nullptr);
    QString getDeviceName() const;
    DeviceEnums::Type getDeviceType() const;
    bool getPowerState() const;
    void setPowerState(bool state);

signals:
    void powerStateChanged(bool state);
protected:
    bool m_powerState;


private:
    QString m_deviceName;
    DeviceEnums::Type m_deviceType;

};

#endif // ISMARTDEVICE_H
