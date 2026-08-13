#include "deviceidgenerator.h"

// Static member definitions
QMap<DeviceEnums::Type, int> DeviceIdGenerator::s_counters;
QMutex DeviceIdGenerator::s_mutex;

QString DeviceIdGenerator::typeToPrefix(DeviceEnums::Type type) {
    switch (type) {
        case DeviceEnums::Light:          return "light";
        case DeviceEnums::AirConditioner: return "ac";
        case DeviceEnums::Fridge:         return "fridge";
        case DeviceEnums::WashingMachine: return "washer";
        case DeviceEnums::Television:     return "tv";
        case DeviceEnums::SmartPlug:      return "plug";
        case DeviceEnums::SecurityCamera: return "cam";
        case DeviceEnums::Unknown:
        default:                         return "dev";
    }
}

QString DeviceIdGenerator::generateSequentialId(DeviceEnums::Type type) {
    QMutexLocker locker(&s_mutex);
    
    // Increment counter for specific device type
    int count = ++s_counters[type];
    
    // Generates formatted string e.g., "light_01", "light_02"
    return QString("%1_%2")
            .arg(typeToPrefix(type))
            .arg(count, 2, 10, QChar('0'));
}

QString DeviceIdGenerator::generateUniqueId(DeviceEnums::Type type) {
    // Takes the first 8 hex characters of a new UUID
    QString shortUuid = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);
    
    // Generates e.g., "light_a1b2c3d4"
    return QString("%1_%2")
            .arg(typeToPrefix(type))
            .arg(shortUuid);
}

DeviceEnums::Type DeviceIdGenerator::typeFromId(const QString &id) {
    QString prefix = id.split('_').first().toLower();

    if (prefix == "light")  return DeviceEnums::Light;
    if (prefix == "ac")     return DeviceEnums::AirConditioner;
    if (prefix == "fridge") return DeviceEnums::Fridge;
    if (prefix == "washer") return DeviceEnums::WashingMachine;
    if (prefix == "tv")     return DeviceEnums::Television;
    if (prefix == "plug")   return DeviceEnums::SmartPlug;
    if (prefix == "cam")    return DeviceEnums::SecurityCamera;

    return DeviceEnums::Unknown;
}
