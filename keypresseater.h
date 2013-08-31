#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>

class KeyPressEater : public QObject
{
    Q_OBJECT

public:
    bool isLeftButtonPressed;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void tabCatched(const QString&);
    void rightButtonCatched(const QString&);

};

#endif // KEYPRESSEATER_H
