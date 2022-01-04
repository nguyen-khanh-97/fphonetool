#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QThread>
#include "asblservicecommunication.h"
#include "sharedpreferenceshelper.h"

class AppMain : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool accessibilityAvailble READ accessibilityAvailble NOTIFY accessibilityAvailbleChanged)
    Q_PROPERTY(QString currentScreenId READ getCurrentScreenId NOTIFY currentScreenIdChanged)

    Q_PROPERTY(QString androidId READ getAndroidId WRITE setAndroidId NOTIFY androidIdChanged)
    Q_PROPERTY(QString screenId READ getScreenId WRITE setScreenId NOTIFY screenIdChanged)
    Q_PROPERTY(QString token READ getToken WRITE setToken NOTIFY tokenChanged)
    Q_PROPERTY(QString action READ getAction WRITE setAction NOTIFY actionChanged)

    Q_PROPERTY(int waitTime READ getWaitTime WRITE setWaitTime NOTIFY waitTimeChanged)

public:
    explicit AppMain(QQmlApplicationEngine* engine, QObject *parent = nullptr);
    ~AppMain();
    void initAplication();

    Q_INVOKABLE void startGetScreenInfo();
    Q_INVOKABLE void sendScreenInfo();
    Q_INVOKABLE void openAccessibilySetting();
    Q_INVOKABLE void updateDefinition();

public:
    bool accessibilityAvailble();

private:
    void connectSignalSlots();

public slots:
    void onInitializedReplicaSuccess();
    void onASBLServiceCommunicationBroadcastData(QString key, QVariant value);

    QString getScreenId();
    void setScreenId(QString screenId);

    QString getAndroidId();
    void setAndroidId(QString androidId);

    QString getToken();
    void setToken(QString token);

    QString getAction();
    void setAction(QString action);

    int getWaitTime();
    void setWaitTime(int waitTime);


    QString getCurrentScreenId() const;
    void setCurrentScreenId(QString currentScreenId);

signals:
    void accessibilityAvailbleChanged(bool asblStatus);
    void startHandler();

    void appNotify(QString message);

    void screenIdChanged();
    void androidIdChanged();
    void tokenChanged();
    void actionChanged();
    void waitTimeChanged();
    void currentScreenIdChanged();

private:
    QQmlApplicationEngine* m_engine;

    bool m_isAccessibilityAvailble;
    ASBLServiceCommunication m_aslbServiceCom;

    SharedPreferencesHelper m_appDataPrefs;
    QString m_currentScreenId;
};

#endif // APPMAIN_H
