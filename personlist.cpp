#include "personlist.h"

PersonList::PersonList(QListWidget *parent) :
    QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭
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
    personsMap.insert(groupname,buddy);
}
