#ifndef LIGHT_H
#define LIGHT_H
#pragma once
#include "IDevice.h"
class Light : public IDevice
{
public:
    enum class BrightnessLevel
    {
        LOW,
        MEDIUM,
        HIGH
    };
    Light(const std::string& deviceName = "Unnamed Light", PowerState powerState = PowerState::OFF, BrightnessLevel brightnessLevel = BrightnessLevel::MEDIUM);
    /**
     * @brief Default virtual destructor.
     *
     * The class is not intended to be further derived, so the default
     * destructor is sufficient. Marking it virtual is a good practice to
     * ensure correct cleanup if the class is ever used polymorphically.
     */
    virtual ~Light();

    virtual void turnOn() override;
    virtual void turnOff() override;
    virtual void status() override;
    Light::BrightnessLevel getBrightnessLevel();
    void setBrightnessLevel(Light::BrightnessLevel value);

protected:
    Light::BrightnessLevel m_brightnessLevel; 


};


#endif