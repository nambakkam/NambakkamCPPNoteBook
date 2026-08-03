import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: root
    title: "Add New Room"
    modal: true
    focus: true
    anchors.centerIn: Overlay.overlay
    width: 320

    signal roomAdded(string roomName)

    readonly property var roomPresets: ["Living Room", "Bedroom", "Kitchen", "Office", "Garage", "Bathroom"]

    onAboutToShow: {
        roomInput.text = ""
        roomInput.forceActiveFocus()
    }

    // Modal Card Window Styling
    background: Rectangle {
        color: "#ffffff"
        radius: 12
        border.color: "#d8dadf"
    }

    // Custom Header
    header: Rectangle {
        height: 48
        color: "#f2f3f5"
        radius: 12

        // Flatten bottom corners to align with card body
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 12
            color: "#f2f3f5"
        }

        Text {
            anchors.centerIn: parent
            text: root.title
            font.pixelSize: 15
            font.bold: true
            color: "#1c1d20"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 16

        // 1. Text Field Section
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "Room Name"
                font.pixelSize: 13
                font.bold: true
                color: "#818a97"
            }

            TextField {
                id: roomInput
                placeholderText: "Type or pick a preset..."
                Layout.fillWidth: true
                implicitHeight: 40
                selectByMouse: true
                color: "#1c1d20"
                placeholderTextColor: "#818a97"

                background: Rectangle {
                    radius: 8
                    color: "#f2f3f5"
                    border.color: roomInput.activeFocus ? "#5688b9" : "#d8dadf"
                    border.width: roomInput.activeFocus ? 2 : 1

                    Behavior on border.color {
                        ColorAnimation { duration: 150 }
                    }
                }

                onAccepted: {
                    if (okButton.enabled) root.accept()
                }
            }
        }

        // 2. Quick Presets Section
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "Quick Presets"
                font.pixelSize: 12
                color: "#818a97"
            }

            Flow {
                Layout.fillWidth: true
                spacing: 6

                Repeater {
                    model: root.roomPresets

                    Button {
                        text: modelData
                        implicitHeight: 32

                        contentItem: Text {
                            text: parent.text
                            font.pixelSize: 12
                            font.weight: Font.Medium
                            color: parent.down ? "#3b638b" : (parent.hovered ? "#5688b9" : "#1c1d20")
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 16
                            color: parent.down ? "#d8dadf" : (parent.hovered ? "#eaebed" : "#f2f3f5")
                            border.color: parent.hovered || parent.down ? "#5688b9" : "#d8dadf"

                            Behavior on color {
                                ColorAnimation { duration: 100 }
                            }
                        }

                        onClicked: {
                            roomInput.text = modelData
                            roomInput.forceActiveFocus()
                        }
                    }
                }
            }
        }
    }

    // 3. Custom Footer Buttons
    footer: DialogButtonBox {
        background: Rectangle {
            color: "#ffffff"
        }

        // "Add Room" Primary Button
        Button {
            id: okButton
            text: "Add Room"
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            enabled: roomInput.text.trim().length > 0
            implicitHeight: 36

            contentItem: Text {
                text: parent.text
                font.pixelSize: 13
                font.bold: true
                color: parent.enabled ? "#ffffff" : "#818a97"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: parent.enabled
                    ? (parent.down ? "#3b638b" : (parent.hovered ? "#4875a3" : "#5688b9"))
                    : "#f2f3f5"

                Behavior on color {
                    ColorAnimation { duration: 100 }
                }
            }
        }

        // "Cancel" Secondary Button
        Button {
            text: "Cancel"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
            implicitHeight: 36

            contentItem: Text {
                text: parent.text
                font.pixelSize: 13
                color: parent.down ? "#3b638b" : (parent.hovered ? "#5688b9" : "#818a97")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                radius: 8
                color: parent.down ? "#d8dadf" : (parent.hovered ? "#eaebed" : "#f2f3f5")

                Behavior on color {
                    ColorAnimation { duration: 100 }
                }
            }
        }
    }

    onAccepted: {
        let trimmedName = roomInput.text.trim()
        if (trimmedName.length > 0) {
            root.roomAdded(trimmedName)
        }
    }
}
