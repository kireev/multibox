#ifndef PAINTDELEGATE_H
#define PAINTDELEGATE_H

#include <QItemDelegate>

// class for overriding dotted rectangle in QTableView
class PaintDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    virtual void drawFocus ( QPainter * /*painter*/, const QStyleOptionViewItem & /*option*/, const QRect & /*rect*/ ) const;
};


#endif // PAINTDELEGATE_H
