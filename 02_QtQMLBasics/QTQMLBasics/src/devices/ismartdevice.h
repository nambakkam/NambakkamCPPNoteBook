#ifndef ISMARTDEVICE_H
#define ISMARTDEVICE_H

#include <QObject>
#include "deviceenums.h"
class ISmartDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString deviceName READ getDeviceName CONSTANT)
    Q_PROPERTY(DeviceEnums::Type deviceType READ getDeviceType CONSTANT)
    Q_PROPERTY(DeviceEnums::DeviceStates deviceState READ getDeviceState NOTIFY deviceStateChanged)
public:
    virtual ~ISmartDevice() = default;

    QString getDeviceName() const;
    DeviceEnums::Type getDeviceType() const;
    DeviceEnums::DeviceStates getDeviceState() const;
    Q_INVOKABLE  virtual void togglePower();

signals:
    void deviceStateChanged(DeviceEnums::DeviceStates state);
protected:
    DeviceEnums::DeviceStates m_deviceState;
    //Made constructor protected to make ISmartDevice an abstract class
    explicit ISmartDevice(QString deviceNameVal = "",DeviceEnums::Type deviceTypeVal = DeviceEnums::Unknown,DeviceEnums::DeviceStates stateVal = DeviceEnums::Off,QObject *parent = nullptr);
private:
    QString m_deviceName;
    DeviceEnums::Type m_deviceType;

};

#endif // ISMARTDEVICE_H
