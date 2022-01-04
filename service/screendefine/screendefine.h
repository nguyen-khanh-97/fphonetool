#ifndef SCREENDEFINE_H
#define SCREENDEFINE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include "wrapper/qaccessibilitynodeinfo.h"
#include "futils.h"

#define SCREEN_UNKNOWN "SCREEN_UNKNOWN"
#define SCREEN_FACEBOOK_FACEBOOK_POLICY_ACCEPT "SCREEN_FACEBOOK_POLICY_ACCEPT"
#define SCREEN_FACEBOOK_LOGIN "SCREEN_FACEBOOK_LOGIN"
#define SCREEN_FACEBOOK_FACEBOOK_LOGGING_IN "SCREEN_FACEBOOK_LOGGING_IN"
#define SCREEN_FACEBOOK_FACEBOOK_LOGGING_OUT "SCREEN_FACEBOOK_LOGGING_OUT"
#define SCREEN_FACEBOOK_FACEBOOK_HOME "SCREEN_FACEBOOK_HOME"
#define SCREEN_FACEBOOK_FACEBOOK_WATCH_TAB "SCREEN_FACEBOOK_WATCH_TAB"
#define SCREEN_FACEBOOK_LOGGED_OUT "SCREEN_FACEBOOK_LOGGED_OUT"
#define SCREEN_FACEBOOK_FACEBOOK_STOP_SETTING_PROFILE "SCREEN_FACEBOOK_STOP_SETTING_PROFILE"
#define SCREEN_FACEBOOK_MENU "SCREEN_FACEBOOK_MENU"
#define SCREEN_FACEBOOK_SETTINGS "SCREEN_FACEBOOK_SETTINGS"
#define SCREEN_FACEBOOK_SETTINGS_PERSONAL_INFORMATION "SCREEN_FACEBOOK_SETTINGS_PERSONAL_INFORMATION"
#define SCREEN_FACEBOOK_SETTINGS_MANAGE_CONTACT_INFO "SCREEN_FACEBOOK_SETTINGS_MANAGE_CONTACT_INFO"
#define SCREEN_FACEBOOK_SETTINGS_ADD_MAIL "SCREEN_FACEBOOK_SETTINGS_ADD_MAIL"
#define SCREEN_FACEBOOK_SETTINGS_EMAIL_CONFIRM_CODE "SCREEN_FACEBOOK_SETTINGS_EMAIL_CONFIRM_CODE"
#define SCREEN_FACEBOOK_SECURITY_LOGIN "SCREEN_FACEBOOK_SECURITY&LOGIN"
#define SCREEN_FACEBOOK_FACEBOOK_CHANGE_PASSWORD "SCREEN_FACEBOOK_CHANGE_PASSWORD"
#define SCREEN_FACEBOOK_FACEBOOK_PASSWORD_CHANGED "SCREEN_FACEBOOK_PASSWORD_CHANGED"
#define SCREEN_FACEBOOK_FACEBOOK_LOGOUT_OTHER_DEVICES "SCREEN_FACEBOOK_LOGOUT_OTHER_DEVICES"
#define SCREEN_FACEBOOK_FACEBOOK_MEMBER_TOOLS "SCREEN_FACEBOOK_MEMBER_TOOLS"
#define SCREEN_FACEBOOK_FACEBOOK_LEAVE_GROUP_POPUP "SCREEN_FACEBOOK_LEAVE_GROUP_POPUP"
#define SCREEN_FACEBOOK_FACEBOOK_LEAVE_GROUP_REPORTS "SCREEN_FACEBOOK_LEAVE_GROUP_REPORTS"
#define SCREEN_FACEBOOK_2FA "SCREEN_FACEBOOK_2FA"
#define SCREEN_FACEBOOK_FACEBOOK_2FA_IS_ON "SCREEN_FACEBOOK_2FA_IS_ON"
#define SCREEN_FACEBOOK_FACEBOOK_2FA_IS_OFF "SCREEN_FACEBOOK_2FA_IS_OFF"
#define SCREEN_FACEBOOK_SETTING_LANGUAGE "SCREEN_FACEBOOK_SETTING_LANGUAGE"
#define SCREEN_FACEBOOK_CHECKPOINT "SCREEN_FACEBOOK_CHECKPOINT"
#define SCREEN_FACEBOOK_ADD_PHOTO "SCREEN_FACEBOOK_ADD_PHOTO"
#define SCREEN_FACEBOOK_FIND_FRIENDS "SCREEN_FACEBOOK_FIND_FRIENDS"
#define SCREEN_FACEBOOK_SKIP_FIND_FRENDS "SCREEN_FACEBOOK_SKIP_FIND_FRENDS"
#define SCREEN_FACEBOOK_SAVE_LOGGIN_INFO "SCREEN_FACEBOOK_SAVE_LOGGIN_INFO"
#define SCREEN_FACEBOOK_ALERT_CHANGE_TIME_SETTINGS "SCREEN_FACEBOOK_ALERT_CHANGE_TIME_SETTINGS"
#define SCREEN_FACEBOOK_2FA_GETCODE "SCREEN_FACEBOOK_2FA_GETCODE"
#define SCREEN_FACEBOOK_ENTER_2FA_CONFIRM_CODE "SCREEN_FACEBOOK_ENTER_2FA_CONFIRM_CODE"
#define SCREEN_FACEBOOK_RE_ENTER_PASSWORD "SCREEN_FACEBOOK_RE_ENTER_PASSWORD"
#define SCREEN_FACEBOOK_SETTING_2FA_DONE "SCREEN_FACEBOOK_SETTING_2FA_DONE"
#define SCREEN_FACEBOOK_INCORRECT_PASSWORD "SCREEN_FACEBOOK_INCORRECT_PASSWORD"
#define SCREEN_FACEBOOK_FB_REQUEST_ACCESS_LOCATION "SCREEN_FACEBOOK_REQUEST_ACCESS_LOCATION"
#define SCREEN_FACEBOOK_LOGGIN_CODE_REQUIRE "SCREEN_FACEBOOK_LOGGIN_CODE_REQUIRE"
#define SCREEN_FACEBOOK_ENTER_LOGGIN_CODE "SCREEN_FACEBOOK_ENTER_LOGGIN_CODE"
#define SCREEN_FACEBOOK_NOT_FOUND_ACCOUNT "SCREEN_FACEBOOK_NOT_FOUND_ACCOUNT"
#define SCREEN_FACEBOOK_MY_PROFILE "SCREEN_FACEBOOK_MY_PROFILE"
#define SCREEN_FACEBOOK_FB_REQUEST_ACCESS_MEDIA "SCREEN_FACEBOOK_REQUEST_ACCESS_MEDIA"
#define SCREEN_FACEBOOK_FB_GET_PHOTO_OPTIONS "SCREEN_FACEBOOK_GET_PHOTO_OPTIONS"
#define SCREEN_FACEBOOK_FB_GET_COVER_PHOTO_OPTIONS "SCREEN_FACEBOOK_GET_COVER_PHOTO_OPTIONS"
#define SCREEN_FACEBOOK_FB_SELECT_PHOTO "SCREEN_FACEBOOK_SELECT_PHOTO"
#define SCREEN_FACEBOOK_FB_PRIVEW_PROFILE_PIC "SCREEN_FACEBOOK_PRIVEW_PROFILE_PIC"
#define SCREEN_FACEBOOK_FB_PRIVEW_COVER_PIC "SCREEN_FB_PRIVEW_COVER_PIC"
#define SCREEN_FACEBOOK_FB_ANOTHER_PROFILE "SCREEN_FACEBOOK_ANOTHER_PROFILE"
#define SCREEN_FACEBOOK_FB_INVALID_PROFILE "SCREEN_FACEBOOK_INVALID_PROFILE"
#define SCREEN_FACEBOOK_FB_INVALID_PAGE "SCREEN_FACEBOOK_INVALID_PAGE"
#define SCREEN_FACEBOOK_FACEBOOK_BEFORE_LIKE_PAGE "SCREEN_FACEBOOK_BEFORE_LIKE_PAGE"
#define SCREEN_FACEBOOK_DRAWER_OVER_REQUEST "SCREEN_FACEBOOK_DRAWER_OVER_REQUEST"
#define SCREEN_FACEBOOK_FB_ANOTHER_FANPAGE "SCREEN_FACEBOOK_ANOTHER_FANPAGE"
#define SCREEN_FACEBOOK_FACEBOOK_SHARE_PAGE_OPTIONS "SCREEN_FACEBOOK_SHARE_PAGE_OPTIONS"
#define SCREEN_FACEBOOK_FACEBOOK_UNFOLLOW_PROFILE "SCREEN_FACEBOOK_UNFOLLOW_PROFILE"
#define SCREEN_FACEBOOK_LOGIN_FAILED "SCREEN_LOGIN_FAILED"
#define SCREEN_FACEBOOK_FACEBOOK_GROUP_PROFILE "SCREEN_FACEBOOK_GROUP_PROFILE"
#define SCREEN_FACEBOOK_FACEBOOK_ANWSER_QUESTION "SCREEN_FACEBOOK_ANWSER_QUESTION"
#define SCREEN_FACEBOOK_FACEBOOK_LOGOUT_ACCEPT "SCREEN_FACEBOOK_LOGOUT_ACCEPT"
#define SCREEN_FACEBOOK_FACEBOOK_REMOVE_ACCOUNT_ACCEPT "SCREEN_FACEBOOK_REMOVE_ACCOUNT_ACCEPT"
#define SCREEN_FACEBOOK_FACEBOOK_FRIENDS_TAB "SCREEN_FACEBOOK_FRIENDS_TAB"
#define SCREEN_FACEBOOK_FACEBOOK_START_CONVERSION "SCREEN_FACEBOOK_START_CONVERSION"
#define SCREEN_FACEBOOK_FACEBOOK_FRIENDS_SUGGESTION "SCREEN_FACEBOOK_FRIENDS_SUGGESTION"
#define SCREEN_FACEBOOK_FACEBOOK_SHARE_OPTIONS "SCREEN_FACEBOOK_SHARE_OPTIONS"
#define SCREEN_FACEBOOK_FACEBOOK_FANPAGE_OPERATIONS "SCREEN_FACEBOOK_FANSCREEN_OPERATIONS"
#define SCREEN_FACEBOOK_FACEBOOK_CHOOSE_GROUP "SCREEN_FACEBOOK_CHOOSE_GROUP"
#define SCREEN_FACEBOOK_FACEBOOK_POST_ON "SCREEN_FACEBOOK_POST_ON"
#define SCREEN_FACEBOOK_FACEBOOK_UPDATE_PROFILE "SCREEN_FACEBOOK_UPDATE_PROFILE"
#define SCREEN_FACEBOOK_SAVE_ACCOUNT "SCREEN_FACEBOOK_SAVE_ACCOUNT"
#define SCREEN_FACEBOOK_FACEBOOK_SESSION_EXPIRED "SCREEN_FACEBOOK_SESSION_EXPIRED"
#define SCREEN_FACEBOOK_FACEBOOK_LOST_CONNECTION "SCREEN_FACEBOOK_LOST_CONNECTION"
#define SCREEN_FACEBOOK_FACEBOOK_CANNOT_USE_FEATURE "SCREEN_FACEBOOK_CANNOT_USE_FEATURE_RIGHT_NOW"
#define SCREEN_FACEBOOK_FACEBOOK_REQUEST_ACCESS_CONTACT "SCREEN_FACEBOOK_REQUEST_ACCESS_CONTACT"
#define SCREEN_FACEBOOK_FACEBOOK_EXIT_WITHOUT_ANSWERING "SCREEN_FACEBOOK_EXIT_WITHOUT_ANSWERING"
#define SCREEN_FACEBOOK_FACEBOOK_LOADING "SCREEN_FACEBOOK_LOADING"
#define SCREEN_FACEBOOK_FB_REQUEST_OVERLAY_PERMISSION "SCREEN_FACEBOOK_REQUEST_OVERLAY_PERMISSION"
#define SCREEN_FACEBOOK_FACEBOOK_USE_DATA_TO_CONTINUE "SCREEN_FACEBOOK_USE_DATA_TO_CONTINUE"
#define SCREEN_FACEBOOK_FACEBOOK_CREATE_ACCOUNT "SCREEN_FACEBOOK_CREATE_ACCOUNT"
#define SCREEN_FACEBOOK_FACEBOOK_LIVE_VIDEO_VIEW "SCREEN_FACEBOOK_LIVE_VIDEO_VIEW"
#define SCREEN_FACEBOOK_FACEBOOK_REQUEST_MANAGE_CALL "SCREEN_FACEBOOK_REQUEST_MANAGE_CALL"
#define SCREEN_FACEBOOK_FACEBOOK_REG_INPUT_NAME "SCREEN_FACEBOOK_REG_INPUT_NAME"
#define SCREEN_FACEBOOK_FACEBOOK_REG_INPUT_BIRTHDAY "SCREEN_FACEBOOK_REG_INPUT_BIRTHDAY"
#define SCREEN_FACEBOOK_FACEBOOK_REG_INPUT_GENDER "SCREEN_FACEBOOK_REG_INPUT_GENDER"
#define SCREEN_FACEBOOK_FACEBOOK_CONFIRM_BIRTHDAY "SCREEN_FACEBOOK_CONFIRM_BIRTHDAY"
#define SCREEN_FACEBOOK_FACEBOOK_ENTER_MOBILE_NUMBER "SCREEN_FACEBOOK_ENTER_MOBILE_NUMBER"
#define SCREEN_FACEBOOK_FACEBOOK_ENTER_EMAIL "SCREEN_FACEBOOK_ENTER_EMAIL"
#define SCREEN_FACEBOOK_FACEBOOK_ENTER_PASSWORD "SCREEN_FACEBOOK_ENTER_PASSWORD"
#define SCREEN_FACEBOOK_FACEBOOK_FINISH_SIGNING_UP "SCREEN_FACEBOOK_FINISH_SIGNING_UP"
#define SCREEN_FACEBOOK_FACEBOOK_ENTER_CODE_FROM_EMAIL "SCREEN_FACEBOOK_ENTER_CODE_FROM_EMAIL"
#define SCREEN_FACEBOOK_FACEBOOK_PROCESSING "SCREEN_FACEBOOK_PROCESSING"
#define SCREEN_FACEBOOK_FACEBOOK_ENTER_CODE_FROM_SMS "SCREEN_FACEBOOK_ENTER_CODE_FROM_SMS"
#define SCREEN_FACEBOOK_FB_REMEMBER_PHONENUMBER_PASSWORD "SCREEN_FACEBOOK_REMEMBER_PHONENUMBER_PASSWORD"
#define SCREEN_FACEBOOK_FACEBOOK_SAVEINFO_WHEN_REGISTER "SCREEN_FACEBOOK_SAVEINFO_WHEN_REGISTER"
#define SCREEN_FACEBOOK_FACEBOOK_CREATING_ACCOUNT "SCREEN_FACEBOOK_CREATING_ACCOUNT"
#define SCREEN_FACEBOOK_FACEBOOK_SIGNING_IN "SCREEN_FACEBOOK_SIGNING_IN"
#define SCREEN_FACEBOOK_FB_ANOTHER_PROFILE_INTERACTION "SCREEN_FACEBOOK_ANOTHER_PROFILE_INTERACTION"
#define SCREEN_FACEBOOK_FACEBOOK_UNLIKE_FACEBOOK_PAGE "SCREEN_FACEBOOK_UNLIKE_FACEBOOK_PAGE"
#define SCREEN_FACEBOOK_FACEBOOK_UPDATE_EMAIL "SCREEN_FACEBOOK_UPDATE_EMAIL"
#define SCREEN_FACEBOOK_FACEBOOK_IS_YOU_CONFIRM "SCREEN_FACEBOOK_IS_YOU_CONFIRM"
#define SCREEN_FACEBOOK_FACEBOOK_PACKAGE_OPTIONS "SCREEN_FACEBOOK_PACKAGE_OPTIONS"
#define SCREEN_FACEBOOK_FACEBOOK_AUTHENTICATION_ERROR "SCREEN_FACEBOOK_AUTHENTICATION_ERROR"
#define SCREEN_FACEBOOK_FACEBOOK_CREATE_POST "SCREEN_FACEBOOK_CREATE_POST"
#define SCREEN_FACEBOOK_FACEBOOK_POST_CANCEL "SCREEN_FACEBOOK_POST_CANCEL"
#define SCREEN_FACEBOOK_APP_FACEBOOK_INFO "SCREEN_APP_FACEBOOK_INFO"
#define SCREEN_FACEBOOK_SETTINGS_APP_PERMISSIONS "SCREEN_SETTINGS_APP_PERMISSIONS"
#define SCREEN_FACEBOOK_SETTINGS_STORAGE_PERMISSIONS "SCREEN_SETTINGS_STORAGE_PERMISSIONS"
#define SCREEN_FACEBOOK_FACEBOOK_WRITE_COMMENT "SCREEN_FACEBOOK_WRITE_COMMENT"
#define SCREEN_FACEBOOK_FACEBOOK_FULL_POST "SCREEN_FACEBOOK_FULL_POST"
#define SCREEN_FACEBOOK_SOMETHING_WENT_WRONG "SCREEN_FACEBOOK_SOMETHING_WENT_WRONG"
#define SCREEN_FACEBOOK_FACEBOOK_PHOTO_VIEW "SCREEN_FACEBOOK_PHOTO_VIEW"
#define SCREEN_FACEBOOK_VIDEO_VIEW "SCREEN_FACEBOOK_VIDEO_VIEW"
#define SCREEN_FACEBOOK_FACEBOOK_CHOOSE_POST_PRIVACY "SCREEN_FACEBOOK_CHOOSE_POST_PRIVACY"
#define SCREEN_FACEBOOK_FACEBOOK_RESTRICT_REACTIONS "SCREEN_FACEBOOK_RESTRICT_REACTIONS"
#define SCREEN_FACEBOOK_REACTION_LIST "SCREEN_FACEBOOK_REACTION_LIST"
#define SCREEN_FACEBOOK_INPUT_RECOMMEND_FANPAGE "SCREEN_FACEBOOK_INPUT_RECOMMEND_FANPAGE"
#define SCREEN_FACEBOOK_THANKS_FOR_RECOMMENDING "SCREEN_FACEBOOK_THANKS_FOR_RECOMMENDING"
#define SCREEN_FACEBOOK_POSTING_RECOMMENDATION "SCREEN_FACEBOOK_POSTING_RECOMMENDATION"
#define SCREEN_FACEBOOK_TROUBLE_LOADING "SCREEN_FACEBOOK_TROUBLE_LOADING"
#define SCREEN_FACEBOOK_PROFILE_INFO_INNER "SCREEN_FACEBOOK_PROFILE_INFO_INNER"
#define SCREEN_FACEBOOK_GUILINE_POPUP "SCREEN_FPHONE_FACEBOOK_GUILINE_POPUP"


