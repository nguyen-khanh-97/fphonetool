#ifndef APPINFO_H
#define APPINFO_H


#include <QString>
#include <QJsonObject>

class AppInfo
{
public:
    static AppInfo* getInstance();

    void setCurrentScreenId(QString currentScreenId);
    QString getCurrentScreenId() const;

    void setAndroidId(QString androidId);
    QString getAndroidId() const;

    void setScreenId(QString screenId);
    QString getScreenId() const;

    void setToken(QString token);
    QString getToken() const;

    void setAction(QString action);
    QString getAction() const;

    void setImagePath(QString imagePath);
    QString getImagePath() const;

    void setScreenInfoPath(QString screenInfoPath);
    QString getScreenInfoPath() const;

    void setWaitTime(int waitTime);
    int getWaitTime() const;

private:
    AppInfo();
    ~AppInfo();

private:
    static AppInfo* instance;

    QString m_currentScreenId;
    QString m_androidId;
    QString m_screenId;
    QString m_token;
    QString m_action;
    QString m_imagePath;
    QString m_screenInfoPath;
    int m_waitTime;
};

#endif // APPINFO_H
