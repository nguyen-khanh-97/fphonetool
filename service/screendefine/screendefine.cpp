#include "screendefine.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QString>
#include <QScreen>
#include <QGuiApplication>
#include <wrapper/qaccessibilitynodeinfo.h>
#include <wrapper/qaccessibilityservice.h>
#include <cstdlib>
#include <jsonparserengine.h>
#include "futils.h"


Screendefine* Screendefine::s_Instance = nullptr;
Screendefine *Screendefine::instance(){
    if(s_Instance == nullptr) {
        s_Instance = new Screendefine();
    }
    return s_Instance;
}

Screendefine::Screendefine() : QObject(nullptr) {
    QFile file(":/resouce/ScreenDefine.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        screenInfinity_local = QJsonDocument::fromJson(file.readAll()).array();
        FUtils::writeFile("/sdcard/definition_local.txt",QJsonDocument(screenInfinity_local).toJson(QJsonDocument::Indented));
    }
}

QJsonArray Screendefine::screentElements(){
    QJsonArray screenElements;
    QList<QAccessibilityWindowInfo> windows = QAccessibilityService::instance()->getWindows();
    if(windows.size() > 0) {
        for(QAccessibilityWindowInfo window : windows){
            if(window.isValid() && window.isFocused()){
                QAccessibilityNodeInfo root = window.getRoot();
                if(root.isValid()){
                    Screendefine::instance()->findAndDefineScreenElement(screenElements,root);
                }
            }
        }
    }
    return screenElements;
}

void Screendefine::findAndDefineScreenElement(QJsonArray& screenElements, QAccessibilityNodeInfo& nodeInfo){
    if(nodeInfo.isValid()){
        QRect location = Screendefine::getLocationFromNode(nodeInfo);

        if( !location.isEmpty()){
            QJsonObject screenInfoObject = QJsonObject();
            screenInfoObject.insert("x",location.x());
            screenInfoObject.insert("y",location.y());
            screenInfoObject.insert("width",location.width());
            screenInfoObject.insert("height",location.height());
            screenInfoObject.insert("contentDescription",!nodeInfo.getContentDescription().isNull() ? nodeInfo.getContentDescription() : "null");
            screenInfoObject.insert("hintText",!nodeInfo.getHintText().isNull() ? nodeInfo.getHintText() : "null");
            screenInfoObject.insert("isCheckable",nodeInfo.isCheckable());
            screenInfoObject.insert("isChecked",nodeInfo.isChecked());
            screenInfoObject.insert("isClickable",nodeInfo.isClickable());
            screenInfoObject.insert("isEnabled",nodeInfo.isEnabled());
            screenInfoObject.insert("isFocusable",nodeInfo.isFocusable());
            screenInfoObject.insert("isFocused",nodeInfo.isFocused());
            screenInfoObject.insert("isPassword",nodeInfo.isPassword());
            screenInfoObject.insert("isScrollable",nodeInfo.isScrollable());
            screenInfoObject.insert("isSelected",nodeInfo.isSelected());
            screenInfoObject.insert("isVisibleToUser",nodeInfo.isVisibleToUser());
            screenInfoObject.insert("packageName",!nodeInfo.getPackageName().isNull() ? nodeInfo.getPackageName() : "null");
            screenInfoObject.insert("text",!nodeInfo.getText().isNull() ? nodeInfo.getText() : "null");
            screenInfoObject.insert("className",!nodeInfo.getClassName().isNull() ? nodeInfo.getClassName() : "");
            screenInfoObject.insert("keyword",QJsonValue::Null);
            screenInfoObject.insert("resourceName",!nodeInfo.getViewIdResourceName().isNull() ? nodeInfo.getViewIdResourceName() : "");

            screenElements.append(screenInfoObject);
        }

        for(int i=0; i < nodeInfo.getChildCount(); i++){
            QAccessibilityNodeInfo child = nodeInfo.getChild(i);
            this->findAndDefineScreenElement(screenElements,child);
        }
    }
}

