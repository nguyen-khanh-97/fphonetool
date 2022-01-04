#ifndef ASBLSERVICECOMMUNICATION_H
#define ASBLSERVICECOMMUNICATION_H

#include "../app/rep_qtandroidasblservice_replica.h"
#include <QObject>
#include <QTimer>

class ASBLServiceCommunication : public QObject
{
    Q_OBJECT
public:
    explicit ASBLServiceCommunication(QObject *parent = nullptr);

    void requestStartMission();
    void sendData(QString key, QVariant value);

    bool asblStatus();

private slots:
    void onCheckASBLServiceConnection();

signals:
    void asblStatusChanged(bool asblStatus);
    void broadcastData(QString key, QVariant value);

    void initializedReplicaSuccess();

private:
    QRemoteObjectNode repNode;
    bool m_isInitializedReplica;
    QTimer m_ConnectionCheckingTimer;
    QSharedPointer<QtAndroidASBLServiceReplica> rep;
};

#endif // ASBLSERVICECOMMUNICATION_H
