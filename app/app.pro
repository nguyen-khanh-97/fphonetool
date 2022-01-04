QT += quick core androidextras remoteobjects

TARGET = F-Phone-Tool

CONFIG += c++11

INCLUDEPATH += $$PWD/../common/chilkat-9.5.0-android-cpp/include

LIBS += -L$$PWD/../common/chilkat-9.5.0-android-cpp/libs/$$QT_ARCH/ -lchilkatAndroid

SOURCES += \
        appmain.cpp \
        ../utils/log.cpp \
        asblservicecommunication.cpp \
        main.cpp

ANDROID_ABIS += armeabi-v7a arm64-v8a

HEADERS += \
    appmain.h \
    ../utils/log.h \
    asblservicecommunication.h

include(../common/common.pri)

REPC_REPLICA += ../common/qtandroidasblservice.rep

RESOURCES += qml.qrc

TRANSLATIONS += \
    f-phone_en_US.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/colors.xml \
    android/res/values/colors.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values/styles.xml \
    android/res/xml/accessibility_service.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/qtproject/fphonetool/activity/MainActivity.java \
    android/src/org/qtproject/fphonetool/service/QAccessibilityService.java \
    android/src/org/qtproject/qt5/android/CursorHandle.java \
    android/src/org/qtproject/qt5/android/EditContextView.java \
    android/src/org/qtproject/qt5/android/EditPopupMenu.java \
    android/src/org/qtproject/qt5/android/ExtractStyle.java \
    android/src/org/qtproject/qt5/android/QtActivityDelegate.java \
    android/src/org/qtproject/qt5/android/QtEditText.java \
    android/src/org/qtproject/qt5/android/QtInputConnection.java \
    android/src/org/qtproject/qt5/android/QtLayout.java \
    android/src/org/qtproject/qt5/android/QtMessageDialogHelper.java \
    android/src/org/qtproject/qt5/android/QtNative.java \
    android/src/org/qtproject/qt5/android/QtNativeLibrariesDir.java \
    android/src/org/qtproject/qt5/android/QtServiceDelegate.java \
    android/src/org/qtproject/qt5/android/QtSurface.java \
    android/src/org/qtproject/qt5/android/QtThread.java \
    android/src/org/qtproject/qt5/android/accessibility/QtAccessibilityDelegate.java \
    android/src/org/qtproject/qt5/android/accessibility/QtNativeAccessibility.java \
    android/src/org/qtproject/qt5/android/bearer/QtNetworkReceiver.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivityLoader.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtLoader.java \
    android/src/org/qtproject/qt5/android/bindings/QtService.java \
    android/src/org/qtproject/qt5/android/bindings/QtServiceLoader.java \
    android/src/org/qtproject/qt5/android/extras/QtAndroidBinder.java \
    android/src/org/qtproject/qt5/android/extras/QtAndroidServiceConnection.java \
    android/src/org/qtproject/qt5/android/extras/QtNative.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

CONFIG(debug, debug|release) {
    message("App: Debug Mode")
    DEFINES += __DEBUG_MODE__
} else {
    message("App: Release Mode")
    DEFINES += __RELEASE_MODE__
    DEFINES += QT_MESSAGELOGCONTEXT
}
