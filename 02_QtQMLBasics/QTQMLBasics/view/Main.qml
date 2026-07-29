import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QTQMLBasics 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 950
    height: 700
    title: "Smart Home Manager - Full Device Suite Test"

    // Seed test data when application loads
    Component.onCompleted: {
        SmartDeviceManager.addRoom("Living Room")
        SmartDeviceManager.addRoom("Kitchen")
        SmartDeviceManager.addRoom("Laundry Room")


            // Add initial test devices (using Enum values)
        SmartDeviceManager.setCurrentRoomIndex(0)

        SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Light, "Main Ceiling Light")
        SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.AirConditioner, "Living Room AC")
        SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Television, "Smart OLED TV")

        SmartDeviceManager.setCurrentRoomIndex(1)
        SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Light, "Kitchen Light")

        SmartDeviceManager.setCurrentRoomIndex(2)
        SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Light, "Laundry Light")

    }

    RoomsTabBar {
        id: checkRoomTabBar
        height: 40
        currentIndex: SmartDeviceManager.currentRoomIndex
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        onCurrentIndexChanged: {
            SmartDeviceManager.setCurrentRoomIndex(checkRoomTabBar.currentIndex)
        }
    }
    DevicesGrid{
        id:deviceGridLayout
        width: parent.width
        height: parent.height-checkRoomTabBar.height
        anchors{
            top:checkRoomTabBar.bottom
            horizontalCenter: checkRoomTabBar.horizontalCenter
        }
    }
}
