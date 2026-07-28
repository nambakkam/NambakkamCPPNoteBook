import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QTQMLBasics 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 950
    height: 700
    title: "Smart Home Manager - Full Device Suite Test"

    // Seed test data when application loads
    Component.onCompleted: {
        SmartDeviceManager.addRoom("Living Room")
        SmartDeviceManager.addRoom("Kitchen")
        SmartDeviceManager.addRoom("Laundry Room")

        if (SmartDeviceManager.roomsModel.rowCount() > 0) {
            // Select first room (Living Room)
            var firstRoom = SmartDeviceManager.roomsModel.data(
                SmartDeviceManager.roomsModel.index(0, 0),
                258 // RoomObjectRole
            )
            SmartDeviceManager.currentRoom = firstRoom

            // Add initial test devices (using Enum values)
            SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Light, "Main Ceiling Light")
            SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.AirConditioner, "Living Room AC")
            SmartDeviceManager.addDeviceToCurrentRoom(DeviceEnums.Television, "Smart OLED TV")
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 16

        // ==========================================
        // 1. ROOMS PANEL
        // ==========================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.preferredWidth: 240
            spacing: 8

            Label {
                text: "Rooms"
                font.bold: true
                font.pixelSize: 18
            }

            ListView {
                id: roomsListView
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                model: SmartDeviceManager.roomsModel

                delegate: ItemDelegate {
                    width: roomsListView.width
                    text: roomName // Custom role from RoomsModel
                    highlighted: SmartDeviceManager.currentRoom === roomObject

                    onClicked: {
                        SmartDeviceManager.currentRoom = roomObject
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: roomNameInput
                    placeholderText: "New Room Name"
                    Layout.fillWidth: true
                }
                Button {
                    text: "Add"
                    enabled: roomNameInput.text.trim() !== ""
                    onClicked: {
                        SmartDeviceManager.addRoom(roomNameInput.text.trim())
                        roomNameInput.clear()
                    }
                }
            }
        }

        // Vertical Separator
        Rectangle {
            Layout.fillHeight: true
            width: 1
            color: "#D0D0D0"
        }

        // ==========================================
        // 2. DEVICES PANEL & CONTROLS
        // ==========================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 8

            Label {
                text: SmartDeviceManager.currentRoom
                      ? "Devices in " + SmartDeviceManager.currentRoom.roomName
                      : "No Room Selected"
                font.bold: true
                font.pixelSize: 18
            }

            ListView {
                id: devicesListView
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 6
                model: SmartDeviceManager.deviceModel

                Label {
                    text: "No devices in this room"
                    anchors.centerIn: parent
                    visible: devicesListView.count === 0 && SmartDeviceManager.currentRoom
                    color: "gray"
                }

                delegate: Frame {
                    width: devicesListView.width
                    padding: 8

                    ColumnLayout {
                        width: parent.width
                        spacing: 6

                        // Primary Row: Name, Power Toggle, and Delete
                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: deviceName
                                font.bold: true
                                font.pixelSize: 14
                                Layout.fillWidth: true
                            }

                            Button {
                                text: (deviceObject && deviceObject.deviceState === DeviceEnums.On) ? "Power OFF" : "Power ON"
                                // highlight: deviceObject && deviceObject.deviceState === DeviceEnums.On
                                onClicked: {
                                    if (deviceObject) {
                                        deviceObject.togglePower()
                                    }
                                }
                            }

                            Button {
                                text: "Delete"
                                onClicked: SmartDeviceManager.removeDeviceFromCurrentRoom(index)
                            }
                        }

                        // Secondary Row: Specific Property Controls Based on Device Type
                        RowLayout {
                            Layout.fillWidth: true
                            visible: deviceObject !== null

                            // 1. LIGHT CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.Light
                                Text { text: "Brightness:" }
                                Slider {
                                    from: 0; to: 100
                                    value: (deviceObject && deviceObject.brightness !== undefined) ? deviceObject.brightness : 0
                                    onMoved: deviceObject.brightness = Math.round(value)
                                }
                                Text { text: (deviceObject && deviceObject.brightness !== undefined) ? deviceObject.brightness + "%" : "" }
                            }

                            // 2. AIR CONDITIONER CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.AirConditioner
                                Text { text: "Target Temp (°C):" }
                                SpinBox {
                                    from: deviceObject ? deviceObject.lowestTempSetting : 16
                                    to: deviceObject ? deviceObject.highestTempSetting : 30
                                    value: (deviceObject && deviceObject.targetTemperature !== undefined) ? deviceObject.targetTemperature : 24
                                    onValueModified: deviceObject.targetTemperature = value
                                }
                            }

                            // 3. FRIDGE CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.Fridge
                                Text { text: "Fridge: " + (deviceObject ? deviceObject.fridgeTemperature : 0) + "°C | " }
                                Text { text: "Freezer: " + (deviceObject ? deviceObject.freezerTemperature : 0) + "°C | " }
                                CheckBox {
                                    text: "Rapid Cool"
                                    checked: deviceObject ? deviceObject.rapidCool : false
                                    onCheckedChanged: if (deviceObject) deviceObject.rapidCool = checked
                                }
                            }

                            // 4. WASHING MACHINE CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.WashingMachine
                                Button {
                                    text: (deviceObject && deviceObject.isRunning) ? "Pause Cycle" : "Start Cycle"
                                    onClicked: {
                                        if (deviceObject.isRunning) deviceObject.pauseCycle()
                                        else deviceObject.startCycle()
                                    }
                                }
                                Text { text: "Speed: " + (deviceObject ? deviceObject.spinSpeed : 0) + " RPM" }
                            }

                            // 5. TELEVISION CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.Television
                                Button { text: "Vol -"; onClicked: deviceObject.volumeDown() }
                                Text { text: "Vol: " + (deviceObject ? deviceObject.volume : 0) }
                                Button { text: "Vol +"; onClicked: deviceObject.volumeUp() }
                                Button { text: "Ch -"; onClicked: deviceObject.channelDown() }
                                Text { text: "Ch: " + (deviceObject ? deviceObject.channelNumber : 1) }
                                Button { text: "Ch +"; onClicked: deviceObject.channelUp() }
                            }

                            // 6. SMART PLUG CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.SmartPlug
                                Text {
                                    text: "Power: " + (deviceObject ? deviceObject.currentPowerWatts.toFixed(1) : 0) + " W | " +
                                          "Energy: " + (deviceObject ? deviceObject.totalEnergyKWh.toFixed(2) : 0) + " kWh"
                                }
                            }

                            // 7. SECURITY CAMERA CONTROLS
                            RowLayout {
                                visible: deviceObject && deviceObject.deviceType === DeviceEnums.SecurityCamera
                                Button {
                                    text: (deviceObject && deviceObject.isStreaming) ? "Stop Feed" : "Start Feed"
                                    onClicked: {
                                        if (deviceObject.isStreaming) deviceObject.stopStream()
                                        else deviceObject.startStream()
                                    }
                                }
                                CheckBox {
                                    text: "Night Vision"
                                    checked: deviceObject ? deviceObject.nightVisionEnabled : false
                                    onCheckedChanged: if (deviceObject) deviceObject.nightVisionEnabled = checked
                                }
                            }
                        }
                    }
                }
            }

            // Controls for adding new devices of any enum type
            RowLayout {
                Layout.fillWidth: true
                enabled: SmartDeviceManager.currentRoom !== null

                ComboBox {
                    id: deviceTypeSelector
                    Layout.preferredWidth: 160
                    textRole: "text"
                    valueRole: "value"
                    model: [
                        { text: "Light", value: DeviceEnums.Light },
                        { text: "Air Conditioner", value: DeviceEnums.AirConditioner },
                        { text: "Fridge", value: DeviceEnums.Fridge },
                        { text: "Washing Machine", value: DeviceEnums.WashingMachine },
                        { text: "Television", value: DeviceEnums.Television },
                        { text: "Smart Plug", value: DeviceEnums.SmartPlug },
                        { text: "Security Camera", value: DeviceEnums.SecurityCamera }
                    ]
                }

                TextField {
                    id: deviceNameInput
                    placeholderText: "Device Name"
                    Layout.fillWidth: true
                }

                Button {
                    text: "Add Device"
                    enabled: deviceNameInput.text.trim() !== ""
                    onClicked: {
                        SmartDeviceManager.addDeviceToCurrentRoom(
                            deviceTypeSelector.currentValue,
                            deviceNameInput.text.trim()
                        )
                        deviceNameInput.clear()
                    }
                }
            }
        }
    }
}
