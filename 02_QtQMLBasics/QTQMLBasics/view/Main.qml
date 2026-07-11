import QtQuick
import QTQMLBasics
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component.onCompleted: {
        console.log("Printing to check exposure",DeviceEnums.Fridge)
        console.log("Printing to check exposure of smartDeviceManager ",SmartDeviceManager.getTestString())
        SmartDeviceManager.addRoom("TestRoom")
        var rooms = SmartDeviceManager.rooms
        console.log("Room Name is ",rooms[0].roomName)
        rooms[0].addDevice(DeviceEnums.Light,"My Light");
        var devices = rooms[0].devices
        console.log("Device Property is ", devices[0].deviceName)
    }

    //Add a room to smartDeviceManager
    //Add a device to the room in smartDeviceManager
    // Print some property
}
