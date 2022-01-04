#ifndef APPCOMMUNITION_H
#define APPCOMMUNITION_H

#include <QObject>
#include "../service/rep_qtandroidasblservice_source.h"
#include <android/log.h>

class AppCommunition: public QtAndroidASBLServiceSource
{
Q_OBJECT

public:
    explicit AppCommunition(QObject *parent = nullptr);

public:
    virtual bool asblStatus() const override;
    virtual void setAsblStatus(bool asblStatus) override;

public slots:
    void sendData(QString key, QVariant value) override;

signals:
    void startMisstion(QString mission);

private:
    bool m_asblStatus;
};

#endif // APPCOMMUNITION_H
