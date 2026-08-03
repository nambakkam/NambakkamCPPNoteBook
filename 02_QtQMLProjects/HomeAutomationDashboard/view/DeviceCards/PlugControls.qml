import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 6

    Label {
        text: "Power Draw"
        font.pixelSize: 11
        font.bold: true
        color: "#818a97"
    }

    RowLayout {
        spacing: 4

        Text {
            text: model.powerDraw !== undefined ? model.powerDraw : "0"
            font.pixelSize: 20
            font.bold: true
            color: "#1c1d20"
        }

        Text {
            text: "W"
            font.pixelSize: 12
            color: "#818a97"
            Layout.alignment: Qt.AlignBottom
            Layout.bottomMargin: 2
        }
    }
}