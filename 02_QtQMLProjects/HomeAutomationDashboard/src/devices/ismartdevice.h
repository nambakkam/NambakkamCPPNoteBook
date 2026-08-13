#ifndef ISMARTDEVICE_H
#define ISMARTDEVICE_H

#include <QObject>
#include <QJsonObject>
#include "deviceenums.h"
class ISmartDevice : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ISmartDevice)

    Q_PROPERTY(QString deviceName READ getDeviceName CONSTANT)
    Q_PROPERTY(QString deviceId READ getDeviceId CONSTANT)
    Q_PROPERTY(DeviceEnums::Type deviceType READ getDeviceType CONSTANT)
    Q_PROPERTY(bool powerState READ getPowerState WRITE setPowerState NOTIFY powerStateChanged)
public:
    virtual ~ISmartDevice() = default;
    explicit ISmartDevice(const QString& deviceId = "Unknown",const QString& deviceNameVal = "",DeviceEnums::Type deviceTypeVal = DeviceEnums::Unknown,bool stateVal = false,QObject *parent = nullptr);
    QString getDeviceName() const;
    DeviceEnums::Type getDeviceType() const;
    bool getPowerState() const;
    Q_INVOKABLE void setPowerState(bool state);
    QString getDeviceId() const;

    virtual void updateState(const QJsonObject &state) = 0;
    virtual QJsonObject currentState() const = 0;

signals:
    void powerStateChanged(bool state);
    void stateChanged();
protected:
    bool m_powerState;


private:
    QString m_deviceId;
    QString m_deviceName;
    DeviceEnums::Type m_deviceType;

    void autoConnectStateSignals();


};

#endif // ISMARTDEVICE_H
