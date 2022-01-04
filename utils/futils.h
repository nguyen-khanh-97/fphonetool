#ifndef FUTILS_H
#define FUTILS_H

#include <QString>
#include <QDebug>
#include <QThread>
#include <QtAndroid>
#include <QAndroidIntent>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QVariant>
#include <qfile.h>
#include "log.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QTextStream>
#include "../service/wrapper/qaccessibilitynodeinfo.h"
#include <QProcess>
#include <../service/wrapper/qaccessibilityservice.h>
#include <CkCrypt2.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>

class FUtils{
public:
    enum Duration {
        SHORT = 0,
        LONG = 1
    };

    static void delay(int ms) {
        QThread::msleep(ms);
    }

    static void delayRandom(int start,int end) {
        QThread::msleep(randomRange(start,end));
    }

    static int randomRange(int start,int end) {
        QRandomGenerator random;
        return rand()%(end - start + 1) + start;
    }

    static void openWirelessSettings() {
        QAndroidIntent intent = QAndroidIntent("android.settings.WIRELESS_SETTINGS");
        intent.handle().callObjectMethod("setFlags","(I)Landroid/content/Intent;",32768 | 268435456 | 4);
        QtAndroid::androidContext().callMethod<void>("startActivity", "(Landroid/content/Intent;)V",intent.handle().object<jobject>());
    }

    static void openAppInfo(QString packageName) {
        QAndroidIntent intent = QAndroidIntent("android.settings.APPLICATION_DETAILS_SETTINGS");
        QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod("android/net/Uri","parse","(Ljava/lang/String;)Landroid/net/Uri;",QAndroidJniObject::fromString("package:" + packageName).object());
        intent.handle().callObjectMethod("setData","(Landroid/net/Uri;)Landroid/content/Intent;",uri.object());
        intent.handle().callObjectMethod("setFlags","(I)Landroid/content/Intent;",32768 | 268435456 | 4);
        QtAndroid::androidContext().callMethod<void>("startActivity", "(Landroid/content/Intent;)V",intent.handle().object<jobject>());
    }

    static void openPackage(QString packageName) {
        if(isPackageInstalled(packageName)){
            QAndroidJniObject pm = QtAndroid::androidContext().callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
            QAndroidJniObject intentObj = pm.callObjectMethod("getLaunchIntentForPackage", "(Ljava/lang/String;)Landroid/content/Intent;",QAndroidJniObject::fromString(packageName).object<jstring>());
            QtAndroid::androidContext().callMethod<void>("startActivity", "(Landroid/content/Intent;)V",intentObj.object<jobject>());
        }else{
            LOGD("FUtils:openPackage: package not installer %s",packageName.toUtf8().data());
        }
    }

    static void openDeeplink(QString packageName,QString url) {
        QAndroidIntent intent = QAndroidIntent("android.intent.action.VIEW");
        QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod("android/net/Uri","parse","(Ljava/lang/String;)Landroid/net/Uri;",QAndroidJniObject::fromString(url).object());
        intent.handle().callObjectMethod("setData","(Landroid/net/Uri;)Landroid/content/Intent;",uri.object());
        intent.handle().callObjectMethod("setPackage","(Ljava/lang/String;)Landroid/content/Intent;",QAndroidJniObject::fromString(packageName).object());
        intent.handle().callObjectMethod("setFlags","(I)Landroid/content/Intent;",32768 | 268435456 | 4);
        QtAndroid::androidContext().callMethod<void>("startActivity", "(Landroid/content/Intent;)V",intent.handle().object<jobject>());
    }

