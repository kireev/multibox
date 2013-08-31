#ifndef COMMONSOURCE_H
#define COMMONSOURCE_H

#include <QList>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QtNetwork/QSslSocket>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
class QSslSocket;
QT_END_NAMESPACE

//contains position of directory entered and name of this directory
struct pathStructure {
    int position;
    QString path;

};


class CommonSource : public QObject
{
    Q_OBJECT
public:
    CommonSource();
   ~CommonSource();

    QString m_currentPath;

    QString getStringFromHttpResponse(const QString &str);

    //output - date,name,dir,size
    virtual QList<QStringList> listFiles(const QString& path)=0;

    virtual QList<QStringList> getRoot()=0;


    virtual void setCurrentPathAndPosition(int, const QString&)=0;

    virtual QList<QString> updateSelectionInfo(QList<int>)=0;

     QString convertSizeToReadable(const QString& str, bool isDir);
    const QString& convertToDateTime(const QString& str);


private:

signals:
    void readyToUpdateSignal(bool);
    // set current path
public:
    pathStructure pathStr;      //temp structure
    QString fullPath;         //contains full string from currentPath
    bool isRoot;      //this flag is used whether we are in root directory of source
    QList<pathStructure> currentPath;         //contains list of path pieces


    int currentViewIndex;

    // positions of selected rows
    QList<QString> m_selectedRowsPaths;



};



#endif // COMMONSOURCE_H




////    CHUNK_SIZE=4

////    #Set to 1 to enable DEBUG mode
////    DEBUG=0

////    #Set to 1 to enable VERBOSE mode
////    VERBOSE=1

////    #Curl location
////    #If not set, curl will be searched into the $PATH
////    #CURL_BIN="/usr/bin/curl"

////    #Temporary folder
////    TMP_DIR="/tmp"

////    #Don't edit these...
////    apiAPI_REQUEST_TOKEN_URL="https://api.dropbox.com/1/oauth/request_token"
////    API_USER_AUTH_URL="https://www2.dropbox.com/1/oauth/authorize"
////    API_ACCESS_TOKEN_URL="https://api.dropbox.com/1/oauth/access_token"
////    API_CHUNKED_UPLOAD_URL="https://api-content.dropbox.com/1/chunked_upload"
////    API_CHUNKED_UPLOAD_COMMIT_URL="https://api-content.dropbox.com/1/commit_chunked_upload"
////    API_UPLOAD_URL="https://api-content.dropbox.com/1/files_put"
////    API_DOWNLOAD_URL="https://api-content.dropbox.com/1/files"
////    API_DELETE_URL="https://api.dropbox.com/1/fileops/delete"
////    API_METADATA_URL="https://api.dropbox.com/1/metadata"
////    API_INFO_URL="https://api.dropbox.com/1/account/info"
////    API_MKDIR_URL="https://api.dropbox.com/1/fileops/create_folder"
////    API_SHARES_URL="https://api.dropbox.com/1/shares"
////    APP_CREATE_URL="https://www2.dropbox.com/developers/apps"
////    RESPONSE_FILE="$TMP_DIR/du_resp_$RANDOM"
////    CHUNK_FILE="$TMP_DIR/du_chunk_$RANDOM"
////    BIN_DEPS="sed basename date grep stat dd printf"
////    VERSION="0.11.5"

////    print " > Listing \"$1\"... "
////    time=$(utime)
////    $CURL_BIN $CURL_ACCEPT_CERTIFICATES -s --show-error --globoff -i -o "$RESPONSE_FILE" "$API_METADATA_URL/$ACCESS_LEVEL/$DIR_DST?oauth_consumer_key=$APPKEY&oauth_token=$OAUTH_ACCESS_TOKEN&oauth_signature_method=PLAINTEXT&oauth_signature=$APPSECRET%26$OAUTH_ACCESS_TOKEN_SECRET&oauth_timestamp=$time&oauth_nonce=$RANDOM"

//    QString m_accessLevel="dropbox";
//    QString m_appSecret="";
//    QString m_oauthConsumerKey="pzt3m9b6yxfj79t";
//    QString m_oauthToken="8dsmth4k6h4r4z9";
//    QString m_oauthSignatureMethod="PLAINTEXT";
//    QString m_oauthSignature;
//        m_oauthSignature="98mhrfng8fwnugz" && "%26" && "y60lva5ene06yga";

//    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
//    QString random = QString::number(qrand() % 9999);

//    QDateTime timeEpoch;
//    QString oauthTimestamp = timeEpoch.currentDateTime().toTime_t();

//    //for_list_files
//    QString m_apiMetadataUrl = "https://api.dropbox.com/1/metadata/dropbox//sync?oauth_consumer_key=pzt3m9b6yxfj79t&oauth_token=8dsmth4k6h4r4z9&oauth_signature_method=PLAINTEXT&oauth_signature=98mhrfng8fwnugz%26y60lva5ene06yga&oauth_timestamp=1363020679&oauth_nonce=7122";

//    //for_simple_upload
//    QString m_apiSimpleUpload = "https://api-content.dropbox.com/1/files_put/dropbox//sync?oauth_consumer_key=$APPKEY&oauth_token=$OAUTH_ACCESS_TOKEN&oauth_signature_method=PLAINTEXT&oauth_signature=$APPSECRET%26$OAUTH_ACCESS_TOKEN_SECRET&oauth_timestamp=$time&oauth_nonce=$RANDOM";
