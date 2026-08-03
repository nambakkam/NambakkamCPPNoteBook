import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HomeAutomationDashboard 1.0

Dialog {
    id: root
    title: "Add New Device"
    modal: true
    focus: true
    anchors.centerIn: Overlay.overlay
    width: 340

    // Emitted when user confirms creation with device name and C++ enum value
    signal deviceAdded(int deviceType, string deviceName)

    // Tracks whether user has manually edited the text field
    property bool userHasEdited: false

    onAboutToShow: {
        userHasEdited = false
        typeCombo.currentIndex = 0
        updatePrefilledName()
        nameInput.forceActiveFocus()
    }

    // Safely reads the prefix from the selected C++ deviceTypeModel item
    function updatePrefilledName() {
        if (!userHasEdited) {
            let modelData = SmartDeviceManager.deviceTypeModel
            if (modelData && modelData.length > typeCombo.currentIndex) {
                let currentItem = modelData[typeCombo.currentIndex]
                nameInput.text = currentItem.prefix !== undefined ? currentItem.prefix : ""
                nameInput.selectAll()
            }
        }
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

        // 1. Device Type Selector (ComboBox)
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "Device Type"
                font.pixelSize: 13
                font.bold: true
                color: "#818a97"
            }

            ComboBox {
                id: typeCombo
                Layout.fillWidth: true
                implicitHeight: 40

                // Binds directly to C++ QVariantList property
                model: SmartDeviceManager.deviceTypeModel
                textRole: "name"

                // Custom Dropdown Item Layout & Styling
                delegate: ItemDelegate {
                    width: typeCombo.width
                    contentItem: Text {
                        text: modelData.name !== undefined ? modelData.name : ""
                        color: parent.highlighted ? "#5688b9" : "#1c1d20"
                        font.bold: parent.highlighted
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        color: parent.highlighted ? "#f2f3f5" : "#ffffff"
                    }
                }

                // Control Box Styling
                background: Rectangle {
                    radius: 8
                    color: "#f2f3f5"
                    border.color: typeCombo.activeFocus ? "#5688b9" : "#d8dadf"
                    border.width: typeCombo.activeFocus ? 2 : 1

                    Behavior on border.color {
                        ColorAnimation { duration: 150 }
                    }
                }

                contentItem: Text {
                    leftPadding: 10
                    text: typeCombo.displayText
                    font.pixelSize: 13
                    color: "#1c1d20"
                    verticalAlignment: Text.AlignVCenter
                }

                // Trigger prefix pre-fill on selection change
                onActivated: {
                    root.userHasEdited = false
                    root.updatePrefilledName()
                }
            }
        }

        // 2. Device Name Input (TextField)
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 6

            Label {
                text: "Device Name"
                font.pixelSize: 13
                font.bold: true
                color: "#818a97"
            }

            TextField {
                id: nameInput
                Layout.fillWidth: true
                implicitHeight: 40
                selectByMouse: true
                color: "#1c1d20"
                placeholderText: "Enter device name..."
                placeholderTextColor: "#818a97"

                // Stop overwriting if user manually types
                onTextEdited: root.userHasEdited = true

                background: Rectangle {
                    radius: 8
                    color: "#f2f3f5"
                    border.color: nameInput.activeFocus ? "#5688b9" : "#d8dadf"
                    border.width: nameInput.activeFocus ? 2 : 1

                    Behavior on border.color {
                        ColorAnimation { duration: 150 }
                    }
                }

                onAccepted: {
                    if (okButton.enabled) root.accept()
                }
            }
        }
    }

    // 3. Footer Action Buttons
    footer: DialogButtonBox {
        background: Rectangle {
            color: "#ffffff"
        }

        // "Add Device" Primary Button
        Button {
            id: okButton
            text: "Add Device"
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            enabled: nameInput.text.trim().length > 0
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

    // Extract values and emit signal on confirmation
    onAccepted: {
        let trimmedName = nameInput.text.trim()
        let modelData = SmartDeviceManager.deviceTypeModel

        if (trimmedName.length > 0 && modelData && modelData.length > typeCombo.currentIndex) {
            let selectedType = modelData[typeCombo.currentIndex].type
            root.deviceAdded(selectedType,trimmedName)
        }
    }
}
