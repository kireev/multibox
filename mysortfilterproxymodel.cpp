#include "mysortfilterproxymodel.h"
#include <QDebug>
#include <QDateTime>
#include <QApplication>

MySortFilterProxyModel::MySortFilterProxyModel()
{

}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left,
                                      const QModelIndex &right) const
{

    //True if left < right
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    QString dirLeftColumn = sourceModel()->index(left.row(),1).data().toString();
    QString dirRightColumn = sourceModel()->index(right.row(),1).data().toString();

    const QString& leftString = leftData.toString();
    const QString& rightString = rightData.toString();


    // if (right.column()==0)
    switch (left.column())
    {
    case 0:
    {
        //.contains("..")
        if (leftString=="..") {return false;} // greater
        if (rightString=="..")  {return false;}

        if ((dirLeftColumn.contains("DIR")) && (dirRightColumn.contains("DIR")))
        {
            //    qDebug() << "1";
            if (QString::localeAwareCompare(leftString, rightString) < 0) return true;
        }

        if ((dirLeftColumn=="DIR") && (!(dirRightColumn=="DIR")))
        {
            //     qDebug() << "2";
            return true;
        }

        if ((!(dirLeftColumn=="DIR")) && (!(dirRightColumn=="DIR")))
        {
            qDebug() << getRealSize("zzz");
            //  qDebug() << "3";
            if (QString::localeAwareCompare(leftString, rightString) < 0) return true; //greater

        }
        break;
    }



    case 1:     //size
    {
        //     qDebug() << "1one";
  //      qDebug() << getRealSize(leftString);



        if (leftString==".." || leftString.isEmpty()) {return false;} // greater
        if (rightString==".." || rightString.isEmpty())  {return false;}

        if ((dirLeftColumn.contains("DIR")) && (dirRightColumn.contains("DIR")))
        {
            if (QString::localeAwareCompare(leftString, rightString) < 0) return true;
        }

        if ((dirLeftColumn.contains("DIR")) && (!dirRightColumn.contains("DIR")))
        {
            return true;
        }

        if ((!dirLeftColumn.contains("DIR")) and (!dirRightColumn.contains("DIR")))
        {
                    //  qDebug() << "3";
            if (getRealSize(leftString) < getRealSize(rightString)) return true;
            return true; //greater
        }

        break;
    }

    default:
        break;
    }
}

double MySortFilterProxyModel::getRealSize(const QString& origString) const
{
        //convert size to formatted string
        QString rxExpr;
        int multiplier;

        if (origString.contains("Kb"))
        {
            rxExpr="(.*)Kb";
            multiplier=1024;
        }
        if (origString.contains("Mb"))
        {
            rxExpr="(.*)Mb";
            multiplier=1024*1024;
        }
        if (origString.contains("Gb"))
        {
            rxExpr="(.*)Gb";
            multiplier=1024*1024*1024;
        }

        QRegExp rx(rxExpr);
        rx.indexIn(origString);
        QString sstr = rx.cap(1);

    //            if (rxFinalRegEx.cap(3)=="true")
    //            {
    //                sstr="DIR";
    //            }
    //            else
    //            {
    //                            qDebug() << "ss" << sstr;
            double varSize = sstr.toDouble()*multiplier;
            return varSize;
    //        //sstr=QString::number(varSize, 'f',0);
    ////           }
    //    //qDebug() << "act string " << sstr;

}



//qDebug() << "LEFT" << leftString << dirLeftColumn;
//    qDebug() << "RIGHT" << rightString << dirRightColumn;

//   qDebug() << "experimnet" << QString::localeAwareCompare("!!!!", "123");
//qDebug() << left.column();

//    if (leftData.type() == QVariant::DateTime) {
//        return leftData.toDateTime() < rightData.toDateTime();
//    } else {
//        QRegExp *emailPattern = new QRegExp("([\\w\\.]*@[\\w\\.]*)");

//        if(left.column() == 1 && emailPattern->indexIn(leftString) != -1)
//            leftString = emailPattern->cap(1);

//        if(right.column() == 1 && emailPattern->indexIn(rightString) != -1)
//            rightString = emailPattern->cap(1);
//        delete emailPattern;

// test if it's a level-up directory string '..'



//QModelIndex MySortFilterProxyModel::mapToSource(const QModelIndex &proxyIndex) const
//    {
//        if (!proxyIndex.isValid())
//            return QModelIndex();
//        return mapping.key(proxyIndex);
//    }

// QModelIndex  MySortFilterProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
//    {
//        if (!sourceIndex.isValid())
//            return QModelIndex();
//        return mapping.value(sourceIndex);
//    }



//        if ((!dirLeftColumn.contains("DIR")) and (dirRightColumn.contains("DIR")))
//        {
//                        qDebug() << "4";
////            qDebug() << "LEFT" << leftString << dirLeftColumn;
////                qDebug() << "RIGHT" << rightString << dirRightColumn;
//            return true; //NOT DIR less than DIR
//        }

//       qDebug() << "5";
//qDebug() << "LEFT" << leftString << dirLeftColumn;
//qDebug() << "RIGHT" << rightString << dirRightColumn;

//qDebug() << "nothing else matters";



//        if (dirLeftColumn.contains("DIR") && !dirRightColumn.contains("DIR"))
//        {
//            qDebug() << left;
//          //  qDebug() << "Got it2";
//            if (QString::localeAwareCompare(leftString, rightString) < 0) return false;

//        }

//       return false;
