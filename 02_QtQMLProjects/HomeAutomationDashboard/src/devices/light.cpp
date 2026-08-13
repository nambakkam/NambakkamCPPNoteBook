#include "light.h"
#include "deviceenums.h"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()

Light::Light(const QString &deviceId,const QString &deviceNameVal,QObject *parent) : ISmartDevice(deviceId,deviceNameVal,DeviceEnums::Light,false,parent),m_brightnessLevel(50)
{

}

void Light::setBrightness(int level)
{
    if(m_brightnessLevel != level){
        m_brightnessLevel = level;
        emit brightnessChanged(m_brightnessLevel);
    }
}

int Light::brightness() const
{
    return m_brightnessLevel;
}

void Light::updateState(const QJsonObject &state)
{
    if (state.contains("powerState")) {
        setPowerState(state["powerState"].toBool());
    }
    if (state.contains("brightness")) {
        setBrightness(state["brightness"].toInt());
    }
}

QJsonObject Light::currentState() const
{
    QJsonObject state;
    state["deviceId"] = getDeviceId();
    state["deviceName"] = getDeviceName();
    state["deviceType"] = static_cast<int>(getDeviceType());
    state["powerState"] = getPowerState();
    state["brightness"] = brightness();
    return state;
}
