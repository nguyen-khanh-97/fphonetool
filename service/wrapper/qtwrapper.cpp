#include "qtwrapper.h"

QtWrapper::QtWrapper(QAndroidJniObject object)
{
    m_java_object = object;
}

bool QtWrapper::isValid()
{
    return m_java_object.isValid();
}

QString QtWrapper::toString()
{
    return m_java_object.callObjectMethod("toString", "()Ljava/lang/String;").toString();
}

bool QtWrapper::equals(QtWrapper other)
{
    QAndroidJniEnvironment jniEnv;
    jobject otherObject = other.object();
    jobject globalObject = jniEnv->NewGlobalRef(otherObject);
    bool success = static_cast<bool>(m_java_object.callMethod<jboolean>("equals", "(Ljava/lang/Object;)Z"),globalObject);
    jniEnv->DeleteLocalRef(globalObject);
    return success;
}

jobject QtWrapper::object()
{
    return m_java_object.object();
}
