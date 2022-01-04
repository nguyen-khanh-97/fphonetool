#ifndef QTWRAPPER_H
#define QTWRAPPER_H

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include "../utils/log.h"

class QtWrapper
{
public:
    QtWrapper(QAndroidJniObject object);

    bool isValid();
    QString toString();
    bool equals(QtWrapper other);
    jobject object();
protected:
    QAndroidJniObject m_java_object;
};

#endif // QTWRAPPER_H
