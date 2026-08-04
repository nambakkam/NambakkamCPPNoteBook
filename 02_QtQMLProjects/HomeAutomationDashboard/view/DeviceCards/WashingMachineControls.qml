import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 4

    Label {
        text: "Cycle Status"
        font.pixelSize: 11
        font.bold: true
        color: "#818a97"
    }

    Text {
        text: model.deviceObject.isRunning !== undefined ? (model.deviceObject.isRunning ? "Running" : "Idle") : "Idle"
        font.pixelSize: 14
        font.bold: true
        color: "#1c1d20"
    }

    Text {
        text: model.deviceObject.timeRemainingMinutes !== undefined ? (model.deviceObject.timeRemainingMinutes + " min left") : "Ready"
        font.pixelSize: 11
        color: "#5688b9"
    }
}
