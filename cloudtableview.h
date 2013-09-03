#ifndef CloudTableView_H
#define CloudTableView_H
// before-dead

#include <QTableView>
#include "cloudtablemodel.h"
#include "commonsource.h"
#include "dropboxsource.h"
#include "filesystemsource.h"
#include "commonsource.h"
#include "mysortfilterproxymodel.h"
#include "c++/4.7/vector"


//! [Widget definition]
class CloudTableView : public QTableView {
     Q_OBJECT

public:
      CloudTableView(int modelNum);
      ~CloudTableView();

      bool eventFilter(QObject *, QEvent *);


      CloudTableModel* CTModel;
      CommonSource* cs;

      //this is flag is used whether source have finished connection with internet
      bool readyToUpdateFlag;

        QModelIndex moveCursor(CursorAction action, Qt::KeyboardModifiers modifiers);

              void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible);

              MySortFilterProxyModel* myProxyModel;





protected:
      virtual void resizeEvent(QResizeEvent *event);


private:


      //contains item of context menu
      QString contextMenuItem;

      int currentViewIndex;

      pathStructure pathStr;
      //contains list of path pieces
      QList<pathStructure> currentPath;

      //contains full string from currentPath
      QString fullPath;

      //list of selected indices
      QList<QString> m_selectedtems;

      void readyToUpdate(bool);

      QModelIndex ConvertIndexToRealModel(const QModelIndex&);



      //int PreviousPathIndex;

private slots:
      void updateSectionWidth(int logicalIndex,int, int newSize);
      void updateSectionHeight(int logicalIndex, int, int newSize);

      void dblClick(QModelIndex);

      void sheetContextMenu(const QPoint &);
      void sheetRenameItem();

      void cellChanged(QModelIndex,QModelIndex);

      void outOfFocusHappend(); //reimplement from qwidget




public slots:
      void selectChanged(QModelIndexList lst);
            void initModel(int);

 signals:
      void dblClickOnItem(const QString&,const QString&);
             void focusOutEvent(QFocusEvent *event);
             void readyToUpdateSingal(bool);
             void initDone(bool);


};
//! [Widget definition]
#endif
