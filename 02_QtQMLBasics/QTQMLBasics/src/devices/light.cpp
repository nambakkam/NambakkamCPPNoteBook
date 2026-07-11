#include "light.h"
#include "deviceenums.h"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()

Light::Light(QString deviceNameVal,QObject *parent) : ISmartDevice(deviceNameVal,DeviceEnums::Light,DeviceEnums::Off,parent),m_brightnessLevel(50)
{

}

void Light::setBrightness(int level)
{
    if(m_brightnessLevel != level){
        m_brightnessLevel = level;
        emit brightnessChanged(m_brightnessLevel);
    }
}

int Light::getBrightness()
{
    return m_brightnessLevel;
}
