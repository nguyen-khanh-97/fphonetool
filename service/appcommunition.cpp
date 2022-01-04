#include "appcommunition.h"
#include "appinfo.h"
#include "log.h"

AppCommunition::AppCommunition(QObject *parent) : QtAndroidASBLServiceSource(parent),
    m_asblStatus(false)
{
#ifdef DEBUG_MODE
    __android_log_print(ANDROID_LOG_VERBOSE, "AppCommunition", " -- Created AppCommunition -- ");
#endif
}

bool AppCommunition::asblStatus() const
{
    return m_asblStatus;
}

void AppCommunition::setAsblStatus(bool asblStatus)
{
    if(m_asblStatus != asblStatus) {
        m_asblStatus = asblStatus;
        emit asblStatusChanged(asblStatus);
    }
}

void AppCommunition::sendData(QString key, QVariant value)
{
    QTLOGD << key << ": " << value;
    if(key == "requestData"){
        if(value.toString() == "currentScreenId"){
            broadcastData("doGetScreenInfo", AppInfo::getInstance()->getCurrentScreenId());
        }
    } else if(key == "startMission"){
        emit startMisstion(value.toString());
    } else {
        if(key.compare("androidId") == 0){
            AppInfo::getInstance()->setAndroidId(value.toString());
        } else if(key.compare("screenId") == 0){
            AppInfo::getInstance()->setScreenId(value.toString());
        } else if(key.compare("token") == 0){
            AppInfo::getInstance()->setToken(value.toString());
        } else if(key.compare("action") == 0){
            AppInfo::getInstance()->setAction(value.toString());
        } else if(key.compare("waitTime") == 0){
            AppInfo::getInstance()->setWaitTime(value.toInt());
        }
    }
}
