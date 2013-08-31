#ifndef DROPBOXSOURCE_H
#define DROPBOXSOURCE_H

#include "commonsource.h"



class DropBoxSource : public CommonSource
{
    Q_OBJECT
public:
    DropBoxSource();
    ~DropBoxSource();

    virtual QList<QStringList> listFiles(const QString& path);
    virtual QList<QStringList> getRoot();
   // QByteArray getStringFromHttpResponse(const QString &str);
    QString convertFromUTF16(QString str);

    virtual void setCurrentPathAndPosition(int,const QString&);
    virtual QList<QString> updateSelectionInfo(QList<int>);


private:


    QString m_accessLevel;
    QString m_appSecret;
    QString m_oauthConsumerKey;
    QString m_oauthToken;
    QString m_oauthSignatureMethod;
    QString m_oauthSignature;




public:




};


#endif // DROPBOXSOURCE_H
