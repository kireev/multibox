#ifndef STARTWINDOW_H
#define STARTWINDOW_H


#include "commonsource.h"
#include "dropboxsource.h"
#include "filesystemsource.h"
#include "stringlistmodel.h"
#include "cloudtablemodel.h"
#include "cloudtableview.h"
#include "singletable.h"
#include "keypresseater.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QToolBar>
#include <QLineEdit>

class startWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit startWindow(QWidget *parent = 0, KeyPressEater *KeyPressEater=0);


private:
    void setupActions();
    void setupMenus();
    void setupToolBox();

    QMenu* fileMenu;
    QMenu* itemMenu;
    QMenu* aboutMenu;

    QAction* exitAction;
    QAction* addAction;
    QAction* deleteAction;

    QToolBar* editToolBar;
    CloudTableModel* CTModel;

    QList<SingleTable*> tables;
    void MakeActive(bool);

    bool currentActiveTab; //0 -left, 1 - right



private slots:

    void deleteItem();
    void addItem();

    void tabIsPressed(const QString&);
    void focusIsMade(const QModelIndex&);

    // enable or disable windows while update
    void changeTablesViewState(bool);

    // if cursor is out of view area then scroll to cursor
    void stabilizeView ();

    void comboChanged(int);


};

#endif // STARTWINDOW_H
