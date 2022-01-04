import QtQuick 2.14

Rectangle {
    id: root

    property bool checked: false
    property string text: "Button"
    property color textColor: checked? "white" : "black"
    property int fontSize: 30

    readonly property bool pressed: mouseArea.pressed

    signal button_clicked()
    signal button_pressed()

    color: checked? "black" : "grey"
    radius: 5

    Text {
        id: name
        text: root.text
        font.pixelSize: fontSize
        color: textColor
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        padding: 5
        wrapMode: Text.WordWrap
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            button_pressed()
        }

        onClicked:  {
            button_clicked()
        }
    }
}
