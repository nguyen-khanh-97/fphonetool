#include "appmain.h"
#include "../utils/log.h"
#include <QQmlContext>
#include <QAndroidIntent>
#include <QtAndroid>

AppMain::AppMain(QQmlApplicationEngine* engine, QObject *parent) : QObject(parent),
    m_engine(engine),
    m_isAccessibilityAvailble(false),
    m_appDataPrefs("appData")
{
//    m_aslbServiceCom = new ASBLServiceCommunication(this);
    LOGD("");
}

AppMain::~AppMain()
{
    LOGD("");
}

void AppMain::initAplication()
{
    LOGD("");
    m_engine->rootContext()->setContextProperty("APP_MAIN", this);

    // connect signal slot
    connectSignalSlots();
}

void AppMain::startGetScreenInfo()
{
    m_aslbServiceCom.sendData("startMission", "getScreenInfo");
}

void AppMain::sendScreenInfo()
{
    m_aslbServiceCom.sendData("startMission", "sendScreenInfo");
}

void AppMain::openAccessibilySetting()
{
    QAndroidIntent intent = QAndroidIntent("android.settings.ACCESSIBILITY_SETTINGS");
    QtAndroid::startActivity(intent.handle(), 1000, nullptr);
}

void AppMain::updateDefinition()
{
    m_aslbServiceCom.sendData("startMission","updateDefinition");
}

bool AppMain::accessibilityAvailble()
{
    return m_aslbServiceCom.asblStatus();
}

void AppMain::connectSignalSlots()
{
    connect(&m_aslbServiceCom, &ASBLServiceCommunication::asblStatusChanged, this, &AppMain::accessibilityAvailbleChanged);
    connect(&m_aslbServiceCom, &ASBLServiceCommunication::initializedReplicaSuccess, this, &AppMain::onInitializedReplicaSuccess);
    connect(&m_aslbServiceCom, &ASBLServiceCommunication::broadcastData, this, &AppMain::onASBLServiceCommunicationBroadcastData);
    onInitializedReplicaSuccess();
}

void AppMain::onInitializedReplicaSuccess()
{
    m_aslbServiceCom.sendData("androidId", getAndroidId());
    m_aslbServiceCom.sendData("screenId", getScreenId());
    m_aslbServiceCom.sendData("token", getToken());
    m_aslbServiceCom.sendData("action", getAction());
    m_aslbServiceCom.sendData("waitTime", getWaitTime());

    m_aslbServiceCom.sendData("requestData", "currentScreenId");

    updateDefinition();
}

void AppMain::onASBLServiceCommunicationBroadcastData(QString key, QVariant value)
{
    QTLOGD << key << ": " << value;
    if(key == "doGetScreenInfo"){
        setCurrentScreenId(value.toString());
    }
}

QString AppMain::getScreenId()
{
    QString data = m_appDataPrefs.getString("screenId");
    if(data.isEmpty()){
        return "default_screenId";
    } else {
        return data;
    }
}

void AppMain::setScreenId(QString screenId)
{
    if(screenId.isEmpty()){
        screenId = "default_screenId";
    }
    if (getScreenId() == screenId)
        return;

    m_appDataPrefs.setString("screenId", screenId);
    m_aslbServiceCom.sendData("screenId", screenId);
    emit screenIdChanged();
}

QString AppMain::getAndroidId()
{
    QString data = m_appDataPrefs.getString("androidId");
    if(data.isEmpty()){
        return "default_androidId";
    } else {
        return data;
    }
}

void AppMain::setAndroidId(QString androidId)
{
    if(androidId.isEmpty()){
        androidId = "default_androidId";
    }
    if (getAndroidId() == androidId)
        return;

    m_appDataPrefs.setString("androidId", androidId);
    m_aslbServiceCom.sendData("androidId", androidId);
    emit androidIdChanged();
}

QString AppMain::getToken()
{
    QString data = m_appDataPrefs.getString("token");
    if(data.isEmpty()){
        return "default_token";
    } else {
        return data;
    }
}

void AppMain::setToken(QString token)
{
    if(token.isEmpty()){
        token = "default_token";
    }
    if (getToken() == token)
        return;

    m_appDataPrefs.setString("token", token);
    m_aslbServiceCom.sendData("token", token);
    emit tokenChanged();
}

QString AppMain::getAction()
{
    QString data = m_appDataPrefs.getString("action");
    if(data.isEmpty()){
        return "default_action";
    } else {
        return data;
    }
}

void AppMain::setAction(QString action)
{
    if(action.isEmpty()){
        action = "default_action";
    }
    if (getAction() == action)
        return;

    m_appDataPrefs.setString("action", action);
    m_aslbServiceCom.sendData("action", action);
    emit actionChanged();
}

int AppMain::getWaitTime()
{
    int data = m_appDataPrefs.getInt("waitTime",5);
    return data;
}

void AppMain::setWaitTime(int waitTime)
{
    if(waitTime<0){
        waitTime = 0;
    }
    if (getWaitTime() == waitTime)
        return;

    m_appDataPrefs.setInt("waitTime", waitTime);
    m_aslbServiceCom.sendData("waitTime", waitTime);
    emit waitTimeChanged();
}

QString AppMain::getCurrentScreenId() const
{
    return m_currentScreenId;
}

void AppMain::setCurrentScreenId(QString currentScreenId)
{
    if (m_currentScreenId == currentScreenId)
        return;

    m_currentScreenId = currentScreenId;
    emit currentScreenIdChanged();
}
