#ifndef CloudTableModel_H
#define CloudTableModel_H

#include <QAbstractListModel>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <QPixmap>

class CloudTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CloudTableModel(const QList<QStringList> &strings, QObject *parent = 0);



    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);


private:
    QList<QStringList> stringList;
        QStringList header_data;

};

#endif // CloudTableModel_H
