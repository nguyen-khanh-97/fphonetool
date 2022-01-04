import QtQuick 2.0
import "Component"

Item {
    Rectangle{
        anchors.verticalCenter: jsonParserParam.top
        anchors.horizontalCenter: jsonParserParam.horizontalCenter
        z: jsonParserParam.z+1
        width: jsonParserParamtxt.width
        height: jsonParserParamtxt.height
        Text {
            id: jsonParserParamtxt
            z:parent.z+1
            text: "JsonParser Parameter"
        }
    }
    Rectangle{
        id: jsonParserParam
        color: "transparent"
        border.width: 1
        clip: true
        anchors{
            top: parent.top
            topMargin: 100
            horizontalCenter: parent.horizontalCenter
        }

        height: 400
        width: parent.width-50

        SetParameterComponent{
            id: setScreenId
            anchors{
                top: parent.top
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            height: 75
            labelInput.text: "ScreenId"
            labelDisplay.text: "Value:"
            displayText.text: APP_MAIN.screenId
            onSetValue: APP_MAIN.screenId = inputFiel.text
        }
        SetParameterComponent{
            id: setAndroidId
            anchors{
                top: setScreenId.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            height: 75
            labelInput.text: "AndroidId"
            labelDisplay.text: "Value:"
            displayText.text: APP_MAIN.androidId
            onSetValue: APP_MAIN.androidId = inputFiel.text
        }
        SetParameterComponent{
            id: setToken
            anchors{
                top: setAndroidId.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            height: 75
            labelInput.text: "Token"
            labelDisplay.text: "Value:"
            displayText.text: APP_MAIN.token
            onSetValue: APP_MAIN.token = inputFiel.text
        }
        SetParameterComponent{
            id: setAction
            anchors{
                top: setToken.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            height: 75
            labelInput.text: "Action"
            labelDisplay.text: "Value:"
            displayText.text: APP_MAIN.action
            onSetValue: APP_MAIN.action = inputFiel.text
        }
    }

    Rectangle{
        id: lineJsonParserParam
        width: parent.width
        height: 2
        border.width: 1
        anchors.top: jsonParserParam.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    /*********************** End JsonParserParam ***********************/

    Rectangle{
        anchors.verticalCenter: getScreenInfoParam.top
        anchors.horizontalCenter: getScreenInfoParam.horizontalCenter
        z: getScreenInfoParam.z+1
        width: getScreenInfoParamtxt.width
        height: getScreenInfoParamtxt.height
        Text {
            id: getScreenInfoParamtxt
            z:parent.z+1
            text: "Get ScreenInfo Parameter"
        }
    }
    Rectangle{
        id: getScreenInfoParam
        color: "transparent"
        border.width: 1
        clip: true
        anchors{
            top: lineJsonParserParam.top
            topMargin: 100
            horizontalCenter: parent.horizontalCenter
        }

        height: 235
        width: parent.width-50

        SetParameterComponent{
            id: waitTime
            anchors{
                top: parent.top
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            height: 75
            labelInput.text: "Wait Time"
            labelDisplay.text: "Value:"
            displayText.text: APP_MAIN.waitTime
            onSetValue: APP_MAIN.waitTime = inputFiel.text
        }

        FButton{
            id: updateDefinitionBtn
            anchors{
                top: waitTime.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            width: 200
            height: 100
            text: "Update Definition"
            onButton_clicked: {
                APP_MAIN.updateDefinition()
            }
        }
    }

    Rectangle{
        id: lineGetScreenInfoParam
        width: parent.width
        height: 2
        border.width: 1
        anchors.top: getScreenInfoParam.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    /*********************** End GetScreenInfoParam ***********************/

    FButton{
        id: getScreenInfoBtn
        anchors.top: lineGetScreenInfoParam.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        width: 500
        height: 100
        fontSize: 40
        text: "Start get screen info"
        onButton_clicked: {
            APP_MAIN.startGetScreenInfo()
        }
    }

    Text {
        id: curScreenIdText
        text: "Current Screen Id: " + APP_MAIN.currentScreenId

        anchors.top: getScreenInfoBtn.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 100
    }
    FButton{
        id: sendScreenInfoBtn
        anchors.top: curScreenIdText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 50
        width: 500
        height: 100
        fontSize: 40
        text: "Send to JsonParser"
        onButton_clicked: {
            APP_MAIN.sendScreenInfo()
        }
    }
    Text {
        id: noteTxt
        text: "Note: Screen Info save in /sdcard/FPhoneScreenLog.txt"

        anchors.top: sendScreenInfoBtn.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }
}