    static bool click(int x, int y, bool longPress) {
        QAndroidJniObject clickPath("android/graphics/Path");
        clickPath.callMethod<void>("moveTo","(FF)V",(jfloat)x, (jfloat)y);

        QRandomGenerator rand ;
        int pointCount  = rand.bounded(3) + 1;
        for (int i = 0; i < pointCount; i++) {
            clickPath.callMethod<void>("lineTo","(FF)V",(jfloat)(x + rand.bounded(6) - 3), (jfloat)(y + rand.bounded(6) - 3));
        }

        QAndroidJniEnvironment jniEnv;
        QAndroidJniObject gestureBuilder("android/accessibilityservice/GestureDescription$Builder");
        QAndroidJniObject strokeDescription("android/accessibilityservice/GestureDescription$StrokeDescription","(Landroid/graphics/Path;JJ)V",clickPath.object<jobject>(), (jlong)0,(jlong)(longPress? 1000 : 100));
        QAndroidJniObject builder = gestureBuilder.callObjectMethod("addStroke", "(Landroid/accessibilityservice/GestureDescription$StrokeDescription;)"
                                                     "Landroid/accessibilityservice/GestureDescription$Builder;",strokeDescription.object<jobject>());
        QAndroidJniObject gestureDescription = gestureBuilder.callObjectMethod("build", "()Landroid/accessibilityservice/GestureDescription;");

        return static_cast<bool>(QAccessibilityService::instance()->jniObject()->callMethod<jboolean>("dispatchGesture", "(Landroid/accessibilityservice/GestureDescription;"
                                                                                  "Landroid/accessibilityservice/AccessibilityService$GestureResultCallback;"
                                                                                  "Landroid/os/Handler;)Z",gestureDescription.object<jobject>(),nullptr,nullptr));
    }

    static bool double_click(int x, int y) {
        QAndroidJniObject clickPath("android/graphics/Path");
        clickPath.callMethod<void>("moveTo","(FF)V",(jfloat)x, (jfloat)y);

        QRandomGenerator rand ;
        int pointCount  = rand.bounded(3) + 1;
        for (int i = 0; i < pointCount; i++) {
            clickPath.callMethod<void>("lineTo","(FF)V",(jfloat)(x + rand.bounded(6) - 3), (jfloat)(y + rand.bounded(6) - 3));
        }

        QAndroidJniEnvironment jniEnv;
        QAndroidJniObject gestureBuilder("android/accessibilityservice/GestureDescription$Builder");
        QAndroidJniObject strokeDescription("android/accessibilityservice/GestureDescription$StrokeDescription","(Landroid/graphics/Path;JJ)V",clickPath.object<jobject>(), (jlong)0,(jlong)(100));
        QAndroidJniObject builder = gestureBuilder.callObjectMethod("addStroke", "(Landroid/accessibilityservice/GestureDescription$StrokeDescription;)"
                                                     "Landroid/accessibilityservice/GestureDescription$Builder;",strokeDescription.object<jobject>());
        QAndroidJniObject gestureDescription = gestureBuilder.callObjectMethod("build", "()Landroid/accessibilityservice/GestureDescription;");

        bool touchFirst = static_cast<bool>(QAccessibilityService::instance()->jniObject()->callMethod<jboolean>("dispatchGesture", "(Landroid/accessibilityservice/GestureDescription;"
                                                                                  "Landroid/accessibilityservice/AccessibilityService$GestureResultCallback;"
                                                                                  "Landroid/os/Handler;)Z",gestureDescription.object<jobject>(),nullptr,nullptr));
        delay(200);

        bool touchSecond = static_cast<bool>(QAccessibilityService::instance()->jniObject()->callMethod<jboolean>("dispatchGesture", "(Landroid/accessibilityservice/GestureDescription;"
                                                                                  "Landroid/accessibilityservice/AccessibilityService$GestureResultCallback;"
                                                                                  "Landroid/os/Handler;)Z",gestureDescription.object<jobject>(),nullptr,nullptr));

        return touchFirst & touchSecond;
    }

    static QString getPackageName(){
        QAndroidJniObject packageManager = QAccessibilityService::instance()->jniObject()->callObjectMethod(
                                                    "getPackageName",
                                                    "()Ljava/lang/String;");
        return packageManager.toString();
    }

    static QString getDeviceId(){
//        QString deviceId = runCommand("getprop ro.ril.oem.imei").replace("\n","");

//        if(deviceId.isEmpty() || deviceId == "" || deviceId.length() > 20){
//            deviceId = runCommand("getprop ro.ril.miui.imei0").replace("\n","");;
//        }

//        if(deviceId.isEmpty() || deviceId == "" || deviceId.length() > 20){
//            deviceId = runCommand("getprop ro.serialno").replace("\n","");;
//        }

//        if(deviceId.isEmpty() || deviceId == "" || deviceId.length() > 20){
//            deviceId = runCommand("getprop ro.serialno").replace("\n","");;
//        }

//        if(deviceId.isEmpty() || deviceId == "" || deviceId.length() > 20){
//            deviceId = runCommand("getprop ro.boot.serialno").replace("\n","");;
//        }
          QString deviceId;

        if(deviceId.isEmpty() || deviceId == "" || deviceId.length() > 20){
            QAndroidJniObject cr = QAccessibilityService::instance()->jniObject()->callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
            deviceId =  QAndroidJniObject::callStaticObjectMethod("android/provider/Settings$Secure","getString", "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;",
                                                               cr.object<jobject>(),
                                                               QAndroidJniObject::fromString("android_id").object<jobject>()).toString();
        }

        return deviceId.replace("\n","");
    }

