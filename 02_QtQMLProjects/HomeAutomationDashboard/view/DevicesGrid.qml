import QtQuick
import QtQuick.Layouts
import "DeviceCards"
Rectangle{
    id:deviceGridBackground
    color: "#e6e9ee"
    signal addDeviceClicked()
    GridLayout {
        id: devicesGrid
        columns: 4
        anchors{
            fill: parent
            margins:30
        }
        property var devicesModel: SmartDeviceManager.deviceModel
        Repeater{
            id:devices
            model: devicesGrid.devicesModel
            DeviceCard{
                id:deviceRect
                implicitWidth:devicesGrid.width/devicesGrid.columns - 2*devicesGrid.columnSpacing
                implicitHeight: parent.height/3
            }
        }
        AddNewDevice{
            id:plusIcon
            implicitWidth:devicesGrid.width/devicesGrid.columns - 2*devicesGrid.columnSpacing
            implicitHeight: parent.height/3
            onClicked: {
                addDeviceClicked()
            }
        }
    }
}



