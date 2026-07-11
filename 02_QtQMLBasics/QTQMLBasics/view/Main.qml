import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QTQMLBasics // Replace with your actual CMake QML module name

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Smart Home Manager Test"

    // Seed test data when the application loads
    Component.onCompleted: {
        SmartDeviceManager.addRoom("Living Room");
        SmartDeviceManager.addRoom("Bedroom");
        SmartDeviceManager.addRoom("Kitchen");

        // Select the first room by default
        if (SmartDeviceManager.roomsModel.rowCount() > 0) {
            // Retrieve the first room object from the model
            var firstRoom = SmartDeviceManager.roomsModel.data(
                SmartDeviceManager.roomsModel.index(0, 0),
                258 // This corresponds to RoomObjectRole (Qt.UserRole + 2)
            );
            SmartDeviceManager.currentRoom = firstRoom;

            // Add initial lights to the living room
            // Assuming 0 is DeviceEnums.Light based on your enum order
            SmartDeviceManager.addDeviceToCurrentRoom(0, "Main Ceiling Light");
            SmartDeviceManager.addDeviceToCurrentRoom(0, "Floor Lamp");
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 20

        // ==========================================
        // 1. ROOMS PANEL
        // ==========================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.preferredWidth: 250

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
                        SmartDeviceManager.currentRoom = roomObject;
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
                        SmartDeviceManager.addRoom(roomNameInput.text);
                        roomNameInput.clear();
                    }
                }
            }
        }

        // Vertical Separator Line
        Rectangle {
            Layout.fillHeight: true
            width: 1
            color: "lightgray"
        }

        // ==========================================
        // 2. DEVICES PANEL
        // ==========================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

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
                model: SmartDeviceManager.deviceModel

                // Display fallback placeholder text if empty
                Label {
                    text: "No devices in this room"
                    anchors.centerIn: parent
                    visible: devicesListView.count === 0 && SmartDeviceManager.currentRoom
                    color: "gray"
                }

                delegate: ItemDelegate {
                    width: devicesListView.width

                    contentItem: RowLayout {
                        Text {
                            text: deviceName // Custom role from DeviceListModel
                            Layout.fillWidth: true
                        }

                        // Testing dynamic runtime property access on the Light object
                        // (Safe guard checks against missing properties on unimplemented devices)
                        Text {
                            text: (deviceObject && deviceObject.brightness !== undefined)
                                  ? "Brightness: " + deviceObject.brightness + "%"
                                  : "Light Connected"
                            color: "darkcyan"
                        }
                        TextField {
                            text: deviceObject.brightness
                            onTextChanged: {
                                deviceObject.brightness = parseInt(text);
                            }
                        }

                        Button {
                            text: "Delete"
                            onClicked: SmartDeviceManager.removeDeviceFromCurrentRoom(index)
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                enabled: SmartDeviceManager.currentRoom !== null

                TextField {
                    id: deviceNameInput
                    placeholderText: "New Light Name"
                    Layout.fillWidth: true
                }
                Button {
                    text: "Add Light"
                    enabled: deviceNameInput.text.trim() !== ""
                    onClicked: {
                        // 0 passes the Light enum type
                        SmartDeviceManager.addDeviceToCurrentRoom(0, deviceNameInput.text);
                        deviceNameInput.clear();
                    }
                }
            }
        }
    }
}
