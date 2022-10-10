#include "../Include/Http.h"
#include <QEventLoop>
#include "../Include/Thread.h"
QMap<QString,QString> QtTool::Http::headers;

void QtTool::Http::append(QString* query, const QString & key, const QString & value)
{
    if(query->length()){
        *query+='&';
    }
    *query+=key+'='+value;
}

QtTool::Http::Response QtTool::Http::Get(const QString & url, const QMap<QString,QString> & args)
{
    QString query = "";
    auto it = args.begin();
    while(it!=args.end()){
        append(&query,it.key(),it.value());
    }
    return Get(url,query);
}

QtTool::Http::Response QtTool::Http::Get(const QString & url, const QString & key, const QString & value)
{
    QString query = "";
    append(&query,key,value);
    return Get(url,query);
}

QtTool::Http::Response QtTool::Http::Get(const QString & url, const QJsonObject & arg)
{
    QString query = "";
    auto iter = arg.begin();
    while (iter != arg.end()){
        append(&query,iter.key(),iter.value().toString());
        iter++;
    }
    return Get(url,query);
}

QtTool::Http::Response QtTool::Http::Get(const QString & url, const QString & query)
{
    return Get(url + (query.length()?'?'+query:query));
}

/**
 * @brief QtTool::QHttp::Get Get主请求方法
 * @param url
 * @return
 */
QtTool::Http::Response QtTool::Http::Get(const QString & url)
{
    QUrl u = QUrl(url);
    QNetworkRequest request;
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QtTool::Http::Response r;
    request.setUrl(u);
    if(!headers.empty()){
        auto iter = headers.begin();
        while(iter!=headers.end()){
            request.setRawHeader(iter.key().toUtf8(),iter.value().toUtf8());
            iter++;
        }
    }
    qDebug()<<url;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    r.StatusCode = reply->error();
    r.Content = reply->readAll();
    return r;
}


QFuture<QtTool::Http::Response> QtTool::Http::GetAsync(const QString & url,
                                                       const QMap<QString,QString> & args)
{
    return RunAsync([=]{return Get(url,args);});
}

QFuture<QtTool::Http::Response> QtTool::Http::GetAsync(const QString & url, const QString & key, const QString & value)
{
    return RunAsync([=]{return Get(url,key,value);});
}

QFuture<QtTool::Http::Response> QtTool::Http::GetAsync(const QString & url, const QJsonObject & arg)
{
    return RunAsync([=]{return Get(url,arg);});
}

QFuture<QtTool::Http::Response> QtTool::Http::GetAsync(const QString & url, const QString & query)
{
    return RunAsync([=]{return Get(url,query);});
}

QFuture<QtTool::Http::Response> QtTool::Http::GetAsync(const QString & url)
{
    return RunAsync([=]{return Get(url);});
}


/**
 * @brief QtTool::QHttp::Post 主请求方法
 * @param url
 * @param formData
 * @return
 */
QtTool::Http::Response QtTool::Http::Post(const QString & url, const QJsonObject & formData)
{
    QNetworkRequest request;
    QByteArray postData;
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QtTool::Http::Response r;
    request.setUrl(QUrl(url));
    if(!headers.empty()){
        auto iter = headers.begin();
        while(iter!=headers.end()){
            request.setRawHeader(iter.key().toUtf8(),iter.value().toUtf8());
            iter++;
        }
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    qDebug()<<request.header(QNetworkRequest::ContentTypeHeader);
    postData.clear();
    postData.append(QJsonDocument(formData).toJson(QJsonDocument::Compact));
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    QNetworkReply *reply = manager.post(request,postData);
    QObject::connect(reply, SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    r.StatusCode = reply->error();
    r.Content = reply->readAll();
    return r;
}

QtTool::Http::Response QtTool::Http::Post(const QString & url)
{
    QJsonObject o;
    return Post(url,o);
}

QFuture<QtTool::Http::Response> QtTool::Http::PostAsync(const QString & url, const QJsonObject & formData)
{
    return RunAsync([=]{return Post(url,formData);});
}

QFuture<QtTool::Http::Response> QtTool::Http::PostAsync(const QString & url)
{
    return RunAsync([=]{return Post(url);});
}

void QtTool::Http::SetHeader(const QString & key, const QString & value)
{
    headers[key] = value;
}

void QtTool::Http::SetHeader(const QJsonObject & arg)
{
    auto iter = arg.begin();
    while (iter != arg.end()){
        headers[iter.key()]=iter.value().toString();
        iter++;
    }
}

void QtTool::Http::SetHeader(const QMap<QString, QString> & headers)
{
    auto iter = headers.begin();
    while (iter != headers.end()){
        Http::headers[iter.key()]=iter.value();
        iter++;
    }
}

void QtTool::Http::RemoveHeader(const QString & key)
{
    if(headers.contains(key)){
        headers.remove(key);
    }
}