    static bool canRequestPackageInstalls(){
        QAndroidJniObject packageManager = QAccessibilityService::instance()->jniObject()->callObjectMethod("getPackageManager","()Landroid/content/pm/PackageManager;");

        return static_cast<bool>(packageManager.callMethod<jboolean>("canRequestPackageInstalls","()Z"));
    }

    static bool swipe(int x1, int y1, int x2, int y2, int time) {
        QAndroidJniObject clickPath("android/graphics/Path");
        clickPath.callMethod<void>("moveTo","(FF)V",(jfloat)x1, (jfloat)y1);
        clickPath.callMethod<void>("lineTo","(FF)V",(jfloat)x2, (jfloat)y2);

        QAndroidJniEnvironment jniEnv;
        QAndroidJniObject gestureBuilder("android/accessibilityservice/GestureDescription$Builder");
        QAndroidJniObject strokeDescription("android/accessibilityservice/GestureDescription$StrokeDescription","(Landroid/graphics/Path;JJ)V",clickPath.object<jobject>(), (jlong)0,(jlong) time);
        QAndroidJniObject builder = gestureBuilder.callObjectMethod("addStroke", "(Landroid/accessibilityservice/GestureDescription$StrokeDescription;)"
                                                     "Landroid/accessibilityservice/GestureDescription$Builder;",strokeDescription.object<jobject>());
        QAndroidJniObject gestureDescription = gestureBuilder.callObjectMethod("build", "()Landroid/accessibilityservice/GestureDescription;");

        bool status =  static_cast<bool>(QAccessibilityService::instance()->jniObject()->callMethod<jboolean>("dispatchGesture", "(Landroid/accessibilityservice/GestureDescription;"
                                                                                  "Landroid/accessibilityservice/AccessibilityService$GestureResultCallback;"
                                                                                  "Landroid/os/Handler;)Z",gestureDescription.object<jobject>(),nullptr,nullptr));

        FUtils::delay(time);

        return status;
    }

    static void inputText(QString text,bool delay) {
        QAccessibilityNodeInfo root = QAccessibilityService::instance()->getRootInActiveWindow();
        if(root.isValid()) {
            LOGD("FUtils::inputText ---> %s",text.toUtf8().data());
            QAccessibilityNodeInfo focus = root.findFocus(1);
            if(focus.isValid() && focus.isFocused()) {
                QAndroidJniObject arguments("android/os/Bundle");
                if(delay){
                    QString append;
                    for(int i=0; i < text.length(); i++){
                        append = append + text.at(i);
                        arguments.callMethod<void>("putString","(Ljava/lang/String;Ljava/lang/String;)V",
                                                   QAndroidJniObject::fromString("ACTION_ARGUMENT_SET_TEXT_CHARSEQUENCE").object(),
                                                   QAndroidJniObject::fromString(append).object());
                        focus.performAction(2097152,arguments);
                        delayRandom(100,500);
                    }
                }else {
                    arguments.callMethod<void>("putString","(Ljava/lang/String;Ljava/lang/String;)V", QAndroidJniObject::fromString("ACTION_ARGUMENT_SET_TEXT_CHARSEQUENCE").object(), QAndroidJniObject::fromString(text).object());
                    focus.performAction(2097152,arguments);
                }
            }
        }
    }

    static void inputText(QString text) {
        inputText(text,true);
    }

    static bool back() {
        return QAccessibilityService::instance()->performGlobalAction(QAccessibilityService::GLOBAL_ACTION::GLOBAL_ACTION_BACK);
    }

    static bool home() {
        return QAccessibilityService::instance()->performGlobalAction(QAccessibilityService::GLOBAL_ACTION::GLOBAL_ACTION_HOME);
    }

