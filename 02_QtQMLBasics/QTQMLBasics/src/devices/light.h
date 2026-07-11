#ifndef LIGHT_H
#define LIGHT_H

#include "ismartdevice.h"
class Light : public ISmartDevice
{

    Q_OBJECT
    Q_PROPERTY(int brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)
public:
    explicit Light(QString deviceNameVal = "Unnamed Light",QObject *parent = nullptr);
    ~Light() override = default;
    void setBrightness(int level);
    int getBrightness();

private:
    int m_brightnessLevel;


signals:
    void brightnessChanged(int level);
};

#endif // LIGHT_H
