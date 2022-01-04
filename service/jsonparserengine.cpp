#include "jsonparserengine.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <log.h>
#include <QSslSocket>
#include "CkByteData.h"


JsonParserEngine* JsonParserEngine::instance = nullptr;

JsonParserEngine *JsonParserEngine::getInstance()
{
    if(nullptr == instance){
        instance = new JsonParserEngine();
    }
    return instance;
}

void JsonParserEngine::getDefinitionQNetwork()
{
    LOGD("start get definition");
    const QUrl url(QStringLiteral("https://log-api.congaubeo.us/api/v1/definition/search"));
    QNetworkRequest rq(url);
    rq.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject dataJsonPath;
    dataJsonPath.insert("created_source", "android_dang");
    QJsonDocument dataJsonDoc(dataJsonPath);
    std::string dataJsonPathToString(dataJsonDoc.toJson(QJsonDocument::Compact));

    QByteArray data(dataJsonPathToString.c_str());
    m_reply = m_manager.post(rq, data);
    disconnect(m_reply, nullptr, nullptr, nullptr);
    QObject::connect(m_reply, &QNetworkReply::finished, this, &JsonParserEngine::finishedGetDefinitionQNetworkHandle);
}

void JsonParserEngine::createLogQNetwork()
{
    LOGD("start create log");
    m_multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textpart1;
    textpart1.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"screen_id\""));
    textpart1.setBody("TEST_SCREEN_ID");
    m_multiPart->append(textpart1);

    QHttpPart textpart2;
    textpart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"source\""));
    textpart2.setBody("android_phong");
    m_multiPart->append(textpart2);

    QHttpPart textpart3;
    textpart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"token\""));
    textpart3.setBody("7111118962");
    m_multiPart->append(textpart3);

    QHttpPart textpart4;
    textpart4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
    textpart4.setBody("TEST_ACTION");
    m_multiPart->append(textpart4);

    QHttpPart textpart5;
    textpart5.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"android_id\""));
    textpart5.setBody("123456789");
    m_multiPart->append(textpart5);

    QHttpPart textpart6;
    textpart6.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"device_label\""));
    textpart6.setBody("tt");
    m_multiPart->append(textpart6);

    QHttpPart textpart7;
    textpart7.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"device_model\""));
    textpart7.setBody("cc1");
    m_multiPart->append(textpart7);

    QHttpPart textpart8;
    textpart8.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"module\""));
    textpart8.setBody("cc2");
    m_multiPart->append(textpart8);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\"a9b194d00807d163fbc935acbd552471.jpeg\""));
    QFile *image = new QFile("/Users/macbook/Downloads/a9b194d00807d163fbc935acbd552471.jpeg");
    image->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(image);
    image->setParent(m_multiPart);
    m_multiPart->append(imagePart);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"screen_info\"; filename=\"log.txt\""));
    QFile *file = new QFile("/Users/macbook/Documents/log.txt");
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(m_multiPart);
    m_multiPart->append(filePart);

    QUrl url("https://log-api.congaubeo.us/api/v1/log-screen/create");
    QNetworkRequest rq(url);
    m_reply = m_manager.post(rq, m_multiPart);
    m_multiPart->setParent(m_reply);
    disconnect(m_reply, nullptr, nullptr, nullptr);
    QObject::connect(m_reply, &QNetworkReply::finished, this, &JsonParserEngine::finishedCreateLogQNetworkHandle);
}

bool JsonParserEngine::getDefinition(QJsonArray &definition)
{
    CkHttpW http;
    if(!initCkHttpW(http)){
        QTLOGD << "Cannot init CkHttp!";
        return false;
    }

    QJsonObject bodyData;
    bodyData.insert("created_source", "android_dang");

    bool success = false;
    CkHttpResponseW *resp = http.PostJson(L"https://log-api.congaubeo.us/api/v1/definition/search",
                                          QString(QJsonDocument(bodyData).toJson()).toStdWString().c_str());

    if (!http.get_LastMethodSuccess())
    {
        QTLOGD << "Error: " << http.lastErrorText();
    }
    else
    {
        if (resp->bodyStr()) {
            QTLOGD << "raw: " << resp->bodyStr();
            QJsonDocument respDoc = QJsonDocument::fromJson(QString::fromWCharArray(resp->bodyStr()).toUtf8());
            if(!respDoc.isNull() && respDoc.isObject()) {
                definition = respDoc.object().value("data").toObject().value("data").toObject().value("data").toArray();
                success = true;
            }
        } else {
            QTLOGD << "error_message: resp->bodyStr() is NULL";
        }
    }
    delete resp;
    return success;
}

