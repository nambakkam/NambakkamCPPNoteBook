#ifndef ISMARTDEVICE_H
#define ISMARTDEVICE_H

#include <QObject>
#include "deviceenums.h"
class ISmartDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString getDeviceName READ getDeviceName CONSTANT)
    Q_PROPERTY(DeviceEnums::Type deviceType READ getDeviceType CONSTANT)
    Q_PROPERTY(DeviceEnums::DeviceStates deviceState READ getDeviceState NOTIFY deviceStateChanged)
public:
    explicit ISmartDevice(QString deviceNameVal = "",DeviceEnums::Type deviceTypeVal = DeviceEnums::Unknown,DeviceEnums::DeviceStates stateVal = DeviceEnums::Off,QObject *parent = nullptr);
    virtual ~ISmartDevice() = default;

    QString getDeviceName() const;
    DeviceEnums::Type getDeviceType() const;
    DeviceEnums::DeviceStates getDeviceState() const;
    Q_INVOKABLE  virtual void togglePower() = 0;

signals:
    void deviceStateChanged(DeviceEnums::DeviceStates state);
protected:
    DeviceEnums::DeviceStates m_deviceState;
private:
    QString m_deviceName;
    DeviceEnums::Type m_deviceType;

};

#endif // ISMARTDEVICE_H
