#include "appinfo.h"


AppInfo* AppInfo::instance = nullptr;

AppInfo *AppInfo::getInstance()
{
    if(nullptr == instance){
        instance = new AppInfo();
    }
    return instance;
}

void AppInfo::setCurrentScreenId(QString currentScreenId)
{
    if(m_currentScreenId != currentScreenId) {
        m_currentScreenId = currentScreenId;
    }
}

QString AppInfo::getCurrentScreenId() const
{
    return m_currentScreenId;
}

void AppInfo::setAndroidId(QString androidId)
{
    if(m_androidId != androidId) {
        m_androidId = androidId;
    }
}

QString AppInfo::getAndroidId() const
{
    return m_androidId;
}

void AppInfo::setScreenId(QString screenId)
{
    if(m_screenId != screenId) {
        m_screenId = screenId;
    }
}

QString AppInfo::getScreenId() const
{
    return m_screenId;
}

void AppInfo::setToken(QString token)
{
    if(m_token != token) {
        m_token = token;
    }
}

QString AppInfo::getToken() const
{
    return m_token;
}

void AppInfo::setAction(QString action)
{
    if(m_action != action) {
        m_action = action;
    }
}

QString AppInfo::getAction() const
{
    return m_action;
}

void AppInfo::setImagePath(QString imagePath)
{
    if(m_imagePath != imagePath) {
        m_imagePath = imagePath;
    }
}

QString AppInfo::getImagePath() const
{
    return m_imagePath;
}

void AppInfo::setScreenInfoPath(QString screenInfoPath)
{
    if(m_screenInfoPath != screenInfoPath) {
        m_screenInfoPath = screenInfoPath;
    }
}

QString AppInfo::getScreenInfoPath() const
{
    return m_screenInfoPath;
}

void AppInfo::setWaitTime(int waitTime)
{
    if(m_waitTime != waitTime) {
        m_waitTime = waitTime;
    }
}

int AppInfo::getWaitTime() const
{
    return m_waitTime;
}

AppInfo::AppInfo()
{
    setScreenInfoPath("/sdcard/FPhoneScreenLog.txt");
}

AppInfo::~AppInfo()
{

}
