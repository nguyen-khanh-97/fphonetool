#ifndef LOG_H
#define LOG_H

#include <errno.h>
#include <QDebug>
#include <QJsonObject>
#include <CkHttp.h>
#include <QThread>

#ifdef __OLD_LOG__

//#ifdef ANDROID

#ifndef LOG_TAG
#define LOG_TAG __FUNCTION__
#endif

#include <android/log.h>

#define D LOGD
#define E LOGE

//#ifdef DEBUG_MODE
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)
#define QTLOGD qDebug() << "Thread [" << QThread::currentThread() << "]: "
//#else
//#define LOGV(...)
//#define LOGD(...)
//#define LOGI(...)
//#define LOGW(...)
//#define LOGE(...)
//#endif

//#else /* ANDROID */

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>

//#if DEBUG == 1

//#define LOG_FUNCTION_NAME \
//    fprintf(stderr, "\033[0;1;31m__func__: %s\033[0;0m\n", __FUNCTION__);

//#else

//#define LOG_FUNCTION_NAME

//#endif

//static void
//D(const char *msg, ...)
//{
//    va_list ap;

//    va_start (ap, msg);
//    vfprintf(stdout, msg, ap);
//    fprintf(stdout, "\n");
//    va_end (ap);
//    fflush(stdout);
//}

//static void
//E(const char *msg, ...)
//{
//    va_list ap;

//    va_start (ap, msg);
//    vfprintf(stderr, msg, ap);
//    fprintf(stderr, ", %s", strerror(errno));
//    fprintf(stderr, "\n");
//    va_end (ap);
//}

//#endif /* ANDROID */

#else
#define LOGD(...) qDebug(__VA_ARGS__)
#define LOGE(...) qDebug(__VA_ARGS__)
#define QTLOGD qDebug() << "Thread [" << QThread::currentThread() << "] "

#endif

class LogHelper
{
private:
    static LogHelper* instance;

    LogHelper();
    ~LogHelper();

    static void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static bool initCkHttp(CkHttp& http);

public:
    static LogHelper* getInstance();
    static void deleteInstance();

    void initialize();
    void writeLog(QtMsgType type, const QString &msg);

    void setupDevice(QString device, QString appVersion);
    void setToken(QString token);

private:
    bool m_initialize = false;
    QString m_device;
    QString m_appVersion;
    QString m_token;

    CkHttp m_http;
    QJsonObject m_dataForm;

};

#endif // LOG_H