bool JsonParserEngine::createLog(QString screenId, QString token, QString action, QString androidId,
                                 QString imagePath, QString screenInfoPath, QJsonObject &response)
{
    CkHttp http;
    initCkHttp(http);

    bool success = false;
    // First, let's build the HTTP request object
    CkHttpRequest req;

    req.put_HttpVerb("POST");
    req.put_Path("/api/v1/log-screen/create");

    // The boundary string is automatically generated and added by Chilkat.
    // The value for the boundary string doesn't matter. (As long as it's a unique string that doesn't occur elsewhere in the request.)
    req.put_ContentType("multipart/form-data");

    // --------------------------------------------------
    // IMPORTANT: Never set the Content-Length header.
    // Chilkat will automatically compute the correct Content-Length and will add it.
    // --------------------------------------------------

    // Add the params to the request.  Given that the Content-Type is set to "multipart/form-data", when
    // Chilkat composes the request, it will put each param in it's own MIME sub-part (i.e. in it's own
    // part delimited by the boundary string).
    req.AddParam("screen_id", screenId.toUtf8().data());
    req.AddParam("source","android_phong");
    req.AddParam("token", token.toUtf8().data());
    req.AddParam("action", action.toUtf8().data());
    req.AddParam("android_id", androidId.toUtf8().data());
    req.AddParam("device_label","tt");
    req.AddParam("device_model","cc");
    req.AddParam("module","cc");

    // The param is the contents of a file.
    if(imagePath.isEmpty()) {
        LOGD("Empty path Image");
        CkByteData emptyImage;
        success = req.AddBytesForUpload("image", "emptyImage.png", emptyImage);
        if (success != true) {
            LOGD("Error AddBytesForUpload %s", req.lastErrorText());
            return false;
        }
    } else {
        LOGD("Contain path Image");
        success = req.AddFileForUpload("image",imagePath.toUtf8().data());
        if (success != true) {
            LOGD("Error AddFileForUpload %s", req.lastErrorText());
            return false;
        }
    }

    success = req.AddFileForUpload("screen_info",screenInfoPath.toUtf8().data());
    if (success != true) {
        LOGD("Error AddFileForUpload %s", req.lastErrorText());
        return false;
    }

    // -----------------------------------------------------------
    // IMPORTANT: To duplicate the HTTP request shown above, you'll want to choose
    // either AddStringForUpload or AddFileForUpload, but not both.  It's possible to upload
    // any number of files by calling AddStringForUpload and/or AddFileForUpload any number
    // of times, once per file to be uploaded.  This of course assumes that the receiving
    // end is programmed to receive multiple files..
    // ------------------------------------------------------------

    // The request is ready... now send it using HTTPS (which is port 443 by default).

    CkHttpResponse *resp = http.SynchronousRequest("log-api.congaubeo.us",443,true,req);
    if (!http.get_LastMethodSuccess())
    {
        LOGD("Error: %s", http.lastErrorText());
    }
    else
    {
        LOGD("HTTP response status: %d", resp->get_StatusCode());
        LOGD("rep %s", resp->bodyStr());
        if (resp->bodyStr()) {
            QJsonDocument respDoc = QJsonDocument::fromJson(resp->bodyStr());
            if(!respDoc.isNull() && respDoc.isObject()) {
                response = respDoc.object();
                success = true;
            }
        } else {
            LOGD("error_message: resp->bodyStr() is NULL");
        }
    }
    delete resp;
    return success;
}

void JsonParserEngine::finishedGetDefinitionQNetworkHandle()
{
    QByteArray str = m_reply->readAll();
    QJsonDocument itemDoc = QJsonDocument::fromJson(str);
    QJsonObject obj = itemDoc.object();
    LOGD("finish getDefinition: %s", str.data());
    m_reply->deleteLater();
}

void JsonParserEngine::finishedCreateLogQNetworkHandle()
{
    QByteArray str = m_reply->readAll();
    LOGD("finish createLog: %s", str.data());
    m_reply->deleteLater();
}

JsonParserEngine::JsonParserEngine()
{

}

