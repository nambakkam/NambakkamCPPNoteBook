import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QTQMLBasics 1.0
Rectangle {
    id: root
    implicitWidth: 170
    implicitHeight: 180
    radius: 12
    color: "#ffffff"
    border.color: "#d8dadf"
    border.width: 1

    // Exposed roles from C++ DeviceListModel delegate
    property string deviceName: model.deviceName !== undefined ? model.deviceName : "Device"
    property int deviceType: model.deviceType !== undefined ? model.deviceType : 0
    property bool deviceObj: model.deviceObject !== undefined ? model.deviceObject : false

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        // --- Card Header (Name & Quick Power Switch) ---
        RowLayout {
            Layout.fillWidth: true
            spacing: 4

            Text {
                text: root.deviceName
                font.pixelSize: 14
                font.bold: true
                color: "#1c1d20"
                elide: Text.ElideRight
                Layout.fillWidth: true
            }

            Switch {
                id: powerSwitch
                checked: root.deviceObj.deviceState === DeviceEnums.On
                implicitWidth: 38
                implicitHeight: 22

                indicator: Rectangle {
                    implicitWidth: 38
                    implicitHeight: 22
                    radius: 11
                    color: powerSwitch.checked ? "#5688b9" : "#eaebed"
                    border.color: powerSwitch.checked ? "#3b638b" : "#d8dadf"

                    Rectangle {
                        x: powerSwitch.checked ? parent.width - width - 2 : 2
                        y: 2
                        width: 18
                        height: 18
                        radius: 9
                        color: "#ffffff"

                        Behavior on x {
                            NumberAnimation { duration: 120 }
                        }
                    }
                }

                onCheckedChanged: {
                    model.deviceObject.togglePower()
                }
            }
        }

        // --- Divider Line ---
        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "#f2f3f5"
        }

        // --- Scrollable Inner Controls Area ---
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            Loader {
                width: parent.width
                source: {
                    switch (root.deviceType) {
                        case 0: return "LightControls.qml"          // Light
                        case 1: return "AirConditionerControls.qml" // AirConditioner
                        case 2: return "FridgeControls.qml"         // Fridge
                        case 3: return "WashingMachineControls.qml" // WashingMachine
                        case 4: return "TelevisionControls.qml"     // Television
                        case 5: return "PlugControls.qml"           // SmartPlug
                        case 6: return "SecurityCameraControls.qml" // SecurityCamera
                        default: return ""                                   // Unknown
                    }
                }
            }
        }
    }
}
