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
    Q_ENUM_NS(Type) // Registers the Type enum under this namespace

    enum DeviceStates {
        Off,
        On,
        Error,
        Undefined
    };
    Q_ENUM_NS(DeviceStates) // Registers the Status enum under this namespace

    enum FanSpeed {
        Low,
        Medium,
        High,
        Auto,
        Turbo,  // New addition
        Nature  // New addition
    };

}
#endif // DEVICEENUMS_H
