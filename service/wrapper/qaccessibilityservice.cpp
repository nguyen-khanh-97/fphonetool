#include "qaccessibilityservice.h"
#include "../utils/log.h"
#include "../utils/futils.h"
#include <QRandomGenerator>
#include <QMutex>
#include <QAndroidJniEnvironment>

static void startNative(JNIEnv *env, jobject thiz) {
    jobject globObj = env->NewGlobalRef(thiz);
    QAccessibilityService::instance()->passingObject(globObj);
}

static void passAccessiblityEvent(JNIEnv */*env*/, jobject /*thiz*/, jobject event) {
    QAccessibilityService::instance()->onQAccessibilityEvent(event);
}

QAccessibilityService* QAccessibilityService::s_Instance = nullptr;

QAccessibilityService::QAccessibilityService() :
    QObject(nullptr),
    m_javaServiceInstance(nullptr),
    m_isAvailble(false)
{
    registerNatives();
    LOGD("--- Created QAccessibilityService CPP --- ");
}

QAccessibilityService *QAccessibilityService::instance()
{
    QMutex mutex;
    mutex.lock();
    if(s_Instance == nullptr) {
        s_Instance = new QAccessibilityService();
    }
    mutex.unlock();
    return s_Instance;
}

void QAccessibilityService::registerNatives()
{
    JNINativeMethod methods[] {
        {"startNative", "()V", reinterpret_cast<void *>(startNative)},
        {"onQAccessibilityEvent", "(Landroid/view/accessibility/AccessibilityEvent;)V", reinterpret_cast<void *>(passAccessiblityEvent)},
    };
    QAndroidJniObject javaClass("org/qtproject/fphonetool/service/QAccessibilityService");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

QAndroidJniObject *QAccessibilityService::jniObject()
{
      return m_javaServiceInstance;
}

bool QAccessibilityService::availble()
{
    return m_javaServiceInstance != nullptr && m_javaServiceInstance->isValid();
}

void QAccessibilityService::passingObject(QAndroidJniObject javaObject)
{
    LOGD("");
    if(javaObject == nullptr) {
        delete m_javaServiceInstance;
        m_javaServiceInstance = nullptr;
        emit availbleChanged(false);
    } else {
        if(m_javaServiceInstance == nullptr) {
            m_javaServiceInstance = new QAndroidJniObject(javaObject);
            if(m_javaServiceInstance->isValid()) {
                emit availbleChanged(true);
            } else {
               m_javaServiceInstance = nullptr;
            }
        }
    }
}

void QAccessibilityService::onQAccessibilityEvent(jobject event)
{
    Q_UNUSED(event);
}

QAccessibilityNodeInfo QAccessibilityService::getRootInActiveWindow() const
{
    QAndroidJniObject rootObj = m_javaServiceInstance->callObjectMethod("getRootInActiveWindow", "()Landroid/view/accessibility/AccessibilityNodeInfo;");
    if(!rootObj.isValid()) {
        LOGE("get root in active failed");
    }
    return QAccessibilityNodeInfo(rootObj);
}

bool QAccessibilityService::performGlobalAction(int action)
{
    LOGD("action: %d", action);
    QMutex mutex;
    mutex.lock();
    bool success = static_cast<bool>(m_javaServiceInstance->callMethod<jboolean>("performGlobalAction", "(I)Z", action));
    mutex.unlock();
    return success;
}

QSize QAccessibilityService::getScreenSize()
{
    QAndroidJniObject sizeObj = m_javaServiceInstance->callObjectMethod("getScreenSize", "()Landroid/util/Size;");
    if(sizeObj.isValid()) {
        int width = sizeObj.callMethod<jint>("getWidth");
        int height = sizeObj.callMethod<jint>("getHeight");
        return QSize(width,height);
    }
    return QSize();
}

void QAccessibilityService::onProcess()
{
    LOGD("");
}

QList<QAccessibilityWindowInfo> QAccessibilityService::getWindows() const
{
    QAndroidJniObject windowArray = m_javaServiceInstance->callObjectMethod("getWindows", "()Ljava/util/List;");
    if(windowArray.isValid()) {
        QList<QAccessibilityWindowInfo> windows;
        for (int i = 0; i < windowArray.callMethod<jint>("size"); ++i) {
            QAccessibilityWindowInfo windowInfo(windowArray.callObjectMethod("get", "(I)Ljava/lang/Object;", i));
            windows.append(windowInfo);
        }
        return windows;
    } else {
        LOGE("getWindows failed");
    }
    return QList<QAccessibilityWindowInfo>();
}
