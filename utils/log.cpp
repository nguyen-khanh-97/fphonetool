#include "log.h"
#include <android/log.h>

#include <CkHttpRequest.h>
#include <CkHttpResponse.h>
#include <CkCert.h>
#include <CkPrivateKey.h>
#include <CkTask.h>
#include <QJsonDocument>

LogHelper* LogHelper::instance = nullptr;

LogHelper::LogHelper(): m_device("None"), m_appVersion("None"), m_token("None")
{

}

LogHelper::~LogHelper()
{

}

void LogHelper::qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#ifdef __DEBUG_MODE__
    QString tag = "[" + QString::fromUtf8(context.file) + "][" + context.function +
            "][" + QString::number(context.line) + "]";

    switch (type) {
    case QtDebugMsg:
        __android_log_print(ANDROID_LOG_DEBUG, "QTLOG", "%s %s", tag.toLocal8Bit().constData(), msg.toLocal8Bit().constData());
        break;
    case QtInfoMsg:
        __android_log_print(ANDROID_LOG_INFO, "QTLOG", "%s %s", tag.toLocal8Bit().constData(), msg.toLocal8Bit().constData());
        break;
    case QtWarningMsg:
        __android_log_print(ANDROID_LOG_WARN, "QTLOG", "%s %s", tag.toLocal8Bit().constData(), msg.toLocal8Bit().constData());
        break;
    case QtCriticalMsg:
        __android_log_print(ANDROID_LOG_ERROR, "QTLOG", "%s %s", tag.toLocal8Bit().constData(), msg.toLocal8Bit().constData());
        break;
    case QtFatalMsg:
        __android_log_print(ANDROID_LOG_FATAL, "QTLOG", "%s %s", tag.toLocal8Bit().constData(), msg.toLocal8Bit().constData());
        abort();
        break;
    }
#else

    QString log = "[" + QString::fromUtf8(context.file) + "][" + context.function +
            "][" + QString::number(context.line) + "] " + msg;
    if(nullptr != instance) {
        instance->writeLog(type, log);
    }
#endif
}

bool LogHelper::initCkHttp(CkHttp &http)
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

LogHelper *LogHelper::getInstance()
{
    if(nullptr == instance) {
        instance = new LogHelper();
        instance->initialize();
    }
    return instance;
}

void LogHelper::deleteInstance()
{
    if(nullptr != instance) {
        delete instance;
        instance = nullptr;
    }
}

void LogHelper::initialize()
{
    if(m_initialize) {
        return;
    }

    // install qt message
    qInstallMessageHandler(qtMessageHandler);

    initCkHttp(m_http);
    m_http.SetRequestHeader("Token", "df13e3b2-2801-11ec-a9da-985aeb8ef874");
    m_http.SetRequestHeader("Content-Type", "application/json");
    m_dataForm["AppName"] = "F-Phone-Tool";
    m_dataForm["device"] = m_device;
    m_dataForm["app_version"] = m_appVersion;
    m_dataForm["token"] = m_token;
}

void LogHelper::writeLog(QtMsgType type, const QString &msg)
{
    Q_UNUSED(type);
    m_dataForm["log"] = msg;

    const char * url = "https://api8.fity.one/v1/logs/write";

    CkTask *task = m_http.PostJsonAsync(url, QJsonDocument(m_dataForm).toJson().data());
    if(nullptr != task){
        task->Run();
    }
}

void LogHelper::setupDevice(QString device, QString appVersion)
{
    if(m_device != device){
        m_device = device;
        m_dataForm["device"] = m_device;
    }
    if(m_appVersion != appVersion){
        m_appVersion = appVersion;
        m_dataForm["app_version"] = m_appVersion;
    }
}

void LogHelper::setToken(QString token)
{
    if(m_token != token){
        m_token = token;
        m_dataForm["token"] = m_token;
    }
}
