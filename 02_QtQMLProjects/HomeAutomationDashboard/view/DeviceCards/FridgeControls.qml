import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 6

    RowLayout {
        Layout.fillWidth: true
        Label {
            text: "Fridge"
            font.pixelSize: 11
            color: "#818a97"
            Layout.fillWidth: true
        }
        Text {
            text: (model.fridgeTemp !== undefined ? model.fridgeTemp : 3) + "°C"
            font.pixelSize: 13
            font.bold: true
            color: "#1c1d20"
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label {
            text: "Freezer"
            font.pixelSize: 11
            color: "#818a97"
            Layout.fillWidth: true
        }
        Text {
            text: (model.freezerTemp !== undefined ? model.freezerTemp : -18) + "°C"
            font.pixelSize: 13
            font.bold: true
            color: "#1c1d20"
        }
    }
}