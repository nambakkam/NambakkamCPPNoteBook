#include <iostream>
#include <vector>
#include <memory>
#include "IDevice.h"
#include "DeviceFactory.h"
#include "Light.h"
#include "Fan.h"
#include "AirConditioner.h"

void printSeparator(const std::string& label)
{
    std::cout << "\n--- " << label << " ---\n";
}

// Basic creation + on/off/status cycle for every device type via the factory
void testBasicLifecycle()
{
    printSeparator("Basic Lifecycle Test");

    std::vector<std::unique_ptr<IDevice>> devices;
    devices.push_back(DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT));
    devices.push_back(DeviceFactory::createDevice(DeviceFactory::DeviceType::FAN));
    devices.push_back(DeviceFactory::createDevice(DeviceFactory::DeviceType::AIR_CONDITIONER));

    for (const auto& device : devices)
    {
        device->turnOn();
        device->status();
        device->turnOff();
        device->status();
    }
}

// Verifies per-type naming counters increment independently (Light1, Light2... Fan1, Fan2...)
void testNamingCounters()
{
    printSeparator("Naming Counter Test");

    auto light1 = DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT);
    auto light2 = DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT);
    auto fan1   = DeviceFactory::createDevice(DeviceFactory::DeviceType::FAN);
    auto ac1    = DeviceFactory::createDevice(DeviceFactory::DeviceType::AIR_CONDITIONER);
    auto light3 = DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT);

    // Expect: Light1, Light2, Fan1, AC1 (or similar), Light3 — independent per-type counters
    light1->status();
    light2->status();
    fan1->status();
    ac1->status();
    light3->status();
}

// Tests derived-class-specific getters/setters via downcasting
void testDerivedSpecificBehavior()
{
    printSeparator("Derived-Specific Behavior Test");

    auto device = DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT);

    // Downcast to access Light-specific API (safe here since we know the concrete type)
    if (auto* light = dynamic_cast<Light*>(device.get()))
    {
        light->setBrightnessLevel(Light::BrightnessLevel::HIGH);
        light->turnOn();
        light->status();
    }
    else
    {
        std::cout << "Downcast to Light failed unexpectedly.\n";
    }

    auto fanDevice = DeviceFactory::createDevice(DeviceFactory::DeviceType::FAN);
    if (auto* fan = dynamic_cast<Fan*>(fanDevice.get()))
    {
        fan->setFanSpeed(Fan::FanSpeed::Level5);
        fan->turnOn();
        fan->status();
    }
}

// Tests invalid/out-of-range enum handling
void testInvalidDeviceType()
{
    printSeparator("Invalid Device Type Test");

    auto invalid = DeviceFactory::createDevice(static_cast<DeviceFactory::DeviceType>(999));
    if (invalid == nullptr)
    {
        std::cout << "Correctly returned nullptr for invalid device type.\n";
    }
    else
    {
        std::cout << "ERROR: expected nullptr for invalid device type.\n";
    }
}

// Tests that repeated turnOn/turnOff calls behave idempotently (no crash, correct state)
void testRepeatedStateToggling()
{
    printSeparator("Repeated Toggle Test");

    auto device = DeviceFactory::createDevice(DeviceFactory::DeviceType::LIGHT);
    device->turnOn();
    device->turnOn();   // turning on an already-on device should be safe
    device->status();
    device->turnOff();
    device->turnOff();  // turning off an already-off device should be safe
    device->status();
}

// Tests polymorphic destruction through base pointer (no leaks/UB if virtual dtor is correct)
void testPolymorphicDestruction()
{
    printSeparator("Polymorphic Destruction Test");

    {
        std::unique_ptr<IDevice> device = DeviceFactory::createDevice(DeviceFactory::DeviceType::FAN);
        device->turnOn();
    } // device destroyed here — should print Fan's destructor message, not just IDevice's

    std::cout << "Scope exited — destructor should have fired above.\n";
}

int main()
{
    testBasicLifecycle();
    testNamingCounters();
    testDerivedSpecificBehavior();
    testInvalidDeviceType();
    testRepeatedStateToggling();
    testPolymorphicDestruction();
    return 0;
}