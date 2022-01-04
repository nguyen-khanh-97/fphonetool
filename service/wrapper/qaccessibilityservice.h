#ifndef QACCESSIBILITYSERVICE_H
#define QACCESSIBILITYSERVICE_H

#include <QObject>
#include <jni.h>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include "qaccessibilitywindowinfo.h"
#include "qaccessibilitynodeinfo.h"

class QAccessibilityService : public QObject
{
    Q_OBJECT

public:

    enum GLOBAL_ACTION: int {
    /**
     * Action to go back.
     */
        GLOBAL_ACTION_BACK = 1,
    /**
     * Action to go home.
     */
        GLOBAL_ACTION_HOME = 2,

    /**
     * Action to toggle showing the overview of recent apps. Will fail on platforms that don't
     * show recent apps.
     */
        GLOBAL_ACTION_RECENTS = 3,
    /**
     * Action to open the notifications.
     */
        GLOBAL_ACTION_NOTIFICATIONS = 4,

    /**
     * Action to open the quick settings.
     */
        GLOBAL_ACTION_QUICK_SETTINGS = 5,

    /**
     * Action to open the power long-press dialog.
     */
        GLOBAL_ACTION_POWER_DIALOG = 6,

    /**
     * Action to toggle docking the current app's window
     */
        GLOBAL_ACTION_TOGGLE_SPLIT_SCREEN = 7,

    /**
     * Action to lock the screen
     */
        GLOBAL_ACTION_LOCK_SCREEN = 8,

    /**
     * Action to take a screenshot
     */
        GLOBAL_ACTION_TAKE_SCREENSHOT = 9
    };


private:
    explicit QAccessibilityService();

public:
    static QAccessibilityService* instance();
    QAndroidJniObject *jniObject();
    void registerNatives();
    bool availble();
    void passingObject(QAndroidJniObject);
    void onQAccessibilityEvent(jobject);

    QList<QAccessibilityWindowInfo> getWindows() const;
    QAccessibilityNodeInfo getRootInActiveWindow() const;
    bool performGlobalAction(int action);
    QString packageName();
    QSize getScreenSize();
public slots:
    void onProcess();

signals:
    void availbleChanged(bool);

private:
    static QAccessibilityService* s_Instance;
    QAndroidJniObject* m_javaServiceInstance;
    bool m_isAvailble;
signals:

};

#endif // QACCESSIBILITYSERVICE_H
