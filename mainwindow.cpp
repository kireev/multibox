#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//        ui->setupUi(this);
//        this->setMinimumSize(800,600);


//         CommonSource* dbs = new DropBoxSource();

//    QList<QStringList> list1=dbs->listFiles("/not-sync");

////        foreach (QStringList lst, list1)
////        {
////            listOfFiles << lst;
////        }

//        CTModel=new CloudTableModel(list1,false);


//        //CloudTableView* CTViewLeft = new CloudTableView(CTModel);

////        CTViewLeft->setWindowTitle(QObject::tr("Frozen Column Example"));
////        CTViewLeft->setParent(ui->widgetLeft);
//// //       CTViewLeft->setMinimumSize(250,250);
//////        CTViewLeft->resize(380,468);
////        //CTViewLeft->setRowHeight(10);
////        CTViewLeft->show();

////        //CloudTableView* CTViewRight = new CloudTableView(CTModel);

////        CTViewRight->setWindowTitle(QObject::tr("Frozen Column Example"));
////        CTViewRight->setParent(ui->widgetRight);
//// //       CTViewRight->setMinimumSize(250,250);
//// //       CTViewRight->resize(380,310);
////        CTViewRight->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

