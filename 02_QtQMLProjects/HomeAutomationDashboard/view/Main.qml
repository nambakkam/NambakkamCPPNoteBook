import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HomeAutomationDashboard 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 480
    title: "Smart Home Manager - Full Device Suite Test"

    RoomsTabBar {
        id: checkRoomTabBar
        width: parent.width - roomTabActions.width
        height: 40
        currentIndex: SmartDeviceManager.currentRoomIndex
        anchors {
            top: parent.top
            left: parent.left
        }
        onCurrentIndexChanged: {
            // console.log("Current Index is ", checkRoomTabBar.currentIndex)
            if(currentIndex >= 0){
                SmartDeviceManager.setCurrentRoomIndex(checkRoomTabBar.currentIndex)
            }
        }
    }
    RoomTabActions{
        id:roomTabActions
        width: 80
        height: 40
        anchors{
            top: parent.top
            right: parent.right
        }
        onAddRoomClicked: {
            addRoomDialog.open()

        }
        onSettingsClicked: {

        }
    }

    DevicesGrid{
        id:deviceGridLayout
        width: parent.width
        height: parent.height-checkRoomTabBar.height
        visible: SmartDeviceManager.currentRoomIndex !== -1
        anchors{
            top:checkRoomTabBar.bottom
            horizontalCenter: parent.horizontalCenter
        }
        onAddDeviceClicked:{
            addDeviceDialog.open()
        }
    }
    Text {
            anchors.centerIn: deviceGridLayout
            visible: checkRoomTabBar.count === 0
            text: "Click on '+' icon to add a room"
            font {
                pixelSize: 16
                weight: Font.Medium
                styleName: "Roboto"
            }
            color: "#818a97"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
    }

    AddRoomDialog {
        id: addRoomDialog
        width: root.width*0.4
        height: root.height*0.8
        // 3. On valid input, pass name directly to C++ backend
        onRoomAdded: function(roomName) {
            SmartDeviceManager.addRoom(roomName)
            checkRoomTabBar.currentIndex = checkRoomTabBar.count -1
        }
    }

    AddDeviceDialog{
        id:addDeviceDialog
        width: root.width*0.4
        height: root.height*0.8
        onDeviceAdded: function(deviceType,deviceName) {
            SmartDeviceManager.addDeviceToCurrentRoom(deviceType,deviceName)
        }
    }

}
