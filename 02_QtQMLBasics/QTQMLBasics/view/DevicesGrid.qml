import QtQuick
import QtQuick.Layouts
GridLayout {
    id: devicesGrid
    columns: 4
    property var devicesModel: SmartDeviceManager.deviceModel
    Repeater{
        id:devices
        model: devicesGrid.devicesModel
        Rectangle{
            id:deviceRect
            implicitWidth:devicesGrid.width/devicesGrid.columns - 2*devicesGrid.columnSpacing
            implicitHeight: parent.height/3
            Text{
                id:deviceName
                width: parent.width/2
                anchors.centerIn: parent
                text: model.deviceName !== undefined ? model.deviceName : modelData
            }
        }
    }

}
