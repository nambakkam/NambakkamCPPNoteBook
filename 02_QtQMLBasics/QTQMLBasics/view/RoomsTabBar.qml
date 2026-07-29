import QtQuick
import QtQuick.Controls
import QTQMLBasics 1.0

TabBar {
    id: roomTabs
    property var roomsModel:SmartDeviceManager.roomsModel
    Repeater {
            id: buttonsRepeater
            model: roomTabs.roomsModel

            TabButton {
                implicitWidth: Math.max(100, roomTabs.width / (buttonsRepeater.count || 1))
                implicitHeight: roomTabs.height
                text: model.roomName !== undefined ? model.roomName : modelData
            }
        }
}