JsonParserEngine::~JsonParserEngine()
{

}

bool JsonParserEngine::initCkHttp(CkHttp &http)
{
    bool success = false;
    CkCert cert;
    CkPrivateKey privKey;

    // Load any type of certificate (.cer, .p7b, .pem, etc.) by calling LoadFromFile.
    success = cert.LoadPem("-----BEGIN CERTIFICATE-----\
                           MIID9DCCAtygAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMHcxCzAJBgNVBAYTAlVT\
                           MRMwEQYDVQQIDApTb21lLVN0YXRlMRowGAYDVQQKDBFhcGkuZi1jYXJlLmlvIEx0\
                           ZDEWMBQGA1UEAwwNYXBpLmYtY2FyZS5pbzEfMB0GCSqGSIb3DQEJARYQY2FAYXBp\
                           LmYtY2FyZS5pbzAeFw0yMTA4MDkxMDI1MTFaFw0zMTA4MDcxMDI1MTFaMHoxCzAJ\
                           BgNVBAYTAlVTMRwwGgYDVQQIExNTdGF0ZSBvciBQcm92aWRlbmNlMRAwDgYDVQQK\
                           EwdDb21wYW55MRYwFAYDVQQDEw1hcGkuZi1jYXJlLmlvMSMwIQYJKoZIhvcNAQkB\
                           FhRjbGllbnRAYXBpLmYtY2FyZS5pbzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\
                           AQoCggEBANWre49HRXDu6h+N8vxAeVr5TCbtCcG7jDWLq1aLaQF1k5X2HcFQ7Slw\
                           9KEzbjeAhfm95iNg4BKnmVRxcptdfuVbp0qNUirPOHvSw1eaczckFCHyXx9Sa4FR\
                           CYDMVU5tuWUQ8sXHWBZtlgvdf0fEBy32ArD6kSGitGxUzNJuIMgreHQSQiFv7u3q\
                           lRr9YwsFV7PBNnSFYjQ6Mvlqi47CR5lR6pY6Rnbbfi0rIFE68fHZpQZW7qDP+orV\
                           9Rtwq1IVPchJNmweM1UCAfZQ6b94oeUaKF8vX+9y7hfc+6rHEM5KbGZqr29wEAqq\
                           SA1aJiQL7cHSUu5Y9zHgrz0i1YxXP1sCAwEAAaOBhTCBgjAJBgNVHRMEAjAAMB0G\
                           A1UdDgQWBBQaWmDi+o/KCy7Mjw65BTpLkq+QxzAfBgNVHSMEGDAWgBS8Uy4SbZlr\
                           vxGWW2ypuhiHWtnGtDA1BgNVHR8ELjAsMCqgKKAmhiRodHRwOi8vd3d3LnlvdXJk\
                           b21haW4uY29tL2NhL2NybC5wZW0wDQYJKoZIhvcNAQELBQADggEBAK50frhRm3uo\
                           3WEXaInLovL9Ti8+6eP1wVtxCTXjwKSTepl2bh8B5mr1fh12uG54RS4tQjDVOWuC\
                           3EFTRqn53e92tnc+GShKp6F6Cuqew2T0Bp1oWRJAJ+TFY+UffgvoiXNV4fFH961l\
                           Zqoovwq134I8bpa0qCtUiTJOK1iRBGlnqAfRHmVgaFCwG1hhf9lKJbmlwwyUtYVC\
                           uVqANVmyTCgVJf+BcYfbNsiAj0MB/k98nhcq6LA9szRsPRbFElvLOv/vvtzhNLee\
                           AhmHJLnHmkaDtC2B8mSf9FAm+nyx065rzWcVySYu+rUAJ8++XSF6w/WtC26J3zD1\
                           1ype3Wfivdc=\
                           -----END CERTIFICATE-----");
    if (success != true) {
        LOGD("append cert error: %s", cert.lastErrorText());
        return false;
    }

    // Load the private key.
    success = privKey.LoadEncryptedPem("-----BEGIN PRIVATE KEY-----\
                                       MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDVq3uPR0Vw7uof\
                                       jfL8QHla+Uwm7QnBu4w1i6tWi2kBdZOV9h3BUO0pcPShM243gIX5veYjYOASp5lU\
                                       cXKbXX7lW6dKjVIqzzh70sNXmnM3JBQh8l8fUmuBUQmAzFVObbllEPLFx1gWbZYL\
                                       3X9HxAct9gKw+pEhorRsVMzSbiDIK3h0EkIhb+7t6pUa/WMLBVezwTZ0hWI0OjL5\
                                       aouOwkeZUeqWOkZ2234tKyBROvHx2aUGVu6gz/qK1fUbcKtSFT3ISTZsHjNVAgH2\
                                       UOm/eKHlGihfL1/vcu4X3PuqxxDOSmxmaq9vcBAKqkgNWiYkC+3B0lLuWPcx4K89\
                                       ItWMVz9bAgMBAAECggEAYqCMIT/Juu5dHYGdVnjAS5DlaNZjeYyDlLfKt+ET8DuA\
                                       i2kWpQQg5M8h7ELcLjxiGzxfvZba92FrckIHn9WRXHdpCg2fjukl7moEByzg3+QE\
                                       cwL4i3G08/UfCNfIzLHzMMaY+VghvgCJkSKFvO+sTLfQ2DZgxYDf/V1LShrRgPNP\
                                       fMWyeEUmbuttfwAM9c662khkjzqcuWfYLScfUfLN2FMVHG+4VEup6O70O4iVy8gy\
                                       Rb6EZdOxzj7TzCCXdSFV/bJD02TYwtC1V0YO659MGrtwt6Gz+85THLi9QOQjwYEy\
                                       EQ3s5FkSmmVMJOjXetG5ydX0oAaCLFYF8mftuwTWuQKBgQD52M/uqQLAI5C16TSr\
                                       yZafzKpE/OJBnk2wGx+LO+wUBfHQ3MGv/juWs1XHzbuv+yGEE21kCxhrnmHnKqq+\
                                       By0NV7b2n12bA2lYY3zEOo86Q3rmbzpy9/lIYxUTN69Y0u65E2LxRpbP19QGm5HY\
                                       CX81ngiA9eJ3BAkLZv/zzFggfQKBgQDa7paLCSFpaxKWpD5cvde/7NERx80ivCcb\
                                       +x0jiRsa6i9Em7OIAjM1sKV2noT+EwBHn4Y3JluZXe418XsP+51ldzZTJeY+VL+3\
                                       NPNSJRJdowfeGIXGCOWc6chw/Lcn3jSH86Ytwtdy3Br1VtRTucdm3GRkk1n4ydJx\
                                       DJf8NEz+twKBgQCqHNNGvlCfHhgTo9s29CTYXPO50S0EXJKsy2ro1D3jTEDfYs+F\
                                       0uYjr6tCRXP7WFPzp36d1WglLkuep9BlXmFwaj6rIMsNFn+NrP9wZCbNFtEBQM5d\
                                       JTXX8Y6R7SI4qjXcUbTWbqeUkHFOpnHg1GaGzTkhBUnSmy7FUrYG+yUtyQKBgCi+\
                                       wKvNnjdFYydAGA8gkde5Vkut2MK/K7QsbwbfDHlc3kExjR8h8a/rWVATPoMevC2Y\
                                       Rd1buS546c2GTLXzyR5KKoUdB5XQJgINy78dAScGIX+3JqZtn3YtmE1W6ytzUml+\
                                       8g2QNpK83hOM/mU6rR66o8CIH/WKcizyABNDFJVPAoGBAKmjujs6j2CG9wUQ0G91\
                                       Fy7OnDX3IgoOHyf5HyGzpCIt3x/4i6u0rx9BDBS0zW8r78KOwaPwyzXkvcWP5sT2\
                                       VD1ltxWyRWMNnmk1mPlIEaQlb8/ra5dXF0IxkA/l438sr0bvOla8oMFwS+9IXo6S\
                                       YsqC7uFMpOtN2sdAuoTHkao+\
                                       -----END PRIVATE KEY-----","client");
    if (success != true) {
        LOGD("load key error: %s", privKey.lastErrorText());
        return false;
    };

    // Associate the private key with the cert.
    success = cert.SetPrivateKey(privKey);
    if (success != true) {
        LOGD("SetPrivateKey error: %s", cert.lastErrorText());
        return false;
    }

    success = http.SetSslClientCert(cert);
    if (success != true) {
        LOGD("SetSslClientCert error: %s", http.lastErrorText());
        return false;
    }

    LOGD("init CkHttp success");
    return success;
}

