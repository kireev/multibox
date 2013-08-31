#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
 Q_OBJECT
public:
    MySortFilterProxyModel();
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
//    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
//    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
//    QMap<QPersistentModelIndex, QPersistentModelIndex> mapping;

    double getRealSize(const QString&) const;

protected:

};

#endif // MYSORTFILTERPROXYMODEL_H
