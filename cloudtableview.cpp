#include <QtGui>
#include <QItemSelection>
#include <QList>
#include "cloudtableview.h"


CloudTableView::CloudTableView(int modelNum)
{
    cs=0;
    CTModel=0;
    myProxyModel = new MySortFilterProxyModel();
    myProxyModel->setDynamicSortFilter(true);
 //   myProxyModel->setFilterKeyColumn(0);

    initModel(modelNum);
    this->setSortingEnabled(true);
    this->sortByColumn(0,Qt::AscendingOrder);




    installEventFilter(this);   // event filter for using keyboard


    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(dblClick(QModelIndex)));
    //    connect(this,SIGNAL(activated(QModelIndex)),this,SLOT(verticalScrollbarValueChanged(int)));
    //    connect(this,SIGNAL(entered(QModelIndex)),this,SLOT(qTest()));

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(sheetContextMenu(const QPoint &)));

    //Reimplement signal from QWidget
    connect(this,SIGNAL(focusOutEvent(QFocusEvent*)),this,SLOT(outOfFocusHappend()));

}

void CloudTableView::dblClick(QModelIndex q)
{

    // wait until source returns data
    if (!readyToUpdateFlag) return;


    // if it's not directory return.
    if (this->model()->data(this->model()
                            ->index(q.row(),3)).toString()=="false") return;




    // qDebug() << "first"  << ConvertIndexToRealModel(this->model()->index(q.row(),3));
    // qDebug() << "second" << this->model()->index(q.row(),3);
    //    qDebug() << " OK1 " << CTModel->data(
    //                    ConvertIndexToRealModel(myProxyModel->index(q.row(),0)),
    //                    Qt::DisplayRole).toString();


    cs->setCurrentPathAndPosition(this->currentIndex().row(),
                                  CTModel->data(
                                      ConvertIndexToRealModel(myProxyModel->index(q.row(),0)),
                                      Qt::DisplayRole).toString() );

    //create strings from source
    QList<QStringList> d;

    readyToUpdate(false);;
    //this->setEnabled(false);

    d=cs->listFiles(cs->fullPath);

    readyToUpdate(true);;
    //this->setEnabled(true);
    this->setFocus();

    // clean model completly
    CTModel->removeRows(0,CTModel->rowCount(),QModelIndex());

    // rowNumbers contains number of rows depending of Root or Not-Root
    int rowNumbers;
    int rowIter;

    // insert '..' or not
    if (cs->isRoot)
    {rowNumbers=d.count();
        rowIter=0;
        CTModel->insertRows(0,rowNumbers,QModelIndex());
    }
    else
    {
        // rows plus '..'
        rowNumbers=d.count()+1;
        rowIter=1;

        CTModel->insertRows(0,rowNumbers,QModelIndex());
        QModelIndex index = this->model()->index(0, 0, QModelIndex());
        QStringList lst;
        lst << ""  << ".."  << ""  << "";
        CTModel->setData(index,lst,Qt::DisplayRole);
        d.prepend(lst);
    }


    // insert data in rows
    for (rowIter; rowIter<rowNumbers; rowIter++)
    {
        for (int col=0; col<4; col++)
        {
            QModelIndex index = this->model()->index(rowIter, col, QModelIndex());
            CTModel->setData(index,d.at(rowIter),Qt::DisplayRole);

        }
    }

        myProxyModel->setSourceModel(CTModel);
    //set current index depending on is it Level-Up or Into-Directory
    this->setCurrentIndex(this->model()->index(cs->currentViewIndex,1));


    emit dblClickOnItem(this->objectName(),cs->fullPath);

}

void CloudTableView::sheetContextMenu(const QPoint & pos)
{
    QMenu *menu = new QMenu;
    QModelIndex cell = this->indexAt(pos);
    // Make sure the right click occured on a cell!
    if(cell.isValid())
    {
        //QString str=cell.sibling(cell.row(),0).data().toString();
        //qDebug() << str;
        contextMenuItem=cell.sibling(cell.row(),0).data().toString();
        menu->addAction("Rename item", this, SLOT(sheetRenameItem()));
        menu->exec(this->mapToGlobal(pos));
    }
    delete menu;
}

void CloudTableView::sheetRenameItem()
{
    qDebug() << "Rename" << m_selectedtems;
    // qDebug() << fullPath << contextMenuItem;
    // contextMenuItem.clear();
}

void CloudTableView::cellChanged(QModelIndex x,QModelIndex)
{
    //this method prevents TableView from lost focus on "left arrow" key
    //        if (x.column()==0)
    //        {
    //    QModelIndex nIndex = this->CTModel->index(x.row(),2);
    //   qDebug() << "Cell changed. zero Column. Emitting Right Signal";
    moveCursor(QAbstractItemView::MoveRight,0);
    //   qDebug() << x.column();

    //   this->setCurrentIndex(nIndex);
    //       }
    //qDebug() << sender()    ;

}