bool JsonParserEngine::initCkHttpW(CkHttpW &http)
{
    bool success = false;
    CkCertW cert;
    CkPrivateKeyW privKey;

    // Load any type of certificate (.cer, .p7b, .pem, etc.) by calling LoadFromFile.
    success = cert.LoadPem(L"-----BEGIN CERTIFICATE-----\
                           MIID9DCCAtygAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMHcxCzAJBgNVBAYTAlVT\
                           MRMwEQYDVQQIDApTb21lLVN0YXRlMRowGAYDVQQKDBFhcGkuZi1jYXJlLmlvIEx0\
                           ZDEWMBQGA1UEAwwNYXBpLmYtY2FyZS5pbzEfMB0GCSqGSIb3DQEJARYQY2FAYXBp\
                           LmYtY2FyZS5pbzAeFw0yMTA4MDkxMDI1MTFaFw0zMTA4MDcxMDI1MTFaMHoxCzAJ\
                           BgNVBAYTAlVTMRwwGgYDVQQIExNTdGF0ZSBvciBQcm92aWRlbmNlMRAwDgYDVQQK\
                           EwdDb21wYW55MRYwFAYDVQQDEw1hcGkuZi1jYXJlLmlvMSMwIQYJKoZIhvcNAQkB\
                           FhRjbGllbnRAYXBpLmYtY2FyZS5pbzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\
                           AQoCggEBANWre49HRXDu6h+N8vxAeVr5TCbtCcG7jDWLq1aLaQF1k5X2HcFQ7Slw\
                           9KEzbjeAhfm95iNg4BKnmVRxcptdfuVbp0qNUirPOHvSw1eaczckFCHyXx9Sa4FR\
                           CYDMVU5tuWUQ8sXHWBZtlgvdf0fEBy32ArD6kSGitGxUzNJuIMgreHQSQiFv7u3q\
                           lRr9YwsFV7PBNnSFYjQ6Mvlqi47CR5lR6pY6Rnbbfi0rIFE68fHZpQZW7qDP+orV\
                           9Rtwq1IVPchJNmweM1UCAfZQ6b94oeUaKF8vX+9y7hfc+6rHEM5KbGZqr29wEAqq\
                           SA1aJiQL7cHSUu5Y9zHgrz0i1YxXP1sCAwEAAaOBhTCBgjAJBgNVHRMEAjAAMB0G\
                           A1UdDgQWBBQaWmDi+o/KCy7Mjw65BTpLkq+QxzAfBgNVHSMEGDAWgBS8Uy4SbZlr\
                           vxGWW2ypuhiHWtnGtDA1BgNVHR8ELjAsMCqgKKAmhiRodHRwOi8vd3d3LnlvdXJk\
                           b21haW4uY29tL2NhL2NybC5wZW0wDQYJKoZIhvcNAQELBQADggEBAK50frhRm3uo\
                           3WEXaInLovL9Ti8+6eP1wVtxCTXjwKSTepl2bh8B5mr1fh12uG54RS4tQjDVOWuC\
                           3EFTRqn53e92tnc+GShKp6F6Cuqew2T0Bp1oWRJAJ+TFY+UffgvoiXNV4fFH961l\
                           Zqoovwq134I8bpa0qCtUiTJOK1iRBGlnqAfRHmVgaFCwG1hhf9lKJbmlwwyUtYVC\
                           uVqANVmyTCgVJf+BcYfbNsiAj0MB/k98nhcq6LA9szRsPRbFElvLOv/vvtzhNLee\
                           AhmHJLnHmkaDtC2B8mSf9FAm+nyx065rzWcVySYu+rUAJ8++XSF6w/WtC26J3zD1\
                           1ype3Wfivdc=\
                           -----END CERTIFICATE-----");
    if (success != true) {
        QTLOGD << "append cert error: " << cert.lastErrorText();
        return false;
    }

    // Load the private key.
    success = privKey.LoadEncryptedPem(L"-----BEGIN PRIVATE KEY-----\
                                       MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDVq3uPR0Vw7uof\
                                       jfL8QHla+Uwm7QnBu4w1i6tWi2kBdZOV9h3BUO0pcPShM243gIX5veYjYOASp5lU\
                                       cXKbXX7lW6dKjVIqzzh70sNXmnM3JBQh8l8fUmuBUQmAzFVObbllEPLFx1gWbZYL\
                                       3X9HxAct9gKw+pEhorRsVMzSbiDIK3h0EkIhb+7t6pUa/WMLBVezwTZ0hWI0OjL5\
                                       aouOwkeZUeqWOkZ2234tKyBROvHx2aUGVu6gz/qK1fUbcKtSFT3ISTZsHjNVAgH2\
                                       UOm/eKHlGihfL1/vcu4X3PuqxxDOSmxmaq9vcBAKqkgNWiYkC+3B0lLuWPcx4K89\
                                       ItWMVz9bAgMBAAECggEAYqCMIT/Juu5dHYGdVnjAS5DlaNZjeYyDlLfKt+ET8DuA\
                                       i2kWpQQg5M8h7ELcLjxiGzxfvZba92FrckIHn9WRXHdpCg2fjukl7moEByzg3+QE\
                                       cwL4i3G08/UfCNfIzLHzMMaY+VghvgCJkSKFvO+sTLfQ2DZgxYDf/V1LShrRgPNP\
                                       fMWyeEUmbuttfwAM9c662khkjzqcuWfYLScfUfLN2FMVHG+4VEup6O70O4iVy8gy\
                                       Rb6EZdOxzj7TzCCXdSFV/bJD02TYwtC1V0YO659MGrtwt6Gz+85THLi9QOQjwYEy\
                                       EQ3s5FkSmmVMJOjXetG5ydX0oAaCLFYF8mftuwTWuQKBgQD52M/uqQLAI5C16TSr\
                                       yZafzKpE/OJBnk2wGx+LO+wUBfHQ3MGv/juWs1XHzbuv+yGEE21kCxhrnmHnKqq+\
                                       By0NV7b2n12bA2lYY3zEOo86Q3rmbzpy9/lIYxUTN69Y0u65E2LxRpbP19QGm5HY\
                                       CX81ngiA9eJ3BAkLZv/zzFggfQKBgQDa7paLCSFpaxKWpD5cvde/7NERx80ivCcb\
                                       +x0jiRsa6i9Em7OIAjM1sKV2noT+EwBHn4Y3JluZXe418XsP+51ldzZTJeY+VL+3\
                                       NPNSJRJdowfeGIXGCOWc6chw/Lcn3jSH86Ytwtdy3Br1VtRTucdm3GRkk1n4ydJx\
                                       DJf8NEz+twKBgQCqHNNGvlCfHhgTo9s29CTYXPO50S0EXJKsy2ro1D3jTEDfYs+F\
                                       0uYjr6tCRXP7WFPzp36d1WglLkuep9BlXmFwaj6rIMsNFn+NrP9wZCbNFtEBQM5d\
                                       JTXX8Y6R7SI4qjXcUbTWbqeUkHFOpnHg1GaGzTkhBUnSmy7FUrYG+yUtyQKBgCi+\
                                       wKvNnjdFYydAGA8gkde5Vkut2MK/K7QsbwbfDHlc3kExjR8h8a/rWVATPoMevC2Y\
                                       Rd1buS546c2GTLXzyR5KKoUdB5XQJgINy78dAScGIX+3JqZtn3YtmE1W6ytzUml+\
                                       8g2QNpK83hOM/mU6rR66o8CIH/WKcizyABNDFJVPAoGBAKmjujs6j2CG9wUQ0G91\
                                       Fy7OnDX3IgoOHyf5HyGzpCIt3x/4i6u0rx9BDBS0zW8r78KOwaPwyzXkvcWP5sT2\
                                       VD1ltxWyRWMNnmk1mPlIEaQlb8/ra5dXF0IxkA/l438sr0bvOla8oMFwS+9IXo6S\
                                       YsqC7uFMpOtN2sdAuoTHkao+\
                                       -----END PRIVATE KEY-----",L"client");
    if (success != true) {
        QTLOGD << "load key error: " << privKey.lastErrorText();
        return false;
    };

    // Associate the private key with the cert.
    success = cert.SetPrivateKey(privKey);
    if (success != true) {
        QTLOGD << "SetPrivateKey error: " << cert.lastErrorText();
        return false;
    }

    success = http.SetSslClientCert(cert);
    if (success != true) {
        return false;
    }

    QTLOGD << "init CkHttp success";
    return success;
}
