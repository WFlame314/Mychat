#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QListWidget>
#include <QDir>
#include "person.h"

class PersonList : public QListWidget
{
    Q_OBJECT
public:
    PersonList(QListWidget *parent = 0);
    void addgroup(QString);
    void addperson(QString groupname,Person *buddy);

private:
    QMap<QListWidgetItem*,QListWidgetItem*> allMap;
    QMap<QString,Person*> personsMap;
    QMap<QString,QListWidgetItem*> groupMap;
    QListWidgetItem *currentItem;//当前的项

};

#endif // PERSONLIST_H
