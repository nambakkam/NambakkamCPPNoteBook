import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 8

    Label {
        text: "Brightness"
        font.pixelSize: 11
        font.bold: true
        color: "#818a97"
    }

    Slider {
        id: brightnessSlider
        Layout.fillWidth: true
        from: 0
        to: 100
        value: model.deviceObject !== undefined ? model.deviceObject.brightness : 100

        background: Rectangle {
            x: brightnessSlider.leftPadding
            y: brightnessSlider.topPadding + brightnessSlider.availableHeight / 2 - height / 2
            implicitWidth: 100
            implicitHeight: 4
            width: brightnessSlider.availableWidth
            height: implicitHeight
            radius: 2
            color: "#eaebed"

            Rectangle {
                width: brightnessSlider.visualPosition * parent.width
                height: parent.height
                color: "#5688b9"
                radius: 2
            }
        }

        handle: Rectangle {
            x: brightnessSlider.leftPadding + brightnessSlider.visualPosition * (brightnessSlider.availableWidth - width)
            y: brightnessSlider.topPadding + brightnessSlider.availableHeight / 2 - height / 2
            implicitWidth: 16
            implicitHeight: 16
            radius: 8
            color: brightnessSlider.pressed ? "#3b638b" : "#5688b9"
        }

        onValueChanged: {
            if (model.deviceObject.brightness !== undefined) {
                model.deviceObject.brightness = Math.round(value)
                brightnessSlider.value = model.deviceObject.brightness
            }
        }
    }
}
