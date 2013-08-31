
#include "keypresseater.h"
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QtTest/QtTest>
#include <QtTest/qtest.h>


bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QKeyEvent::KeyPress:
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        switch(keyEvent->key())
        {
        case Qt::Key_Tab:
        {
            //             qDebug() << "GOT IT! TAB IS PRESSED" << qPrintable(obj->objectName());
            if (!isLeftButtonPressed) emit tabCatched(qPrintable(obj->objectName()));
            return true;
            break;
        }
        }


        return QObject::eventFilter(obj, event);
    }

    case QMouseEvent::MouseButtonPress:
    case QMouseEvent::MouseButtonRelease:
    {

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        isLeftButtonPressed= mouseEvent->buttons().testFlag(Qt::LeftButton);
        if (mouseEvent->button()==2)
        {
            return true;
            break;
        }

                 return QObject::eventFilter(obj, event);
    }

    default:
        return QObject::eventFilter(obj, event);
    }

}
