#include "qaccessibilitynodeinfo.h"
#include "qaccessibilityaction.h"
#include "qaccessibilitywindowinfo.h"

QAccessibilityNodeInfo::QAccessibilityNodeInfo(QAndroidJniObject object) : QtWrapper(object)
{

}

QString QAccessibilityNodeInfo::getPackageName()
{
    return  m_java_object.callObjectMethod("getPackageName", "()Ljava/lang/CharSequence;").toString();
}

QAccessibilityNodeInfo QAccessibilityNodeInfo::getParent()
{
    return QAccessibilityNodeInfo(m_java_object.callObjectMethod("getParent", "()Landroid/view/accessibility/AccessibilityNodeInfo;"));
}

QString QAccessibilityNodeInfo::getStateDescription()
{
    return  m_java_object.callObjectMethod("getStateDescription", "()Ljava/lang/CharSequence;").toString();
}

QString QAccessibilityNodeInfo::getText()
{
    return m_java_object.callObjectMethod("getText", "()Ljava/lang/CharSequence;").toString();
}

int QAccessibilityNodeInfo::getTextSelectionEnd()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getTextSelectionEnd", "()I"));
}

int QAccessibilityNodeInfo::getTextSelectionStart()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getTextSelectionStart", "()I"));
}

QString QAccessibilityNodeInfo::getViewIdResourceName()
{
    return m_java_object.callObjectMethod("getViewIdResourceName", "()Ljava/lang/String;").toString();
}

QAccessibilityWindowInfo QAccessibilityNodeInfo::getWindow()
{
    return QAccessibilityWindowInfo(m_java_object.callObjectMethod("getWindow", "()Landroid/view/accessibility/AccessibilityWindowInfo;"));
}

int QAccessibilityNodeInfo::getWindowId()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getWindowId", "()I"));
}

int QAccessibilityNodeInfo::hashCode()
{
    return static_cast<int>(m_java_object.callMethod<jint>("hashCode", "()I"));
}

bool QAccessibilityNodeInfo::isAccessibilityFocused()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isAccessibilityFocused", "()Z"));
}

bool QAccessibilityNodeInfo::isCheckable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isCheckable", "()Z"));
}

bool QAccessibilityNodeInfo::isChecked()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isChecked", "()Z"));
}

bool QAccessibilityNodeInfo::isClickable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isClickable", "()Z"));
}

bool QAccessibilityNodeInfo::isContentInvalid()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isContentInvalid", "()Z"));
}

bool QAccessibilityNodeInfo::isContextClickable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isContextClickable", "()Z"));
}

bool QAccessibilityNodeInfo::isDismissable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isDismissable", "()Z"));
}

bool QAccessibilityNodeInfo::isEditable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isEditable", "()Z"));
}

bool QAccessibilityNodeInfo::isEnabled()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isEnabled", "()Z"));
}

bool QAccessibilityNodeInfo::isFocusable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isFocusable", "()Z"));
}

bool QAccessibilityNodeInfo::isFocused()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isFocused", "()Z"));
}

bool QAccessibilityNodeInfo::isHeading()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isHeading", "()Z"));
}

bool QAccessibilityNodeInfo::isImportantForAccessibility()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isImportantForAccessibility", "()Z"));
}

bool QAccessibilityNodeInfo::isLongClickable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isLongClickable", "()Z"));
}

bool QAccessibilityNodeInfo::isMultiLine()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isMultiLine", "()Z"));
}

bool QAccessibilityNodeInfo::isPassword()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isPassword", "()Z"));
}

bool QAccessibilityNodeInfo::isScreenReaderFocusable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isScreenReaderFocusable", "()Z"));
}

bool QAccessibilityNodeInfo::isScrollable()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isScrollable", "()Z"));
}

bool QAccessibilityNodeInfo::isSelected()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isSelected", "()Z"));
}

bool QAccessibilityNodeInfo::isShowingHintText()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isShowingHintText", "()Z"));
}

bool QAccessibilityNodeInfo::isTextEntryKey()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isTextEntryKey", "()Z"));
}

bool QAccessibilityNodeInfo::isVisibleToUser()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("isVisibleToUser", "()Z"));
}

QString QAccessibilityNodeInfo::getContentDescription()
{
    return m_java_object.callObjectMethod("getContentDescription", "()Ljava/lang/CharSequence;").toString();
}

QString QAccessibilityNodeInfo::getError()
{
    return m_java_object.callObjectMethod("getError", "()Ljava/lang/CharSequence;").toString();
}

QString QAccessibilityNodeInfo::getHintText()
{
    return m_java_object.callObjectMethod("getHintText", "()Ljava/lang/CharSequence;").toString();
}

int QAccessibilityNodeInfo::getInputType()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getInputType", "()I"));
}

