#include "sharedpreferenceshelper.h"
#include <QtAndroid>

SharedPreferencesHelper::SharedPreferencesHelper(QString fileName)
{
    m_sharePrefs = QtAndroid::androidContext().callObjectMethod("getSharedPreferences",
                                                "(Ljava/lang/String;I)Landroid/content/SharedPreferences;",
                                                 QAndroidJniObject::fromString(fileName).object(),
                                                                0);
}

void SharedPreferencesHelper::remove(QString key)
{
    QAndroidJniObject sharePrefsEditor = m_sharePrefs.callObjectMethod("edit",
                                                                       "()Landroid/content/SharedPreferences$Editor;");
    sharePrefsEditor.callObjectMethod("remove",
                                      "(Ljava/lang/String;)Landroid/content/SharedPreferences$Editor;",
                                      QAndroidJniObject::fromString(key).object());
    sharePrefsEditor.callMethod<void>("apply","()V");
}

QString SharedPreferencesHelper::getString(QString key, QString defaultValue)
{

    QString data = m_sharePrefs.callObjectMethod("getString",
                                                 "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                                                 QAndroidJniObject::fromString(key).object(),
                                                 QAndroidJniObject::fromString(defaultValue).object()).toString();
    return data;
}

int SharedPreferencesHelper::getInt(QString key, int defaultValue)
{
    int data = m_sharePrefs.callMethod<jint>("getInt",
                                             "(Ljava/lang/String;I)I",
                                             QAndroidJniObject::fromString(key).object(),
                                             defaultValue);
    return data;
}

void SharedPreferencesHelper::setString(QString key, QString value)
{
    QAndroidJniObject sharePrefsEditor = m_sharePrefs.callObjectMethod("edit",
                                                                       "()Landroid/content/SharedPreferences$Editor;");
    sharePrefsEditor.callObjectMethod("putString",
                                      "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/SharedPreferences$Editor;",
                                      QAndroidJniObject::fromString(key).object(),
                                      QAndroidJniObject::fromString(value).object());
    sharePrefsEditor.callMethod<void>("apply","()V");
}

void SharedPreferencesHelper::setInt(QString key, int value)
{
    QAndroidJniObject sharePrefsEditor = m_sharePrefs.callObjectMethod("edit",
                                                                       "()Landroid/content/SharedPreferences$Editor;");
    sharePrefsEditor.callObjectMethod("putInt",
                                      "(Ljava/lang/String;I)Landroid/content/SharedPreferences$Editor;",
                                      QAndroidJniObject::fromString(key).object(),
                                      value);
    sharePrefsEditor.callMethod<void>("apply",
                                      "()V");
}

bool SharedPreferencesHelper::contain(QString key)
{
    bool contain = m_sharePrefs.callMethod<jboolean>("contains",
                                             "(Ljava/lang/String;)Z",
                                             QAndroidJniObject::fromString(key).object());
    return contain;
}