    static QString tOTP(const char * secretkey) {
        QString result;
        if(secretkey) {
            CkCrypt2 crypt;
            result = crypt.totp(secretkey,"base32","0","",30,6,-1,"sha1");
        }
        return result;
    }

    static bool scrollForward2(){
        static QSize screenSize = QAccessibilityService::instance()->getScreenSize();

        int x = randomRange(1,screenSize.width());

        FUtils::swipe(x,randomRange(3*screenSize.height()/5,4*screenSize.height()/5),x + randomRange(1,10),randomRange(screenSize.height()/5,2*screenSize.height()/5),750);
        return true;
    }

    static bool scrollForward(){
        return scrollForward(QAccessibilityService::instance()->getRootInActiveWindow());
    }

    static bool scrollForward(QAccessibilityNodeInfo nodeInfo){
        if(nodeInfo.isValid()){
            if(nodeInfo.isValid() && nodeInfo.isScrollable()) {
                return nodeInfo.performAction(0x00001000);
            }

            for(int i=0; i < nodeInfo.getChildCount(); i++){
                if (scrollForward(nodeInfo.getChild(i))) {
                    return true;
                }
            }
        }
        return false;
    }

    static bool scrollBackward2(){
        static QSize screenSize = QAccessibilityService::instance()->getScreenSize();

        int x = randomRange(1,screenSize.width());

        FUtils::swipe(x,randomRange(screenSize.height()/5,2*screenSize.height()/5),x + randomRange(1,10),randomRange(3*screenSize.height()/5,4*screenSize.height()/5),750);
        return true;
    }
        static bool scrollBackward(){
        return scrollBackward(QAccessibilityService::instance()->getRootInActiveWindow());
    }

    static bool scrollBackward(QAccessibilityNodeInfo nodeInfo){
        if(nodeInfo.isValid()){
            if(nodeInfo.isValid() && nodeInfo.isScrollable()) {
                return nodeInfo.performAction(0x00002000);
            }

            for(int i=0; i < nodeInfo.getChildCount(); i++){
                if (scrollForward(nodeInfo.getChild(i))) {
                    return true;
                }
            }
        }
        return false;
    }

    static QString runCommand(QString command){
        QProcess process;
        process.start(command);
        process.waitForFinished(10000);
        return process.readAll().data();
    }

    static bool isRunningProcess(QString packageName){
        QAndroidJniObject packageManager = QAccessibilityService::instance()->jniObject()->callObjectMethod("getPackageManager","()Landroid/content/pm/PackageManager;");
        QAndroidJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo",
                                                                            "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;",
                                                                            QAndroidJniObject::fromString(packageName).object<jobject>(),
                                                                            0);

