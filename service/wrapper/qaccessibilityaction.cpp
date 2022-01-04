#include "qaccessibilityaction.h"


QAccessibilityAction::QAccessibilityAction(QAndroidJniObject object) : QtWrapper(object)
{

}

int QAccessibilityAction::getId()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getId", "()I"));
}

QString QAccessibilityAction::getLabel()
{
    return m_java_object.callObjectMethod("getLabel", "()Ljava/lang/CharSequence;").toString();
}


