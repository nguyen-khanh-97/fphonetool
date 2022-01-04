#ifndef JSONPARSERENGINE_H
#define JSONPARSERENGINE_H


#include <QObject>
#include <QNetworkAccessManager>

#include <CkGlobal.h>
#include <CkJsonObject.h>
#include <CkHttpRequest.h>
#include <CkHttpResponse.h>
#include <CkHttp.h>
#include <CkCert.h>
#include <CkPrivateKey.h>
#include <CkHttpRequestW.h>
#include <CkHttpResponseW.h>
#include <CkHttpW.h>
#include <CkCertW.h>
#include <CkPrivateKeyW.h>

class JsonParserEngine: public QObject
{
public:
    static JsonParserEngine* getInstance();

    /**
     * @brief getDefinition
     * @param definition: out
     * @return success
     */
    bool getDefinition(QJsonArray &definition);

    /**
     * @brief createLog
     * @param screenId: in
     * @param token: in
     * @param action: in
     * @param androidId: in
     * @param imagePath: in, screenshot image path
     * @param screenInfoPath: in, .txt screen info path
     * @param response: out
     * @return success
     */
    bool createLog(QString screenId, QString token, QString action, QString androidId,
                   QString imagePath, QString screenInfoPath, QJsonObject &response);

private slots:
    // backup slot handle function use QNetworkAccessManager
    void finishedGetDefinitionQNetworkHandle();
    void finishedCreateLogQNetworkHandle();

private:
    JsonParserEngine();
    ~JsonParserEngine();

    bool initCkHttp(CkHttp& http);
    bool initCkHttpW(CkHttpW& http);

    // backup function use QNetworkAccessManager
    void getDefinitionQNetwork();
    void createLogQNetwork();


private:
    static JsonParserEngine* instance;
    QNetworkAccessManager m_manager;
    QNetworkReply* m_reply = nullptr;
    QHttpMultiPart* m_multiPart = nullptr;

};

#endif // JSONPARSERENGINE_H
