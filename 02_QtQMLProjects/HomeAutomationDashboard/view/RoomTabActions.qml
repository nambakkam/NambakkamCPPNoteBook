import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root
    spacing: 0

    // Signals to communicate clicks to parent
    signal addRoomClicked()
    signal settingsClicked()

    // --- Add Room Button ---
    ToolButton {
        id: addRoomBtn
        text: "+"
        implicitWidth: 40
        implicitHeight: parent.height

        font {
            pixelSize: 30
            weight: Font.Medium
            styleName: "Roboto"
        }

        contentItem: Text {
            text: addRoomBtn.text
            font: addRoomBtn.font

            // Visual feedback: Normal -> Hover -> Pressed (Down)
            color: addRoomBtn.down ? "#3b638b" : (addRoomBtn.hovered ? "#5688b9" : "#818a97")

            // Subtle opacity change when pressed down
            opacity: addRoomBtn.down ? 0.7 : 1.0

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight

            // Smooth opacity transition
            Behavior on opacity {
                NumberAnimation { duration: 100 }
            }
        }

        background: Rectangle {
            implicitWidth: 40
            implicitHeight: addRoomBtn.height

            // Background darkens when hovered, and darkens further when pressed down
            color: addRoomBtn.down ? "#d8dadf" : (addRoomBtn.hovered ? "#eaebed" : "#f2f3f5")

            Behavior on color {
                ColorAnimation { duration: 100 }
            }
        }

        onClicked: root.addRoomClicked()
    }

    // --- Settings Button ---
    ToolButton {
        id: settingsBtn
        text: "⚙"
        implicitWidth: 40
        implicitHeight: parent.height

        font {
            pixelSize: 22 // Adjusted slightly for cleaner icon scale
            weight: Font.Medium
            styleName: "Roboto"
        }

        contentItem: Text {
            text: settingsBtn.text
            font: settingsBtn.font

            // Visual feedback: Normal -> Hover -> Pressed (Down)
            color: settingsBtn.down ? "#3b638b" : (settingsBtn.hovered ? "#5688b9" : "#818a97")

            // Subtle opacity change when pressed down
            opacity: settingsBtn.down ? 0.7 : 1.0

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight

            // Smooth opacity transition
            Behavior on opacity {
                NumberAnimation { duration: 100 }
            }
        }

        background: Rectangle {
            implicitWidth: 40
            implicitHeight: settingsBtn.height

            // Background darkens when hovered, and darkens further when pressed down
            color: settingsBtn.down ? "#d8dadf" : (settingsBtn.hovered ? "#eaebed" : "#f2f3f5")

            Behavior on color {
                ColorAnimation { duration: 100 }
            }
        }

        onClicked: root.settingsClicked()
    }
}
