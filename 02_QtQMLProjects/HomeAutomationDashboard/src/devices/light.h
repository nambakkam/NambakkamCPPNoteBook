#ifndef LIGHT_H
#define LIGHT_H

#include "ismartdevice.h"
class Light : public ISmartDevice
{

    Q_OBJECT
    Q_PROPERTY(int brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
public:
    explicit Light(const QString &deviceId,const QString& deviceNameVal = "Unnamed Light",QObject *parent = nullptr);
    ~Light() override = default;
    int brightness() const;
    void updateState(const QJsonObject &state) override;
    QJsonObject currentState() const override;
public slots:
    void setBrightness(int level);
private:
    int m_brightnessLevel;


signals:
    void brightnessChanged(int level);
};

#endif // LIGHT_H