QRect Screendefine::getLocationFromNode(QAccessibilityNodeInfo& nodeInfo){
    QRect rect = QRect();
    nodeInfo.getBoundsInScreen(rect);
    static QSize screenSize = QAccessibilityService::instance()->getScreenSize();
    if(!screenSize.isNull()) {
        if (rect.top() >= 0 && rect.top() <= screenSize.height() &&
                rect.left() >= 0 && rect.left() <= screenSize.width() &&
                rect.bottom() >= 0 && rect.bottom() <= screenSize.height() &&
                rect.right() >= 0 && rect.right() <= screenSize.width() &&
                rect.bottom() > rect.top() &&
                rect.right() > rect.left()) {
            return rect;
        }
    }
    return QRect();
}

QJsonObject Screendefine::getCurrentScreenInfo(){
    QJsonArray screenElement = this->screentElements();
    return this->getCurrentScreenInfo(screenElement);
}

QJsonObject Screendefine::getCurrentScreenInfo(QJsonArray& screentElements){

    QJsonObject screenInfo;
    for(int i=0; i < Screendefine::screenInfinity.size(); i++){

        QJsonObject screenInfinityInfo = Screendefine::screenInfinity.at(i).toObject();

        QString pageID = screenInfinityInfo.value("page").toString();
        QString appname = screenInfinityInfo.value("appname").toString();
        QJsonObject definitonsObj = screenInfinityInfo.value("definitons").toObject();

        for(QString language : definitonsObj.keys()){
            QJsonArray evidenceArray = definitonsObj.value(language).toArray();

            for(int t=0; t < evidenceArray.size(); t++){
                QJsonArray oneOfEvidence = evidenceArray.at(t).toArray();

                if (!oneOfEvidence.isEmpty() && oneOfEvidence.size() > 0) {
                    if(Screendefine::instance()->isScreenMatch(oneOfEvidence,screentElements)){
                        QJsonObject _keyword = screenInfinityInfo.value("keywords").toObject();
                        QJsonArray keyworkForLanguage = _keyword.value(language).toArray();

                        findAndDefineKeyword(keyworkForLanguage,screentElements);

                        screenInfo.insert("screen_id", pageID);
                        screenInfo.insert("language", language);
                        screenInfo.insert("info", screentElements);

                        LOGD("Element Json: %s",pageID.toUtf8().data());
                        FUtils::writeFile("/sdcard/FPhoneScreenLog.txt",QJsonDocument(screenInfo).toJson(QJsonDocument::Indented));

                        return screenInfo;
                    }
                }
            }
        }
    }
//    for(int i=0; i < Screendefine::screenInfinity_local.size(); i++){

//        QJsonObject screenInfinityInfo = Screendefine::screenInfinity_local.at(i).toObject();

//        QString pageID = screenInfinityInfo.value("page").toString();
//        QString appname = screenInfinityInfo.value("appname").toString();
//        QJsonObject definitonsObj = screenInfinityInfo.value("definitons").toObject();

//        for(QString language : definitonsObj.keys()){
//            QJsonArray evidenceArray = definitonsObj.value(language).toArray();

//            for(int t=0; t < evidenceArray.size(); t++){
//                QJsonArray oneOfEvidence = evidenceArray.at(t).toArray();

//                if (!oneOfEvidence.isEmpty() && oneOfEvidence.size() > 0) {
//                    if(Screendefine::instance()->isScreenMatch(oneOfEvidence,screentElements)){
//                        QJsonObject _keyword = screenInfinityInfo.value("keywords").toObject();
//                        QJsonArray keyworkForLanguage = _keyword.value(language).toArray();

//                        findAndDefineKeyword(keyworkForLanguage,screentElements);

//                        screenInfo.insert("screen_id", pageID);
//                        screenInfo.insert("language", language);
//                        screenInfo.insert("info", screentElements);

//                        LOGD("Element Json Local: %s",pageID.toUtf8().data());
//                        FUtils::writeFile("/sdcard/FPhoneScreenLog.txt",QJsonDocument(screenInfo).toJson(QJsonDocument::Indented));

//                        return screenInfo;
//                    }
//                }
//            }
//        }
//    }



    screenInfo.insert("screen_id", "SCREEN_UNKNOWN");
    screenInfo.insert("info", screentElements);

    QJsonDocument jsonDoc(screenInfo.value("info").toArray());
    LOGD("Element Json: %s","SCREEN_UNKNOWN");
    FUtils::writeFile("/sdcard/FPhoneScreenLog.txt",jsonDoc.toJson(QJsonDocument::Indented));
    // capture screen to "/sdcard/FPhoneScreenShot.png"
    FUtils::writeFile("/sdcard/definition.txt",QJsonDocument(screenInfinity).toJson(QJsonDocument::Indented));

    return screenInfo;
}

