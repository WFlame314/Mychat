#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QListWidget>
#include <QDir>
#include <QMouseEvent>
#include "person.h"

class PersonList : public QListWidget
{
    Q_OBJECT
public:
    PersonList(QListWidget *parent = 0);
    void addgroup(QString);
    void addperson(QString groupname,Person *buddy);
    void addchatting(Person *buddy);
    void clearitem();
    bool finduser(QString account);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QMap<QListWidgetItem*,QListWidgetItem*> allMap;
    QMap<QListWidgetItem*,Person*> personItemMap;
    QMap<QString,Person*> personsMap;
    QMap<QString,QListWidgetItem*> groupMap;
    QListWidgetItem *currentItem;//当前的项

signals:
    void user_selected(Person *user);
    void user_delete(Person *user);

public slots:
    void deleteuser_btn_clicked(QString);

};

#endif // PERSONLIST_H
