import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "devicecards"

Rectangle {
    id: deviceGridBackground
    color: "#e6e9ee"
    signal addDeviceClicked()

    ScrollView {
        id: devicesScrollView
        anchors {
            fill: parent
            margins: 30
        }
        clip: true

        Flow {
            id: devicesFlow
            width: devicesScrollView.availableWidth
            spacing: 16

            readonly property int columns: 4
            readonly property real cardWidth: (width - (columns - 1) * spacing) / columns

            property var devicesModel: SmartDeviceManager.deviceModel

            Repeater {
                id: devices
                model: devicesFlow.devicesModel

                DeviceCard {
                    id:deviceCard
                    width: devicesFlow.cardWidth
                    height: 160
                }
            }
            DragHandler {
                id: handler
                target: devices
            }

            AddNewDevice {
                id: plusIcon
                width: devicesFlow.cardWidth
                height: 160
                onClicked: {
                    addDeviceClicked()
                }
            }
        }
    }
}
