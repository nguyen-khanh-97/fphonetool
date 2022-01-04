import QtQuick 2.0
import QtQuick.Controls 2.14
import "Component"

Item {
    id: root
    anchors.fill: parent

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
    }

    Rectangle{
        id: bg
        anchors.fill: parent
        color: "grey"
        opacity: 0.2
    }

    Rectangle {
        anchors.centerIn: parent
        width: parent.width - 200
        height: 400
        border.width: 1
        border.color: "black"

        Item {
            width: parent.width
            height: guideTxt.contentHeight + 50 + okBtn.height
            anchors.centerIn: parent

            Text {
                id: guideTxt
                text: "On the next screen select F-Phone-Tool, turn on the toggle, and then press OK."
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                width: parent.width - 50
                height: contentHeight
            }

            FButton {
                id: okBtn
                border.width: pressed? 2 : 0
                border.color: "green"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: guideTxt.bottom
                anchors.topMargin: 50
                text: "OK"
                width: 200
                height: 100
                onButton_clicked: {
                    APP_MAIN.openAccessibilySetting()
                }
            }
        }
    }
}
