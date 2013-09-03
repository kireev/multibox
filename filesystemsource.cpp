#include "filesystemsource.h"

FileSystemSource::FileSystemSource()
{
}

FileSystemSource::~FileSystemSource()
{
}

QList<QStringList> FileSystemSource::listFiles(const QString &path)
{

    QDir mDir(path);

    QStringList lst;
    QList<QStringList> tempList;
    QString isReallyDir;

    foreach(QFileInfo mitm, mDir.entryInfoList())
    {
        if (mitm.isDir()) isReallyDir="true"; else isReallyDir="false";

        if (mitm.fileName()=="." || mitm.fileName()=="..") continue;
        lst << mitm.lastModified().toString("yyyy-MM-dd")
            <<  mitm.fileName() << isReallyDir
           //  << QString::number(mitm.size());
                << convertSizeToReadable(QString::number(mitm.size()),mitm.isDir());


        tempList << lst;
        lst.clear();

    }

       //     qDebug() << "Actual size " <<                 convertSizeToReadable("2111311024");

    return tempList;
}

QList<QStringList> FileSystemSource::getRoot()
{

    currentViewIndex=0;

    fullPath="/";
    isRoot=true;

    pathStr.position=0;
    pathStr.path="/";
    currentPath << pathStr;



    return listFiles("/");

}


void FileSystemSource::setCurrentPathAndPosition(int pos ,const QString& str)
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

QList<QString> FileSystemSource::updateSelectionInfo(QList<int> lst)
{
//    qDebug() << currentPath.last().path;

    QString sss = "shit";
    QList<QString> d;
    d << sss;

        return d;



}