class Screendefine : public QObject {

private:
    explicit Screendefine();

public:
    static Screendefine* instance();

    QJsonArray screentElements();
    void findAndDefineScreenElement(QJsonArray& elements, QAccessibilityNodeInfo& nodeInfo);
    QRect getLocationFromNode(QAccessibilityNodeInfo& nodeInfo);
    QJsonObject getCurrentScreenInfo();
    QJsonObject getCurrentScreenInfo(QJsonArray& screentElements);
    bool isScreenMatch(QJsonArray& screenInfinitys,QJsonArray& screentElements);
    bool isElementMatch(QJsonObject defineElement,QJsonArray& screentElements);
    void findAndDefineKeyword(QJsonArray& keywords, QJsonArray& screentElements);

    void setScreenInfinity(QJsonArray screenInfi);

    static bool clickElement(QJsonObject& element,bool random){
        if(!element.isEmpty()){
            int x = element.value("x").toInt() + (element.value("width").toInt() / 2);
            int y = element.value("y").toInt() + (element.value("height").toInt() / 2);

//            if(random){
//                x = FUtils::randomRange(element.value("x").toInt(),element.value("x").toInt() + element.value("width").toInt());
//                y = FUtils::randomRange(element.value("y").toInt(),element.value("y").toInt() + element.value("height").toInt());
//            }

            FUtils::click(x, y, false);

            return true;
        }
        return false;
    }

