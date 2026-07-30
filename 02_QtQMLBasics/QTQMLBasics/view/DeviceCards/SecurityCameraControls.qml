import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 6

    RowLayout {
        spacing: 6

        Rectangle {
            width: 8
            height: 8
            radius: 4
            color: (model.isStreaming !== undefined ? model.isStreaming : true) ? "#4caf50" : "#818a97"
        }

        Text {
            text: (model.isStreaming !== undefined ? model.isStreaming : true) ? "LIVE" : "OFFLINE"
            font.pixelSize: 11
            font.bold: true
            color: "#1c1d20"
        }
    }

    Text {
        text: model.motionDetected ? "Motion Detected" : "No Motion"
        font.pixelSize: 11
        color: model.motionDetected ? "#5688b9" : "#818a97"
    }
}