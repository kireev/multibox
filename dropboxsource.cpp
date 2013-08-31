#include "dropboxsource.h"

DropBoxSource::DropBoxSource()
{


}

DropBoxSource::~DropBoxSource()
{
}

QList<QStringList> DropBoxSource::listFiles(const QString& path)
{
    // qDebug() << convertSizeToReadable("1400");

    QString line;
    /////////////////////// read_from_file
    //    QFile file_test;
    //    qDebug() << QDir::currentPath();
    //    //QFile::copy()
    //    file_test.setFileName(QDir::currentPath()+"/123.txt");

    //    if (!file_test.open(QIODevice::ReadOnly)) qDebug() << "false2";


    //    QTextStream in(&file_test);
    //    in.setAutoDetectUnicode(true);

    //    while (!in.atEnd()) {
    //        line = in.readLine()+"\r\n";
    //    }
    //////////////////////


    QString lineWithPath= QString("https://api.dropbox.com/1/metadata/dropbox")+
            path.toUtf8()+
            QString("/?oauth_consumer_key=pzt3m9b6yxfj79t&oauth_token=8dsmth4k6h4r4z9&oauth_signature_method=PLAINTEXT&oauth_signature=98mhrfng8fwnugz%26y60lva5ene06yga&oauth_timestamp=1363020679&oauth_nonce=7122");

    line= getStringFromHttpResponse(lineWithPath);
    //  qDebug() << line;
    //qDebug() << getStringFromHttpResponse("https://api.dropbox.com/1/metadata/dropbox//sync?oauth_consumer_key=pzt3m9b6yxfj79t&oauth_token=8dsmth4k6h4r4z9&oauth_signature_method=PLAINTEXT&oauth_signature=98mhrfng8fwnugz%26y60lva5ene06yga&oauth_timestamp=1363020679&oauth_nonce=7122");

    int pos=0;
    QRegExp rxWholeRegEx("\\[(.*)\\]");
    pos = rxWholeRegEx.indexIn(line);
    QList<QStringList> resultList;
    resultList.clear();

    if (pos > -1) {
        QString value1 = rxWholeRegEx.cap(1);
        QStringList parsedListTemp;

        QRegExp rxItemRegEx("(\\{.*\\})");
        rxItemRegEx.setMinimal(true);
        pos=0;
        while ((pos = rxItemRegEx.indexIn(value1, pos)) != -1) {
            parsedListTemp << rxItemRegEx.cap(1);
            //     qDebug() << "ZZZ"<< rxItemRegEx.cap(1);
            pos += rxItemRegEx.matchedLength();
        }

        QStringList temp1;
        // QRegExp rxFinalRegEx("modified\": \"(.+)\".+path\": \".*/.*/([^/.]+)\", \"is_dir\": (.+), \"icon.+size\": \"(.+)\"");
        QRegExp rxFinalRegEx("modified\": \".*(\\d{2} \\w{3} \\d{4} \\d{2}:\\d{2}:\\d{2}).*\",.*path\": \".*/([^/]+)\", \"is_dir\": (.+), \"icon.+size\": \"(.+)\"");
        rxFinalRegEx.setMinimal(true);
        foreach (const QString &str, parsedListTemp) {
            rxFinalRegEx.indexIn(str);
            temp1.clear();
            //   qDebug() << "FINAL "  << rxFinalRegEx.cap(1); //.toString("yyyy-MM-d");


            //convert size to formatted string
            QString rxExpr;
            int multiplier;

            if (rxFinalRegEx.cap(4).contains("bytes"))
            {
                rxExpr="(.*) bytes";
                multiplier=1;
            }
            if (rxFinalRegEx.cap(4).contains("KB"))
            {
                rxExpr="(.*) KB";
                multiplier=1024;
            }
            if (rxFinalRegEx.cap(4).contains("MB"))
            {
                rxExpr="(.*) MB";
                multiplier=1024*1024;
            }

            QRegExp rx(rxExpr);
            rx.indexIn(rxFinalRegEx.cap(4));
            QString sstr = rx.cap(1);

//            if (rxFinalRegEx.cap(3)=="true")
//            {
//                sstr="DIR";
//            }
//            else
//            {
//                            qDebug() << "ss" << sstr;
                double varSize = sstr.toDouble()*multiplier;
                sstr=QString::number(varSize, 'f',0);
 //           }
            //qDebug() << "act string " << sstr;




            QString tmpTime= QDateTime::fromString(rxFinalRegEx.cap(1), "d MMM yyyy hh:mm:ss").toString("yyyy-MM-dd");

            temp1 << tmpTime << convertFromUTF16(rxFinalRegEx.cap(2))
                  << rxFinalRegEx.cap(3)
                  << convertSizeToReadable(sstr,rxFinalRegEx.cap(3)=="true" ? true : false);
            resultList << temp1;

        }
    }

    //qDebug() << resultList;
    emit readyToUpdateSignal(true);
    return resultList;

}

QList<QStringList> DropBoxSource::getRoot()
{

    currentViewIndex=0;

    fullPath="/";
    isRoot=true;

    pathStr.position=0;
    pathStr.path="/";
    currentPath << pathStr;

    return listFiles("/");

}

QString DropBoxSource::convertFromUTF16(QString str)
{
    QString strComplete=str;
    QRegExp rx("u([0-9a-f]{4})");
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {

        QString charToInt="0x"+rx.cap(1);
        strComplete.replace("\\u"+rx.cap(1),QChar(charToInt.toInt(0,16)));
        pos += rx.matchedLength();
    }

    return strComplete;
}



void DropBoxSource::setCurrentPathAndPosition(int pos,const QString& str)
{
    pathStr.position=pos;
    pathStr.path=str+ "/";

    //    // now we want to understand what path we need to display. This is temp variable
    fullPath="";

    // if level-up
    if (pathStr.path.contains("../"))
    {
        currentViewIndex=currentPath.last().position;
        currentPath.removeLast();
    }
    //if it's a directory
    else
    {
        currentPath << pathStr;
        currentViewIndex=0;
    }

    //create fullpath string which contains fullpath to directory
    foreach (pathStructure str, currentPath) {
        //qDebug() << str.path << str.position;
        fullPath = fullPath+str.path;
    }

    // set isRoot flag
    if (fullPath=="/") {isRoot=true;}
    else {isRoot=false;}


}

QList<QString> DropBoxSource::updateSelectionInfo(QList<int> lst)
{
    QString sss = "shit";
    QList<QString> d;
    d << sss;
    return d;
}


