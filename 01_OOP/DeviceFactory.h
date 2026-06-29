#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#pragma once

#include <memory>

class IDevice;

class DeviceFactory
{
public:
    enum class DeviceType
    {
        LIGHT,
        FAN,
        AirConditioner
    };
    static std::unique_ptr<IDevice> createDevice(DeviceFactory::DeviceType type);
    static DeviceFactory& getInstance();

private:
    DeviceFactory() = default;
    ~DeviceFactory() = default;
    //Deleting copy constructor and assignment operator to prevent copying of the singleton instance
    DeviceFactory(const DeviceFactory&) = delete;
    DeviceFactory& operator=(const DeviceFactory&) = delete;
    //Deleting move constructor and move assignment operator to prevent moving of the singleton instance
    // This is a common practice to ensure that the singleton instance cannot be copied or moved, which could lead to multiple instances of the class being created.
    DeviceFactory (DeviceFactory&&) = delete;
    DeviceFactory& operator=(DeviceFactory&&) = delete;
    inline static int referenceCount = 0; // Reference count to keep track of the number of instances

};

#endif