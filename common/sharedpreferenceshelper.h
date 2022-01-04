#ifndef SHAREDPREFERENCESHELPER_H
#define SHAREDPREFERENCESHELPER_H

#include <QAndroidJniObject>

#define DEFAULT_INT -1000

class SharedPreferencesHelper
{
public:
    SharedPreferencesHelper(QString fileName);

    void remove(QString key);

    QString getString(QString key, QString defaultValue = "");
    int getInt(QString key, int defaultValue = DEFAULT_INT);

    void setString(QString key, QString value);
    void setInt(QString key, int value);

    bool contain(QString key);

private:
    QAndroidJniObject m_sharePrefs;
};

#endif // SHAREDPREFERENCESHELPER_H
