#ifndef FILESYSTEMSOURCE_H
#define FILESYSTEMSOURCE_H

#include "commonsource.h"

class FileSystemSource : public CommonSource
{
        Q_OBJECT
public:
    FileSystemSource();
    ~FileSystemSource();
    virtual QList<QStringList> listFiles(const QString &path);
    virtual QList<QStringList> getRoot();

    virtual void setCurrentPathAndPosition(int,const QString&);
    virtual QList<QString> updateSelectionInfo(QList<int>);
};

#endif // FILESYSTEMSOURCE_H
