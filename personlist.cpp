#include "personlist.h"
#include <QtDebug>

PersonList::PersonList(QListWidget *parent) :
    QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭
}

void PersonList::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);
    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取
    if(event->button()==Qt::LeftButton && currentItem!=NULL && personItemMap.find(currentItem)!=personItemMap.end())//如果点击的左键并且是点击的是人
    {
        emit user_selected(personItemMap.find(currentItem).value());
    }
}

void PersonList::addgroup(QString groupname)
{
    QDir dir;
    if(dir.mkpath("./files/All_user/image/"))
    {
        QListWidgetItem *newItem=new QListWidgetItem(groupname.toUtf8());    //创建一个Item
        newItem->setSizeHint(QSize(this->width(),20));//设置宽度、高度
        newItem->setTextAlignment(Qt::AlignBottom);
        this->addItem(newItem);         //加到QListWidget中
        allMap.insert(newItem,newItem);//加到容器groupMap里，key和value都为组
        groupMap.insert(groupname,newItem);
        newItem->setFlags(Qt::ItemIsEnabled);
    }
}

void PersonList::addperson(QString groupname,Person *buddy)
{
    currentItem = groupMap.find(groupname).value();
    QList<QListWidgetItem*> temp = allMap.keys(currentItem);//当前组对应的项（包括组本身和好友）复制给temp
    //关键代码
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    this->insertItem(row(currentItem)+temp.count(),newItem); //将该newItem插入到后面
    newItem->setSizeHint(QSize(this->width(), 50));
    this->setItemWidget(newItem, buddy); //将word赋给该newItem
    allMap.insert(newItem,currentItem);   //加进容器，key为好友，value为组
    personsMap.insert(buddy->get_account(),buddy);
    personItemMap.insert(newItem,buddy);
    connect(buddy,SIGNAL(deleteuser_btn_clicked(QString)),this,SLOT(deleteuser_btn_clicked(QString)));
}

void PersonList::deleteuser_btn_clicked(QString account)
{
    if(personsMap.find(account) != personsMap.end())
    {
        emit user_delete(personsMap.find(account).value());
    }
}

void PersonList::clearitem()
{
    allMap.clear();
    groupMap.clear();
    personsMap.clear();
    personItemMap.clear();
}

bool PersonList::finduser(QString account)
{
    if(personsMap.find(account)!=personsMap.end())
    {
        emit user_selected(personsMap.find(account).value());
        return true;
    }
    return false;
}