    static bool findElementExistsByTextOrDes(QString textOrDes,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == textOrDes || screenElement.value("contentDescription") == textOrDes){
                return true;
            }
        }
        return false;
    }

    static bool findElementExistsByText(QString text,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == text){
                return true;
            }
        }
        return false;
    }

    static bool findElementExistsByDescription(QString description,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("contentDescription").toString() == description){
                return true;
            }
        }
        return false;
    }

    static bool findElementExistsByClassName(QString className,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("className").toString() == className){
                return true;
            }
        }
        return false;
    }

    static bool findElementExistsByKeyword(QString keyword,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("keyword").toString() == keyword){
                return true;
            }
        }
        return false;
    }

    static bool findAndClickElementByTextOrDes(QString textOrDes,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == textOrDes || screenElement.value("contentDescription") == textOrDes){
                return clickElement(screenElement,true);
            }
        }
        return false;
    }

    static bool findAndClickElementByText(QString text,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == text){
                return clickElement(screenElement,true);
            }
        }
        return false;
    }

    static bool findAndClickElementByDescription(QString description,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("contentDescription").toString() == description){
                return clickElement(screenElement,true);
            }
        }
        return false;
    }

    static bool findAndClickElementByClassName(QString className,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("className").toString() == className){
                return clickElement(screenElement,true);
            }
        }
        return false;
    }

    static bool findAndClickElementByKeyword(QString keyword, QJsonArray &screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("keyword").toString() == keyword){
                return clickElement(screenElement,true);
            }
        }
        return false;
    }

    static QJsonObject findElementByTextOrDes(QString textOrDes,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == textOrDes || screenElement.value("contentDescription") == textOrDes){
                return screenElement;
            }
        }
        return QJsonObject();
    }

    static QJsonObject findElementByText(QString text,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == text){
                return screenElement;
            }
        }
        return QJsonObject();
    }

    static QJsonObject findElementByDescription(QString description,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("contentDescription").toString() == description){
                return screenElement;
            }
        }
        return QJsonObject();
    }

    static QJsonObject findElementByClassName(QString className,QJsonArray& screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("className").toString() == className){
                return screenElement;
            }
        }
        return QJsonObject();
    }

    static QJsonObject findElementByKeyword(QString keyword, QJsonArray &screenElements){
        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("keyword").toString() == keyword){
                return screenElement;
            }
        }
        return QJsonObject();
    }

    static QList<QJsonObject> findElementsByTextOrDes(QString textOrDes,QJsonArray& screenElements){
        QList<QJsonObject> elements = QList<QJsonObject>();

        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == textOrDes || screenElement.value("contentDescription") == textOrDes){
                elements.append(screenElement);
            }
        }
        return elements;
    }

    static QList<QJsonObject> findElementsByText(QString text,QJsonArray& screenElements){
        QList<QJsonObject> elements = QList<QJsonObject>();

        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("text").toString() == text){
                elements.append(screenElement);
            }
        }
        return elements;
    }

    static QList<QJsonObject> findElementsByDescription(QString description,QJsonArray& screenElements){
        QList<QJsonObject> elements = QList<QJsonObject>();

        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("contentDescription").toString() == description){
                elements.append(screenElement);
            }
        }
        return elements;
    }

    static QList<QJsonObject> findElementsByClassName(QString className,QJsonArray& screenElements){
        QList<QJsonObject> elements = QList<QJsonObject>();

        for (int i=0; i < screenElements.size(); i++){
            QJsonObject screenElement = screenElements.at(i).toObject();

            if (screenElement.value("className").toString() == className){
                elements.append(screenElement);
            }
        }
        return elements;
    }

private:
    static Screendefine* s_Instance;
    QJsonArray screenInfinity;
    QJsonArray screenInfinity_local;

};

#endif // SCREENDEFINE_H