void Screendefine::findAndDefineKeyword(QJsonArray& keywords, QJsonArray& screentElements){
    for(int i=0; i < keywords.size(); i++){
        QJsonObject keyword = keywords.at(i).toObject();

        for(int j=0; j < screentElements.size(); j++){
            QJsonObject screentElement = screentElements.at(j).toObject();

            if (keyword.value("contentDescription").toString().toLower() == screentElement.value("contentDescription").toString().toLower() &&
                    keyword.value("text").toString().toLower() == screentElement.value("text").toString().toLower() &&
                    keyword.value("className").toString().toLower() == screentElement.value("className").toString().toLower() &&
                    keyword.value("checked").toBool() == screentElement.value("isChecked").toBool() &&
                    keyword.value("clickable").toBool() == screentElement.value("isClickable").toBool() &&
                    keyword.value("selected").toBool() == screentElement.value("isSelected").toBool()) {

                if(!keyword.value("keyword").toString().isEmpty()){
                    screentElement.insert("keyword",keyword.value("keyword").toString());

                    screentElements.replace(j,screentElement);
                }
            }
        }
    }
}

void Screendefine::setScreenInfinity(QJsonArray screenInfi){
    screenInfinity = screenInfi;
}

bool Screendefine::isScreenMatch(QJsonArray& screenInfinitys,QJsonArray& screentElements){
    for(int e=0; e < screenInfinitys.size(); e++){
        if(!isElementMatch(screenInfinitys.at(e).toObject(),screentElements)){
            return false;
        }
    }
    return true;
}

bool Screendefine::isElementMatch(QJsonObject defineElement,QJsonArray& screentElements){
    QString eDefineDes          = defineElement.value("contentDescription").toString().toLower();
    QString eDefineText         = defineElement.value("text").toString().toLower();
    QString eDefineClassName    = defineElement.value("className").toString().toLower();
    bool eDefineChecked         = defineElement.value("checked").toBool();
    bool eDefineClickable       = defineElement.value("clickable").toBool();
    bool eDefineSelected        = defineElement.value("selected").toBool();

    for(int f=0; f < screentElements.size(); f++){
        QJsonObject screentElement = screentElements.at(f).toObject();
        QString eScreenDes = screentElement.value("contentDescription").toString().toLower();
        QString eScreenText = screentElement.value("text").toString().toLower();
        QString eScreenClassName = screentElement.value("className").toString().toLower();
        bool eScreenChecked = screentElement.value("isChecked").toBool();
        bool eScreenClickable = screentElement.value("isClickable").toBool();
        bool eScreenSelected = screentElement.value("isSelected").toBool();

        if (eScreenDes.contains(eDefineDes) &&
                eScreenText.contains(eDefineText) &&
                eScreenClassName == eDefineClassName &&
                eScreenChecked == eDefineChecked &&
                eScreenClickable == eDefineClickable &&
                eScreenSelected == eDefineSelected) {
            return true;
        }
    }
    return false;
}
