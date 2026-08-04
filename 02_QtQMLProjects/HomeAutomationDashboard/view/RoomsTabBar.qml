import QtQuick
import QtQuick.Controls
import HomeAutomationDashboard 1.0

Flickable {
    id: roomTabsContainer
    implicitHeight: 40
    clip: true
    boundsBehavior: Flickable.StopAtBounds
    flickableDirection: Flickable.HorizontalFlick
    contentWidth: roomTabs.width
    contentHeight: height

    // Forward properties so main.qml can read checkRoomTabBar.currentIndex and checkRoomTabBar.count
    property alias currentIndex: roomTabs.currentIndex
    property alias count: buttonsRepeater.count

    TabBar {
        id: roomTabs
        height: parent.height

        // Show max 4 tabs in view. If fewer than 4, divide width evenly across existing tabs.
        readonly property real tabWidth: roomTabsContainer.width / Math.min(4, Math.max(1, buttonsRepeater.count))
        width: tabWidth * (buttonsRepeater.count || 1)

        property var roomsModel: SmartDeviceManager.roomsModel

        // Automatically scroll the active tab into view when selected
        onCurrentIndexChanged: {
            if (currentIndex >= 0 && currentIndex < buttonsRepeater.count) {
                let tabLeft = currentIndex * tabWidth
                let tabRight = tabLeft + tabWidth

                if (tabLeft < roomTabsContainer.contentX) {
                    roomTabsContainer.contentX = tabLeft
                } else if (tabRight > roomTabsContainer.contentX + roomTabsContainer.width) {
                    roomTabsContainer.contentX = tabRight - roomTabsContainer.width
                }
            }
        }

        Repeater {
            id: buttonsRepeater
            model: roomTabs.roomsModel

            TabButton {
                id: roomTab
                width: roomTabs.tabWidth
                height: roomTabs.height
                text: model.roomName !== undefined ? model.roomName : modelData
                font {
                    pixelSize: 16
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
                    leftPadding: 6
                    rightPadding: 6
                }

                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: "#f2f3f5"

                    Rectangle {
                        height: parent.height * 0.08
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
}