bool QAccessibilityNodeInfo::performAction(int action)
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("performAction", "(I)Z", action));
}

bool QAccessibilityNodeInfo::performAction(int action, QAndroidJniObject& arguments)
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("performAction", "(ILandroid/os/Bundle;)Z", action, arguments.object<jobject>()));
}

bool QAccessibilityNodeInfo::refresh()
{
    return static_cast<bool>(m_java_object.callMethod<jboolean>("performAction", "()Z"));
}

void QAccessibilityNodeInfo::recycle()
{
    m_java_object.callMethod<void>("recycle", "()V");
}

QList<QAccessibilityNodeInfo> QAccessibilityNodeInfo::findAccessibilityNodeInfosByText(QString text)
{
    QAndroidJniObject nodeArray = m_java_object.callObjectMethod("findAccessibilityNodeInfosByText", "(Ljava/lang/String;)Ljava/util/List;", QAndroidJniObject::fromString(text).object<jstring>());
    if(nodeArray.isValid()) {
        LOGD("findAccessibilityNodeInfosByText successed");
        QList<QAccessibilityNodeInfo> nodes;
        for (int i = 0; i < nodeArray.callMethod<jint>("size"); ++i) {
            QAccessibilityNodeInfo node(nodeArray.callObjectMethod("get", "(I)Ljava/lang/Object;", i));
            nodes.append(node);
        }
        return nodes;
    } else {
        LOGE("findAccessibilityNodeInfosByText failed");
    }
    return QList<QAccessibilityNodeInfo>();
}

QList<QAccessibilityNodeInfo> QAccessibilityNodeInfo::findAccessibilityNodeInfosByViewId(QString viewId)
{
    QAndroidJniObject nodeArray = m_java_object.callObjectMethod("findAccessibilityNodeInfosByText", "(Ljava/lang/String;)Ljava/util/List;",QAndroidJniObject::fromString(viewId).object<jstring>());
    if(nodeArray.isValid()) {
        LOGD("findAccessibilityNodeInfosByViewId successed");
        QList<QAccessibilityNodeInfo> nodes;
        for (int i = 0; i < nodeArray.callMethod<jint>("size"); ++i) {
            QAccessibilityNodeInfo node(nodeArray.callObjectMethod("get", "(I)Ljava/lang/Object;", i));
            nodes.append(node);
        }
        return nodes;
    } else {
        LOGE("findAccessibilityNodeInfosByViewId failed");
    }
    return QList<QAccessibilityNodeInfo>();
}

QList<QAccessibilityAction> QAccessibilityNodeInfo::getActionList()
{
    QAndroidJniObject actionArray = m_java_object.callObjectMethod("getActionList", "()Ljava/util/List;");
    if(actionArray.isValid()) {
        LOGD("getActionList successed");
        QList<QAccessibilityAction> actions;
        for (int i = 0; i < actionArray.callMethod<jint>("size"); ++i) {
            QAccessibilityAction action(actionArray.callObjectMethod("get", "(I)Ljava/lang/Object;", i));
            actions.append(action);
        }
        return actions;
    } else {
        LOGE("getActionList failed");
    }
    return QList<QAccessibilityAction>();
}

void QAccessibilityNodeInfo::getBoundsInScreen(QRect& outBounds)
{
    QAndroidJniObject rect("android/graphics/Rect");
    QAndroidJniEnvironment jniEnv;
    jobject jrect = jniEnv->NewGlobalRef(rect.object<jobject>());
    m_java_object.callMethod<void>("getBoundsInScreen", "(Landroid/graphics/Rect;)V", jrect);
    outBounds.setTop(rect.getField<jint>("top"));
    outBounds.setLeft(rect.getField<jint>("left"));
    outBounds.setRight(rect.getField<jint>("right"));
    outBounds.setBottom(rect.getField<jint>("bottom"));
    jniEnv->DeleteGlobalRef(jrect);
}

int QAccessibilityNodeInfo::getChildCount()
{
    return static_cast<int>(m_java_object.callMethod<jint>("getChildCount", "()I"));
}

QString QAccessibilityNodeInfo::getClassName()
{
    return m_java_object.callObjectMethod("getClassName", "()Ljava/lang/CharSequence;").toString();
}

QAccessibilityNodeInfo QAccessibilityNodeInfo::getChild(int index)
{
    return QAccessibilityNodeInfo(m_java_object.callObjectMethod("getChild", "(I)Landroid/view/accessibility/AccessibilityNodeInfo;", static_cast<jint>(index)));
}

QAccessibilityNodeInfo QAccessibilityNodeInfo::findFocus(int focus)
{
    return QAccessibilityNodeInfo(m_java_object.callObjectMethod("findFocus", "(I)Landroid/view/accessibility/AccessibilityNodeInfo;", static_cast<jint>(focus)));
}
