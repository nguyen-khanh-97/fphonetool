#include "servicemain.h"
#include "../utils/log.h"
#include "wrapper/qaccessibilityservice.h"
#include <QThread>
#include "jsonparserengine.h"
#include "screendefine/screendefine.h"
#include "appinfo.h"
#include "futils.h"

ServiceMain::ServiceMain(QObject *parent) :
    QObject(parent)
{
    QUrl url(QStringLiteral("local:replica"));
    srcNode = new QRemoteObjectHost(url);
    srcNode->enableRemoting(&m_app_communition);

    connectSignalSlots();

    QAccessibilityService::instance();
    LOGD(" -- Created ServiceMain -- ");
}

void ServiceMain::doGetScreenInfo()
{
    QTLOGD;
    for(int i = AppInfo::getInstance()->getWaitTime(); i>=0; i--){
        FUtils::showToast("Start get screen info in " + QString::number(i) + " second!");
        FUtils::delay(1000);
    }

    QJsonObject screenInfo = Screendefine::instance()->getCurrentScreenInfo();
    QString screenId = screenInfo.value("screen_id").toString();
    AppInfo::getInstance()->setCurrentScreenId(screenId);
    m_app_communition.broadcastData("doGetScreenInfo", screenId);
    FUtils::showToast("Get screen info success!");
}

void ServiceMain::doSendScreenInfo()
{
    FUtils::showToast("Start send screen info to JsonParser");
    QJsonObject response;
    bool success = JsonParserEngine::getInstance()->createLog(AppInfo::getInstance()->getScreenId(), AppInfo::getInstance()->getToken(),
                                               AppInfo::getInstance()->getAction(), AppInfo::getInstance()->getAndroidId(),
                                               AppInfo::getInstance()->getImagePath(), AppInfo::getInstance()->getScreenInfoPath(),
                                               response);
    QTLOGD << "success: " << success << ", response: " << response;
    FUtils::showToast("Send success: " + QVariant(success).toString());
}

void ServiceMain::updateDefinition()
{
    FUtils::showToast("Start get definition");
    QJsonArray definition;
    if(JsonParserEngine::getInstance()->getDefinition(definition)){
        Screendefine::instance()->setScreenInfinity(definition);
        FUtils::showToast("Get definition success!");
    } else {
        FUtils::showToast("Cannot get definition, please check connection again");
    }
}

void ServiceMain::connectSignalSlots()
{
    LOGD("connectSignalSlots");
    connect(QAccessibilityService::instance(), &QAccessibilityService::availbleChanged, this, &ServiceMain::onASBLServiceAvailbleChanged);
    connect(&m_app_communition, &AppCommunition::startMisstion, this, &ServiceMain::onStartMission);
}

void ServiceMain::onASBLServiceAvailbleChanged(bool state)
{
    QTLOGD << state;
    m_app_communition.setAsblStatus(state);
}

void ServiceMain::onStartMission(QString mission)
{
    if(mission == "getScreenInfo"){
        doGetScreenInfo();
    } else if(mission == "sendScreenInfo") {
        doSendScreenInfo();
    } else if(mission == "updateDefinition") {
        updateDefinition();
    }
}
