import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 6

    Label {
        text: "Volume"
        font.pixelSize: 11
        font.bold: true
        color: "#818a97"
    }

    Slider {
        id: volSlider
        Layout.fillWidth: true
        from: 0
        to: 100
        value: model.volume !== undefined ? model.volume : 20

        background: Rectangle {
            x: volSlider.leftPadding
            y: volSlider.topPadding + volSlider.availableHeight / 2 - height / 2
            implicitWidth: 100
            implicitHeight: 4
            width: volSlider.availableWidth
            height: implicitHeight
            radius: 2
            color: "#eaebed"

            Rectangle {
                width: volSlider.visualPosition * parent.width
                height: parent.height
                color: "#5688b9"
                radius: 2
            }
        }

        handle: Rectangle {
            x: volSlider.leftPadding + volSlider.visualPosition * (volSlider.availableWidth - width)
            y: volSlider.topPadding + volSlider.availableHeight / 2 - height / 2
            implicitWidth: 16
            implicitHeight: 16
            radius: 8
            color: volSlider.pressed ? "#3b638b" : "#5688b9"
        }

        onValueChanged: {
            if (model.volume !== undefined) model.volume = Math.round(value)
        }
    }
}