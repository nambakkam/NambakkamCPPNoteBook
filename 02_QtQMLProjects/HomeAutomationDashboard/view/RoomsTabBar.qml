import QtQuick
import QtQuick.Controls
import HomeAutomationDashboard 1.0

TabBar {
    id: roomTabs
    property var roomsModel: SmartDeviceManager.roomsModel

    Repeater {
        id: buttonsRepeater
        model: roomTabs.roomsModel

        TabButton {
            id: roomTab
            implicitWidth: Math.max(100, roomTabs.width / (buttonsRepeater.count || 1))
            implicitHeight: roomTabs.height
            text: model.roomName !== undefined ? model.roomName : modelData
            font{
                pixelSize: 20
                weight: Font.Medium
                styleName: "Roboto"
            }

            contentItem: Text {
                text: roomTab.text
                font: roomTab.font
                color: roomTab.checked ? "#5688b9" : "#1c1d20"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                color: "#f2f3f5"

                Rectangle {
                    height: parent.height * 0.05
                    width: parent.width
                    visible: roomTab.checked
                    color: "#5688b9"
                    anchors {
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }
}
