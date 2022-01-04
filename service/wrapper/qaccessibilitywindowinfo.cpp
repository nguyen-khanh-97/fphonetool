#include "qaccessibilitywindowinfo.h"
#include "qaccessibilitynodeinfo.h"

QAccessibilityWindowInfo::QAccessibilityWindowInfo(QAndroidJniObject object) : QtWrapper(object)
{

}

QString QAccessibilityWindowInfo::getTitle()
{
    return m_java_object.callObjectMethod("getTitle", "()Ljava/lang/CharSequence;").toString();
}

int QAccessibilityWindowInfo::getType()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getType", "()I"));
}

int QAccessibilityWindowInfo::getLayer()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getLayer", "()I"));
}

int QAccessibilityWindowInfo::getId()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getId", "()I"));
}

bool QAccessibilityWindowInfo::isFocused()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isFocused", "()Z"));
}

QAccessibilityNodeInfo QAccessibilityWindowInfo::getRoot()
{
    return QAccessibilityNodeInfo(m_java_object.callObjectMethod("getRoot", "()Landroid/view/accessibility/AccessibilityNodeInfo;"));
}

void QAccessibilityWindowInfo::recycle()
{
    m_java_object.callMethod<void>("recycle", "()V");
}
