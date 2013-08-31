#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QStringList>
#include <QtNetwork>

#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QDateTime>
#include <QtNetwork>

#include "commonsource.h"
#include "dropboxsource.h"
#include "filesystemsource.h"
#include "stringlistmodel.h"
#include "cloudtablemodel.h"
#include "cloudtableview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList lst;
    //StringListModel* str;
    CloudTableModel* CTModel;


private slots:


private:
    Ui::MainWindow *ui;

    QInputDialog* dialog;
};

#endif // MAINWINDOW_H
