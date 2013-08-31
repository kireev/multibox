#include "cloudtablemodel.h"

CloudTableModel::CloudTableModel(const QList<QStringList> &strings,  QObject *parent)
    : QAbstractTableModel(parent), stringList(strings)

{
    header_data << "Name" << "Size" << "Date" << "Dir";
    //qDebug() << "blar " << stringList.at(0);

}

QVariant CloudTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.count())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0 )
            return stringList.at(index.row()).at(1);
        if (index.column() == 1 )
            return stringList.at(index.row()).at(3);
        if (index.column() == 2 )
            return stringList.at(index.row()).at(0);
        if (index.column() == 3 )
            return stringList.at(index.row()).at(2);


    }

    if (role == Qt::DecorationRole)
    {

        QPixmap pixmap1(":/img/browse.png");

        if ((stringList.at(index.row()).at(2)=="true") && (index.column() == 0 ))
            return pixmap1;

    }


        return QVariant();
}

QVariant CloudTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
            return QVariant();
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return header_data.at(section);
    }else{
        return QString("%1").arg( section + 1 );
    }
}



int CloudTableModel::columnCount(const QModelIndex &parent) const
{
        return 4;
}


int CloudTableModel::rowCount(const QModelIndex &parent) const
{
        return stringList.count();

}


bool CloudTableModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(position);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        QStringList lst;
        lst << "" << "" << "" << "";
        stringList.insert(3,lst);
    }

    endInsertRows();
    return true;
}

bool CloudTableModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(position);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        stringList.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool CloudTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::DisplayRole) {
        int row = index.row();

        QStringList s = value.toStringList();

        if (index.column() == 0 ){
            stringList[row][1]=s.at(1);
            }
        if (index.column() == 1 ){
            stringList[row][3]=s.at(3);
            }
        if (index.column() == 2 ){
            stringList[row][0]=s.at(0);
            }
        if (index.column() == 3 ){
            stringList[row][2]=s.at(2);
            }

        emit(dataChanged(index, index));

        return true;
    }

    return false;

}
