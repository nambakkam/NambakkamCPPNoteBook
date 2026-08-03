import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: addDeviceButton

    // Matching standard DeviceCard dimensions
    implicitWidth: 170
    implicitHeight: 180

    // Path to your plus icon asset
    property url iconSource: "../Assets/addDevice.svg"

    contentItem: ColumnLayout {
        spacing: 10
        // alignment: Qt.AlignCenter

        // Icon Circle Wrapper
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: 48
            implicitHeight: 48
            radius: 24

            // Subtle fill transition
            color: addDeviceButton.down
                ? "#d8dadf"
                : (addDeviceButton.hovered ? "#eaebed" : "#f2f3f5")

            Image {
                anchors.centerIn: parent
                source: addDeviceButton.iconSource
                sourceSize: Qt.size(24, 24)
                fillMode: Image.PreserveAspectFit
            }

            Behavior on color {
                ColorAnimation { duration: 120 }
            }
        }

        // Label
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "Add Device"
            font.pixelSize: 13
            font.bold: true
            color: addDeviceButton.down
                ? "#3b638b"
                : (addDeviceButton.hovered ? "#5688b9" : "#818a97")

            Behavior on color {
                ColorAnimation { duration: 120 }
            }
        }
    }

    // Outer Card Frame
    background: Rectangle {
        radius: 12
        color: addDeviceButton.down
            ? "#f2f3f5"
            : (addDeviceButton.hovered ? "#fafafa" : "#ffffff")

        border.color: addDeviceButton.hovered || addDeviceButton.down ? "#5688b9" : "#d8dadf"
        border.width: addDeviceButton.hovered ? 2 : 1

        Behavior on color {
            ColorAnimation { duration: 120 }
        }
        Behavior on border.color {
            ColorAnimation { duration: 120 }
        }
    }
}
