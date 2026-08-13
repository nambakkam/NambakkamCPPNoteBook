#ifndef DEVICEIDGENERATOR_H
#define DEVICEIDGENERATOR_H

#include <QString>
#include <QMap>
#include <QMutex>
#include <QUuid>
#include "deviceenums.h"

class DeviceIdGenerator {
public:
    // Generates sequential IDs: "light_01", "light_02", "ac_01", "ac_02"
    static QString generateSequentialId(DeviceEnums::Type type);

    // Generates random UUID-based unique IDs: "light_a1b2c3d4", "ac_8f9e0a1b"
    static QString generateUniqueId(DeviceEnums::Type type);

    // Helper: Converts enum to prefix string ("Light" -> "light", "AirConditioner" -> "ac")
    static QString typeToPrefix(DeviceEnums::Type type);

    // Helper: Reverse lookup DeviceType from an ID string (e.g., "light_01" -> DeviceType::Light)
    static DeviceEnums::Type typeFromId(const QString &id);

private:
    static QMap<DeviceEnums::Type, int> s_counters;
    static QMutex s_mutex;
};

#endif // DEVICEIDGENERATOR_H
