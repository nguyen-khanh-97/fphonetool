import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import "Component"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("F-Phone")

    GetScreenInfoDialog {
        anchors.fill: parent
        visible: APP_MAIN.accessibilityAvailble
    }

    AccessibilityDialog{
        anchors.fill: parent
        visible: !APP_MAIN.accessibilityAvailble
    }
}
