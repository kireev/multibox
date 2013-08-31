#ifndef SINGLETABLE_H
#define SINGLETABLE_H

#include "cloudtableview.h"
#include <QtGui>


class SingleTable : public QObject
{
    Q_OBJECT
private:
    QHBoxLayout * HorizontalStringLayout_;

    QLineEdit* PathLineEdit_;
    QItemSelectionModel *SelectionModel_;

public:
    SingleTable();
    CloudTableView* Ctv;
    QVBoxLayout* VerticalLayout;
        QComboBox* FileSystemCombo_;





    //    bool firstRun;

public slots:

    void changePathInLineEdit(const QString& obj,const QString& folder);
    void selectionArrangement();


private slots:
    void selectChanged(const QItemSelection&,const QItemSelection&);
        void comboChange(int);

signals:
    void stabilizeViewSignal();
};

#endif // SINGLETABLE_H
