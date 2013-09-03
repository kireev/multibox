#include "startwindow.h"
#include <QMenuBar>


startWindow::startWindow(QWidget *parent, KeyPressEater *keyPressEater) :
    QMainWindow(parent)
{
    currentActiveTab=false;

    connect(keyPressEater,SIGNAL(tabCatched(const QString&)),this,SLOT(tabIsPressed(const QString&)));


    SingleTable *sgt1 = new SingleTable();
    tables.append(sgt1);
    SingleTable *sgt2 = new SingleTable();
    tables.append(sgt2);

    QHBoxLayout *hLayout = new QHBoxLayout;
    int temp_cnt=0;
    foreach (SingleTable* sng, tables) {

        sng->Ctv->setObjectName("tab"+QString::number(temp_cnt));   //give object names
        sng->FileSystemCombo_->setObjectName("t"+QString::number(temp_cnt));
        temp_cnt++;
        hLayout->addLayout(sng->VerticalLayout);    //add to layout

        //    // on mouse of keyboard press
       connect(sng->Ctv,SIGNAL(pressed(const QModelIndex&)) ,this,SLOT(focusIsMade(const QModelIndex&)));

       //    // on mouse wheel focus is made too
       connect(sng->Ctv,SIGNAL(entered(const QModelIndex&)) ,this,SLOT(focusIsMade(const QModelIndex&)));

       //    // disable or enable tables while update
       connect(sng->Ctv,SIGNAL(readyToUpdateSingal(bool)),this,SLOT(changeTablesViewState(bool)));

       //    // disable or enable tables while update
       connect(sng,SIGNAL(stabilizeViewSignal()),this,SLOT(stabilizeView()));

       connect(sng->FileSystemCombo_,SIGNAL(currentIndexChanged(int)),this,SLOT(comboChanged(int)));
       //connect(sng->SelectionModel_,SIGNAL(currentChanged(QModelIndex,QModelIndex))
    }



    QWidget *window = new QWidget();
    window->setLayout(hLayout);
    setCentralWidget(window);

    //initialization
    tables.at(0)->Ctv->setFocus();
    tables.at(1)->Ctv->clearSelection();

    this->setupActions();
    this->setupMenus();
    this->setupToolBox();

    this->setMinimumSize(800,600);

}


void startWindow::setupMenus()
{

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(addAction);
}

void startWindow::setupToolBox()
{

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(addAction);
    editToolBar->addAction(exitAction);
}


void startWindow::setupActions()
{
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit program"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    deleteAction = new QAction(QIcon(":/img/apply.png"),tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    addAction = new QAction(QIcon(":/img/add.JPG"),tr("&Add"), this);
    addAction->setShortcut(tr("Delete"));
    addAction->setStatusTip(tr("Delete item from diagram"));
    connect(addAction, SIGNAL(triggered()), this, SLOT(addItem()));
}

void startWindow::deleteItem()
{
    qDebug() << "delete item";
}

void startWindow::addItem()
{
    qDebug() << "add item";
}



void startWindow::tabIsPressed(const QString& tab)
{

    stabilizeView();

    if (tab=="tab0") {
        MakeActive(true);
    }
    else {
        MakeActive(false);
    }
}

void startWindow::focusIsMade(const QModelIndex& idx)
{
    foreach (SingleTable* sng, tables) {
        if (!sng->Ctv->readyToUpdateFlag) sng->Ctv->setEnabled(false);
    }
    //Debug() << "Focus is made" << sender()->objectName();

    if (sender()->objectName()=="tab1") {
        MakeActive(true);
    }
    else {
        MakeActive(false);
    }

}

void startWindow::changeTablesViewState(bool b)
{
    foreach (SingleTable* sng, tables) {
        sng->Ctv->setEnabled(b);
        sng->FileSystemCombo_->setEnabled(b);

    }

}


void startWindow::MakeActive(bool b)
{
    currentActiveTab=b;
   // qDebug() << "cat" << currentActiveTab;
    foreach (SingleTable* sng, tables) {
        if (!sng->Ctv->readyToUpdateFlag) return;

    }

    // true - left, false - right
    if (b)
    {
        tables.at(1)->Ctv->setFocus();
        tables.at(1)->Ctv->setCurrentIndex(tables.at(1)->Ctv->model()->index(tables.at(1)->Ctv->currentIndex().row(),1));
        tables.at(0)->Ctv->clearSelection();

    }
    else
    {
        tables.at(0)->Ctv->setFocus();
        tables.at(0)->Ctv->setCurrentIndex(tables.at(0)->Ctv->model()->index(tables.at(0)->Ctv->currentIndex().row(),1));
        tables.at(1)->Ctv->clearSelection();
    }
}

void startWindow::stabilizeView()
{
    foreach (SingleTable* sng, tables) {

                int currentRow = sng->Ctv->currentIndex().row();
                int topLeft = sng->Ctv->indexAt(sng->Ctv->rect().topLeft()).row();
                int bottomLeft = sng->Ctv->indexAt(sng->Ctv->rect().bottomLeft()).row();
     //           qDebug() << sng << "sng" << "tL" << topLeft << "bL" << bottomLeft << "current" << currentRow ;
                if (currentRow >= bottomLeft)
                {
                    QModelIndex modelIndex =  sng->Ctv->currentIndex();
                    sng->Ctv->scrollTo(modelIndex);
                }

    }
}

void startWindow::comboChanged(int idx)
{
//    qDebug() << "iii" << idx;

//    foreach (SingleTable* sng, tables) {
//        sng->Ctv->clearSelection();
//                }

    //select first row in left table by default
    MakeActive(sender()->objectName()=="t1");
    //qDebug() << sender()->objectName();

}



