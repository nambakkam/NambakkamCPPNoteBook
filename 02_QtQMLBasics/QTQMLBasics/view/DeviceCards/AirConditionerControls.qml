import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 6

    Label {
        text: "Target Temp"
        font.pixelSize: 11
        font.bold: true
        color: "#818a97"
    }

    RowLayout {
        Layout.fillWidth: true
        spacing: 6

        Button {
            text: "-"
            implicitWidth: 28
            implicitHeight: 28
            contentItem: Text {
                text: parent.text
                color: "#1c1d20"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                radius: 6
                color: parent.down ? "#d8dadf" : (parent.hovered ? "#eaebed" : "#f2f3f5")
            }
            onClicked: {
                if (model.deviceObject.targetTemperature !== undefined) model.deviceObject.targetTemperature -= 1
            }
        }

        Text {
            text: (model.deviceObject.targetTemperature !== undefined ? model.deviceObject.targetTemperature : 22) + "°C"
            font.pixelSize: 15
            font.bold: true
            color: "#1c1d20"
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            text: "+"
            implicitWidth: 28
            implicitHeight: 28
            contentItem: Text {
                text: parent.text
                color: "#1c1d20"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                radius: 6
                color: parent.down ? "#d8dadf" : (parent.hovered ? "#eaebed" : "#f2f3f5")
            }
            onClicked: {
                if (model.deviceObject.targetTemperature !== undefined) model.deviceObject.targetTemperature += 1
            }
        }
    }
}
