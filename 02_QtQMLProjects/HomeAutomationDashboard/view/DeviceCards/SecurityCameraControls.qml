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
            color: (model.deviceObject.isStreaming !== undefined ? model.deviceObject.isStreaming  : true) ? "#4caf50" : "#818a97"
        }

        Text {
            text: (model.deviceObject.isStreaming  !== undefined ? model.deviceObject.isStreaming  : true) ? "LIVE" : "OFFLINE"
            font.pixelSize: 11
            font.bold: true
            color: "#1c1d20"
        }
    }

    Text {
        text: model.deviceObject.motionDetectionEnabled ? "Motion Detected" : "No Motion"
        font.pixelSize: 11
        color: model.deviceObject.motionDetectionEnabled ? "#5688b9" : "#818a97"
    }
}
