#include "singletable.h"
#include "paintdelegate.h"


SingleTable::SingleTable()
{

    Ctv = new CloudTableView(0);

    // change PathLine in QlineEdit
    connect(Ctv,SIGNAL(dblClickOnItem(const QString&,const QString&)),this,SLOT(changePathInLineEdit(const QString&,const QString&)));

    selectionArrangement();

    // Override dotted rectangle in view
    Ctv->setItemDelegate(new PaintDelegate());



    HorizontalStringLayout_ = new QHBoxLayout;
    PathLineEdit_ = new QLineEdit();
    PathLineEdit_->setReadOnly(true);
    PathLineEdit_->setText("/");
    FileSystemCombo_ = new QComboBox();

    QStringList comboItems;
    comboItems  << "FileSystem" << "DropBox";
    FileSystemCombo_->addItems(comboItems);

    HorizontalStringLayout_->addWidget(FileSystemCombo_,1);  //left
    HorizontalStringLayout_->addWidget(PathLineEdit_,2);    //right

    VerticalLayout= new QVBoxLayout();

    VerticalLayout->addLayout(HorizontalStringLayout_);
    VerticalLayout->addWidget(Ctv);

    //connect combo
    connect(FileSystemCombo_,SIGNAL(currentIndexChanged(int)),this,SLOT(comboChange(int)));

    //set selectionmodel
    connect(Ctv,SIGNAL(initDone(bool)),this,SLOT(selectionArrangement()));

}

void SingleTable::comboChange(int idx)
{
//    qDebug() << "idx" << idx;
    Ctv->initModel(idx);
}


void SingleTable::selectChanged(const QItemSelection&, const QItemSelection&)
{

    // pass indexes to CloutTableView
    Ctv->selectChanged(SelectionModel_->selectedIndexes());

    //qDebug() << SelectionModel_;

}

void SingleTable::changePathInLineEdit(const QString& obj,const QString& folder)
{
            emit stabilizeViewSignal();
    this->PathLineEdit_->setText(folder);
}

void SingleTable::selectionArrangement()
{


    // Model holds selected rows
    SelectionModel_ = Ctv->selectionModel();

    connect(SelectionModel_,SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),this,SLOT(selectChanged(const QItemSelection&,const QItemSelection&)));
    //prevent loss of focus on tabs by pressing arrow keys
    connect(SelectionModel_,SIGNAL(currentChanged(QModelIndex,QModelIndex)),Ctv,SLOT(cellChanged(QModelIndex,QModelIndex)));
    //connect(SelectionModel_,SIGNAL(currentChanged(QItemSelection,QItemSelection)),this,SLOT(selectChanged(const QItemSelection&,const QItemSelection&)));

}
