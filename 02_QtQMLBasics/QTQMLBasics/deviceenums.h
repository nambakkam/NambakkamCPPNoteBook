#ifndef DEVICEENUMS_H
#define DEVICEENUMS_H

#include <QObject>

namespace DeviceEnums {
    Q_NAMESPACE

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

    enum Status {
        Off,
        On,
        Standby,
        Error,
        Undefined
    };
    Q_ENUM_NS(Status) // Registers the Status enum under this namespace
}
#endif // DEVICEENUMS_H