QModelIndex CloudTableView::moveCursor(QAbstractItemView::CursorAction action, Qt::KeyboardModifiers modifiers)
{


    QModelIndex index = QTableView::moveCursor(action, modifiers);
    if (action == MoveLeft )
    {
        index = index.sibling(index.row(), currentIndex().column()); // keep the column intact
        moveCursor(QAbstractItemView::MoveRight,0); //qDebug() << "Left";
    }

    if (action == MoveRight) { index= index.sibling(index.row(), 1); //qDebug() << "Right";
    }

    if (action == MoveUp & currentIndex().row()==0) {
        index = index.sibling(index.row(), currentIndex().column());
        //    qDebug() << "UP" << currentIndex().row();
        return index;
    }

    if (action == MoveDown )
    {
        if (currentIndex().column()==0)
            this->setCurrentIndex(this->model()->index(cs->currentViewIndex,1));
        //          this->clearSelection();
        //          qDebug() << currentIndex().column();
        index = index.sibling(index.row(), currentIndex().column()); // keep the column intact
        moveCursor(QAbstractItemView::MoveRight,0); //qDebug() << "Left";

        return index;
    }

    if (action == MoveUp )
    {
        if (currentIndex().column()==0)
            this->setCurrentIndex(this->model()->index(cs->currentViewIndex,1));
        //          this->clearSelection();
        //          qDebug() << currentIndex().column();
        index = index.sibling(index.row(), currentIndex().column()); // keep the column intact
        moveCursor(QAbstractItemView::MoveRight,0); //qDebug() << "Left";

        return index;
    }


}



void CloudTableView::outOfFocusHappend()
{
}

void CloudTableView::initModel(int modelNum)
{
    readyToUpdate(false);

    if (cs) delete cs;

    if (modelNum==0)
        cs = new FileSystemSource();

    if (modelNum==1)
        cs = new DropBoxSource();

    this->clearSelection(); // or program crashes
    //qDebug() << CTModel;
    if (CTModel) delete CTModel;
    CTModel=new CloudTableModel(cs->getRoot());


    readyToUpdate(true);

    //setModel(CTModel);
    myProxyModel->setSourceModel(CTModel);
    setModel(myProxyModel);
    //myProxyModel->mapToSource()

    emit initDone(true);


    this->verticalHeader()->hide();
    this->setShowGrid(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setColumnHidden(3,true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setAlternatingRowColors(true);
    this->verticalHeader()->setDefaultSectionSize(25);
    this->setFocus();
    this->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);

    emit dblClickOnItem(this->objectName(),"/");

    if (this->model()->rowCount()>0)                                    // if non-zero count of rows then select first row
        this->setCurrentIndex(this->model()->index(0,1));

}

void CloudTableView::selectChanged(QModelIndexList lst)
{
    m_selectedtems.clear();
    foreach (QModelIndex idx, lst) {
        if (idx.column()!=0) lst.removeOne(idx);
    }

    foreach (QModelIndex idx, lst) {
        QString tmp =  cs->fullPath + myProxyModel->
                data(myProxyModel->index(idx.row(),0),Qt::DisplayRole).toString();
        if (!tmp.contains("/.."))
            m_selectedtems << cs->fullPath + CTModel->
                              data(ConvertIndexToRealModel(myProxyModel->index(idx.row(),0))
                                   ,Qt::DisplayRole).toString();
    }
}



bool CloudTableView::eventFilter(QObject* object, QEvent* event)
{


    if (event->type()==QEvent::KeyPress)                                        // key pressed
    {



        QKeyEvent* pKeyEvent=static_cast<QKeyEvent*>(event);                    // transforms QEvent into QKeyEvent
        switch(pKeyEvent->key())
        {
        case Qt::Key_Return:
        {
            this->dblClick(this->currentIndex());
            break;
        }
        case Qt::Key_Left:
        {
            return true;
            break;
        }
        }
        return QObject::eventFilter(object, event);
    } else
    {
        return QObject::eventFilter(object, event);
    }
}


CloudTableView::~CloudTableView()
{
    if (cs) delete cs;
    if (CTModel) delete CTModel;
}



void CloudTableView::readyToUpdate(bool b)
{
    if (b) {
        readyToUpdateFlag=true;
        emit readyToUpdateSingal(true);
    }
    else
    {
        readyToUpdateFlag=false;
        emit readyToUpdateSingal(false);
    }
}

QModelIndex CloudTableView::ConvertIndexToRealModel(const QModelIndex& q)
{
    //map inices from proxy to global model
    return this->myProxyModel->mapToSource(q);

    //    foreach (index, indexes) {
    //        row = proxy->mapToSource(index).row();
    //        qDebug() << "ToSource" << row <<  "Argument:" << index.row();
    //        i = table->index(row, 0, QModelIndex());
    //        QVariant varName = table->data(i, Qt::DisplayRole);
    //        name = varName.toString();

    //        i = table->index(row, 1, QModelIndex());
    //        QVariant varAddr = table->data(i, Qt::DisplayRole);
    //        address = varAddr.toString();
    //    }

}













void CloudTableView::updateSectionWidth(int logicalIndex, int, int newSize)
{

}

void CloudTableView::updateSectionHeight(int logicalIndex, int, int newSize)
{
}



void CloudTableView::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
}


void CloudTableView::scrollTo (const QModelIndex & index, ScrollHint hint){
    if(index.column()>0)
        QTableView::scrollTo(index, hint);
}