        return (static_cast<int>(applicationInfo.getField<jint>("flags")) & 2097152) == 0;
    }

    static bool isAirplaneModeOn(){
        QAndroidJniObject cr = QAccessibilityService::instance()->jniObject()->callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
        jint test = QAndroidJniObject::callStaticMethod<jint>("android/provider/Settings$Global","getInt", "(Landroid/content/ContentResolver;Ljava/lang/String;I)I",
                                                           cr.object<jobject>(),
                                                           QAndroidJniObject::fromString("airplane_mode_on").object<jobject>(),
                                                           0);
        return static_cast<int>(test) != 0;
    }

    static QString readFile(QString filePath){

        QAndroidJniObject fileContent = QAndroidJniObject::callStaticObjectMethod(
                    "org/qtproject/fphonetool/service/QAccessibilityService",
                    "readFile",
                    "(Ljava/lang/String;)Ljava/lang/String;",
                    QAndroidJniObject::fromString(filePath).object<jobject>());

        QAndroidJniEnvironment jniEnv;
        jstring test = fileContent.object<jstring>();
        const char *nativeString = jniEnv->GetStringUTFChars(test, 0);
        QString fileContentStr = QString(nativeString);
        jniEnv->ReleaseStringUTFChars(test, nativeString);
        return fileContentStr;
    }

    static bool isPackageInstalled(QString packageName){
        jboolean isPackageInstalled = QAndroidJniObject::callStaticMethod<jboolean>(
                    "org/qtproject/fphonetool/service/QAccessibilityService",
                    "isPackageInstalled",
                    "(Ljava/lang/String;)Z",
                    QAndroidJniObject::fromString(packageName).object<jobject>());
        return static_cast<bool>(isPackageInstalled);
    }

    static bool isNetworkConnected(){
        CkHttp http;
        http.put_ReadTimeout(2);
        http.put_ConnectTimeout(2);
        const char *result = http.quickGetStr("https://www.google.com/");
        if (http.get_LastMethodSuccess()) {
            if(result) {
                int length = strlen(result);
                if(length > 0){
                    return true;
                }
            }
        }
        return false;
    }

    static bool writeFile(QString filePath,QString content){
        QFile outputFile(filePath);
        outputFile.open(QIODevice::WriteOnly);

        if(!outputFile.isOpen()){
            return false;
        }

        QTextStream outStream(&outputFile);
        outStream << content;
        outputFile.close();

        return true;
    }

    static void openInstallAPK(QString filePath){
        QAndroidJniObject::callStaticMethod<void>(
                            "org/qtproject/fphonetool/service/QAccessibilityService",
                            "openInstallAPK",
                            "(Ljava/lang/String;)V",
                            QAndroidJniObject::fromString(filePath).object<jobject>());
    }

    static void showToast(QString message){
        QAndroidJniObject::callStaticMethod<void>(
                            "org/qtproject/fphonetool/service/QAccessibilityService",
                            "showToast",
                            "(Ljava/lang/String;)V",
                            QAndroidJniObject::fromString(message).object<jobject>());
    }

    static void openUnknownApp(){
        QAndroidJniObject::callStaticMethod<void>(
                            "org/qtproject/fphonetool/service/QAccessibilityService",
                            "openUnknownApp",
                            "()V");
    }

    static void setWifiEnable(bool enable){
        QAndroidJniObject wifiManager = QAccessibilityService::instance()->jniObject()->callObjectMethod(
                    "getSystemService",
                    "(Ljava/lang/String;)Ljava/lang/Object;", QAndroidJniObject::fromString("wifi").object<jstring>());

        wifiManager.callMethod<jboolean>(
                   "setWifiEnabled",
                   "(Z)Z",
                   enable);
    }

    static bool isWifiEnable(){
        QAndroidJniObject wifiManager = QAccessibilityService::instance()->jniObject()->callObjectMethod(
                    "getSystemService",
                    "(Ljava/lang/String;)Ljava/lang/Object;", QAndroidJniObject::fromString("wifi").object<jstring>());

        return static_cast<bool>(wifiManager.callMethod<jboolean>(
                                     "isWifiEnabled",
                                     "()Z"));
    }

    static QString toQString(QJsonObject jsonObject){
        QJsonDocument document;
        document.setObject(jsonObject);
        return document.toJson().replace("\n","").data();
    }

    static QString toQString(QJsonArray jsonArray){
        QJsonDocument document;
        document.setArray(jsonArray);
        return document.toJson().data();
    }

    static QString getVersionName(){
        return getVersionName(getPackageName());
    }

    static QString getVersionName(QString packageName){
        if(isPackageInstalled(packageName)){
            QAndroidJniObject packageManager = QAccessibilityService::instance()->jniObject()->callObjectMethod(
                                                        "getPackageManager",
                                                        "()Landroid/content/pm/PackageManager;");
            QAndroidJniObject packageInfo = packageManager.callObjectMethod(
                                                        "getPackageInfo",
                                                        "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;",
                                                        QAndroidJniObject::fromString(packageName).object<jobject>(),
                                                        0);

            return packageInfo.getObjectField("versionName","Ljava/lang/String;").toString();
        }
        return "";
    }

     static int getVersionCode(){
         return getVersionCode(getPackageName());
     }

    static int getVersionCode(QString packageName){
        if(isPackageInstalled(packageName)){
            QAndroidJniObject packageManager = QAccessibilityService::instance()->jniObject()->callObjectMethod(
                                                        "getPackageManager",
                                                        "()Landroid/content/pm/PackageManager;");
            QAndroidJniObject packageInfo = packageManager.callObjectMethod(
                                                        "getPackageInfo",
                                                        "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;",
                                                        QAndroidJniObject::fromString(packageName).object<jobject>(),
                                                        0);

            return packageInfo.getField<jint>("versionCode");
        }
        return 0;
    }
};

#endif // FUTILS_H

