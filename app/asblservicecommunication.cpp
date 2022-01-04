#include "asblservicecommunication.h"
#include "../utils/log.h"

ASBLServiceCommunication::ASBLServiceCommunication(QObject *parent) :
    QObject(parent),
    m_isInitializedReplica(false),
    rep(nullptr)
{
    m_ConnectionCheckingTimer.setInterval(1500);
    m_ConnectionCheckingTimer.setSingleShot(false);
    QObject::connect(&m_ConnectionCheckingTimer, &QTimer::timeout, this, &ASBLServiceCommunication::onCheckASBLServiceConnection);
    m_ConnectionCheckingTimer.start();
    LOGD(" --- Created ServiceCommunication ---");
    onCheckASBLServiceConnection();
}

void ASBLServiceCommunication::requestStartMission()
{

}

void ASBLServiceCommunication::sendData(QString key, QVariant value)
{
    qDebug() << "sendData";
    if(m_isInitializedReplica) {
        qDebug() << "sendData connected";
        rep->sendData(key, value);
    }
}

bool ASBLServiceCommunication::asblStatus()
{
    if(m_isInitializedReplica) {
        return rep->asblStatus();
    } else {
        return false;
    }
}

void ASBLServiceCommunication::onCheckASBLServiceConnection()
{
    qDebug()<<__FUNCTION__;
    if(!m_isInitializedReplica) {
        repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
        rep = QSharedPointer<QtAndroidASBLServiceReplica>(repNode.acquire<QtAndroidASBLServiceReplica>());
        m_isInitializedReplica = rep->waitForSource(1000);
        if(m_isInitializedReplica) {
            qDebug()<<"Init succes";
            QObject::connect(rep.data(), &QtAndroidASBLServiceReplica::asblStatusChanged, this, &ASBLServiceCommunication::asblStatusChanged);
            QObject::connect(rep.data(), &QtAndroidASBLServiceReplica::broadcastData, this, &ASBLServiceCommunication::broadcastData);
            emit initializedReplicaSuccess();
        } else {
            qDebug()<<"cannot connect";
        }
    } else {
        m_ConnectionCheckingTimer.stop();
    }
}

