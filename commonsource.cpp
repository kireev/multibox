#include "commonsource.h"

CommonSource::CommonSource()
{

}

CommonSource::~CommonSource()
{
}


 QString CommonSource::convertSizeToReadable(const QString & str, bool isDir)
{
   // qDebug() << "size" << str;

    double varSize = str.toDouble();

   // qDebug() << QString::number(varSize/1024, 'f', 1);;

    if (isDir) return "DIR";
    if (varSize<1024) return "1Kb";
    if (varSize<1048576) return QString::number(varSize/1024, 'f', 1)+"Kb";
    if (varSize<1073741824) return QString::number(varSize/(1024*1024), 'f', 1)+"Mb";

    return QString::number(varSize/(1024*1024*1024), 'f', 1)+"Gb";

}

const QString& CommonSource::convertToDateTime(const QString & str)
{

}

QString CommonSource::getStringFromHttpResponse(const QString &str)
{
    QNetworkRequest request;
    request.setUrl(QUrl(str));
    //request.setUrl(QUrl("https://api.dropbox.com/1/metadata/dropbox//sync?oauth_consumer_key=pzt3m9b6yxfj79t&oauth_token=8dsmth4k6h4r4z9&oauth_signature_method=PLAINTEXT&oauth_signature=98mhrfng8fwnugz%26y60lva5ene06yga&oauth_timestamp=1363020679&oauth_nonce=7122"));

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(request);

    QTimer tT;
    tT.setSingleShot(true);
    tT.start(90000);

    QEventLoop eventLoop;

    connect(&tT, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

    eventLoop.exec();


 //   qDebug() << reply->readAll();

    if (tT.isActive() & reply->error()==0)
    {

        return reply->readAll();
    }

    if (reply->error()!=0)
    {
        if (reply->error()!=0) return "ConnectionProblems";
    }

}

