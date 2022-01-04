TEMPLATE = lib
TARGET = service
CONFIG += dll
QT += core androidextras remoteobjects

INCLUDEPATH += $$PWD/../utils
INCLUDEPATH += $$PWD/../common/chilkat-9.5.0-android-cpp/include

LIBS += -L$$PWD/../common/chilkat-9.5.0-android-cpp/libs/$$QT_ARCH/ -lchilkatAndroid

#fitty.one lib
CONFIG(debug, debug|release) {
    message("debug mode")
    LIBS += -L$$PWD/../common/fity.one-api/f-android/libs/debug/$$QT_ARCH -lfandroid.fityone
    DEFINES += __DEBUG_MODE__
}else {
    message("release mode")
    LIBS += -L$$PWD/../common/fity.one-api/f-android/libs/release/$$QT_ARCH -lfandroid.fityone
    DEFINES += __RELEASE_MODE__
    DEFINES += QT_MESSAGELOGCONTEXT
}
INCLUDEPATH += $$PWD/../common/fity.one-api/f-android/include

ANDROID_ABIS += armeabi-v7a arm64-v8a


SOURCES += \
    ../utils/log.cpp \
    service_main.cpp \
    appcommunition.cpp \
    appinfo.cpp \
    jsonparserengine.cpp \
    servicemain.cpp \
    screendefine/screendefine.cpp \
    wrapper/qaccessibilityaction.cpp \
    wrapper/qaccessibilitynodeinfo.cpp \
    wrapper/qaccessibilityservice.cpp \
    wrapper/qaccessibilitywindowinfo.cpp \
    wrapper/qaesencryption.cpp \
    wrapper/qtwrapper.cpp

HEADERS += \
    ../utils/futils.h \
    ../utils/log.h \
    appcommunition.h \
    appinfo.h \
    jsonparserengine.h \
    servicemain.h \
    screendefine/screendefine.h \
    wrapper/qaccessibilityaction.h \
    wrapper/qaccessibilitynodeinfo.h \
    wrapper/qaccessibilityservice.h \
    wrapper/qaccessibilitywindowinfo.h \
    wrapper/qaesencryption.h \
    wrapper/qtwrapper.h

include(../common/common_ro.pri)

REPC_SOURCE += ../common/qtandroidasblservice.rep

RESOURCES += resource.qrc

CONFIG(debug, debug|release) {
    message("Service: Debug Mode")
    DEFINES += DEBUG_MODE
}
