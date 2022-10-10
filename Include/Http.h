#ifndef QHTTP_H
#define QHTTP_H
#include <QtNetwork/QNetworkReply>
#include <QFuture>
#include <QJsonObject>
namespace QtTool
{
    class Http
    {
        public:
            class Response{
                public:
                    QNetworkReply::NetworkError StatusCode;
                    QByteArray Content;
            };
        private:
            static QMap<QString,QString> headers;
            static void append(QString* url,const QString & key,const QString & value);
        public:
            static Response Get(const QString & url,const QMap<QString,QString> & args);
            static Response Get(const QString & url,const QString & key,const QString & value);
            static Response Get(const QString & url,const QJsonObject & arg);
            static Response Get(const QString & url,const QString & query);
            static Response Get(const QString & url);

            static QFuture<Response> GetAsync(const QString & url,const QMap<QString,QString> & args);
            static QFuture<Response> GetAsync(const QString & url,const QString & key,const QString & value);
            static QFuture<Response> GetAsync(const QString & url,const QJsonObject & arg);
            static QFuture<Response> GetAsync(const QString & url,const QString & query);
            static QFuture<Response> GetAsync(const QString & url);

            static Response Post(const QString & url,const QJsonObject & formData);
            static Response Post(const QString & url);

            static QFuture<Response> PostAsync(const QString & url,const QJsonObject & formData);
            static QFuture<Response> PostAsync(const QString & url);

            static void SetHeader(const QString & key,const QString & value);
            static void SetHeader(const QJsonObject & value);
            static void SetHeader(const QMap<QString,QString> & headers);
            static void RemoveHeader(const QString & key);
    };
}
#define POST QHttp::Post
#define POST_ASYNC QHttp::PostAsync
#define GET QHttp::Get
#define GET_ASYNC QHttp::GetAsync

#endif // QHTTP_H
