#include<iostream>
#include "IDevice.h"
#include "DeviceFactory.h"
#include <vector>
using namespace std;

void testDeviceFactory() {
    std::vector<std::unique_ptr<IDevice>> devices;
    DeviceFactory& factory = DeviceFactory::getInstance();
    devices.push_back(factory.createDevice(DeviceFactory::DeviceType::LIGHT));
    devices.push_back(factory.createDevice(DeviceFactory::DeviceType::FAN));

    for (const auto& device : devices) {
        device->turnOn();
        device->status();
        device->turnOff();
        device->status();
    }
}

int main() {
    testDeviceFactory();
    return 0;
}