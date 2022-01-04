import QtQuick 2.0

Item {
    id: root
    property alias labelInput: labelInputId
    property alias inputFiel: inputFielId
    property alias labelDisplay: labelDisplayId
    property alias displayText: displayTextId
    property alias sendButton: sendBtnId

    signal setValue()

    Text {
        id: labelInputId
        clip: true
        width: root.width*4/40
        anchors{
            left: parent.left
            leftMargin: root.width/40
            verticalCenter: parent.verticalCenter
        }
    }
    TextInput{
        id: inputFielId
        clip: true
        width: root.width*11/40
        anchors{
            top: labelInputId.top
            bottom: labelInputId.bottom
            left: labelInputId.right
            leftMargin: root.width/40
        }

        Rectangle{
            anchors.fill: parent
            color: "transparent"
            border.width: 1
        }
    }

    Text {
        id: labelDisplayId
        clip: true
        width: root.width*4/40
        anchors{
            top: inputFielId.top
            bottom: inputFielId.bottom
            left: inputFielId.right
            leftMargin: root.width/40
        }
    }
    Text{
        id: displayTextId
        clip: true
        width: root.width*11/40
        anchors{
            top: labelDisplayId.top
            bottom: labelDisplayId.bottom
            left: labelDisplayId.right
            leftMargin: root.width/40
        }
    }
    FButton {
        id: sendBtnId
        border.width: pressed? 2 : 0
        border.color: "green"
        width: root.width*4/40
        text: "Set"
        anchors{
            top: displayTextId.top
            bottom: displayTextId.bottom
            left: displayTextId.right
            leftMargin: root.width/40
        }
        onButton_clicked: {
            root.setValue()
        }
    }
}
