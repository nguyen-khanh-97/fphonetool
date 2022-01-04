#ifndef SERVICEMAIN_H
#define SERVICEMAIN_H

#include <QObject>
#include "appcommunition.h"

class ServiceMain : public QObject
{
    Q_OBJECT
public:
    ServiceMain(QObject *parent = nullptr);
    virtual ~ServiceMain() {};

    void doGetScreenInfo();
    void doSendScreenInfo();

    void updateDefinition();

private:
    void connectSignalSlots();

private slots:
    void onASBLServiceAvailbleChanged(bool);
    void onStartMission(QString mission);

private:
    AppCommunition m_app_communition;
    QRemoteObjectHost* srcNode;
};

#endif // SERVICEMAIN_H
