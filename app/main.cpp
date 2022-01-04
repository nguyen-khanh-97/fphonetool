#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appmain.h"
#include <QtAndroid>
#include "../utils/log.h"
#include <QThread>
#include <QDebug>
#include "asblservicecommunication.h"

#include <CkGlobal.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>

static  CkGlobal glob;
bool unlockChilkat() {
    LOGD("unlockChilkat");
    CkGlobal glob;
    bool success_global = glob.UnlockBundle("AUTFRM.CB4082023_Pz2Ry7az86p4");
    if (success_global != true) {
        LOGD("Error: %s", glob.lastErrorText());
        return false;
    }

    int status = glob.get_UnlockStatus();
    if (status == 2) {
        LOGD("Unlocked using purchased unlock code.");
    } else {
        LOGD("Unlocked in trial mode.");
    }
    return true;
}

bool requestAndroidPermissions(){
    LOGD("");
    //Request requiered permissions at runtime

    const QVector<QString> permissions({"android.permission.READ_CONTACTS",
                                        "android.permission.WRITE_CONTACTS",
                                        "android.permission.WRITE_EXTERNAL_STORAGE",
                                        "android.permission.READ_PHONE_STATE",
                                        "android.permission.CAMERA",
                                        "android.permission.ACCESS_WIFI_STATE",
                                        "android.permission.CHANGE_WIFI_STATE",
                                        "android.permission.GET_ACCOUNTS"});

    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    LOGD("QtAndroidService starting from libf-phone.so");
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QGuiApplication app(argc, argv);

    if(!requestAndroidPermissions())
        return -1;

    unlockChilkat();
    LogHelper::getInstance();

    QQmlApplicationEngine engine;
    AppMain app_main(&engine);

    app_main.initAplication();

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
