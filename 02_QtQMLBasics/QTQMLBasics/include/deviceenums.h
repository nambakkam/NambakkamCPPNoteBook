#ifndef DEVICEENUMS_H
#define DEVICEENUMS_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace DeviceEnums {
    Q_NAMESPACE
    QML_ELEMENT

    enum Type {
        Light,
        AirConditioner,
        Fridge,
        WashingMachine,
        Television,
        SmartPlug,
        SecurityCamera,
        Unknown
    };
    Q_ENUM_NS(Type)

    enum DeviceStates {
        Off,
        On,
        Error,
        Undefined
    };
    Q_ENUM_NS(DeviceStates)

    enum FanSpeed {
        Low,
        Medium,
        High,
        Auto,
        Turbo,
        Nature
    };
    Q_ENUM_NS(FanSpeed)

    enum WashCycle {
        Cotton,
        Synthetics,
        Delicates,
        QuickWash,
        Eco,
        Wool,
        HeavyDuty,
        RinseAndSpin
    };
    Q_ENUM_NS(WashCycle)

    enum InputSource {
        TV,
        HDMI1,
        HDMI2,
        HDMI3,
        AV
    };
    Q_ENUM_NS(InputSource)
}

#endif // DEVICEENUMS_H
