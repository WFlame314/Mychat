#include "person.h"
#include <QtDebug>

Person::Person(QWidget *parent) : QWidget(parent)
{

}


Person::Person(QString account,QString name,QString passwordkey,int state,QWidget *parent) : QWidget(parent)
{
    this->account = account;
    this->name = name;
    this->state = state;
    this->passwordkey = passwordkey;
    face_image = new QLabel(this);
    name_label = new QLabel(this);
    account_label = new QLabel(this);
    delete_btn = new QPushButton(this);
    connect(delete_btn,SIGNAL(clicked()),this,SLOT(delete_btn_clicked()));
    init_userlist_buddy();
}

void Person::delete_btn_clicked()
{
    qDebug() <<"delete";
}

void Person::init_userlist_buddy()
{
    face_image->setFixedSize(40,40);
    name_label->setFixedSize(140,20);
    account_label->setFixedSize(140,20);
    delete_btn->setFixedSize(20,20);
    face_image->move(10,5);
    name_label->move(10+face_image->width()+10,5);
    account_label->move(10+face_image->width()+10,5+name_label->height());
    delete_btn->move(10+face_image->width()+10+name_label->width()-30,15);
    name_label->setText(name);
    account_label->setText(account);
    face_image->setStyleSheet(QString("QLabel{"
                                      "border-image: url(./files/All_user/image/faces/%1.png);"
                                      "border-radius: 20px;"
                                      "border: none;"
                                      "}").arg(account));
    name_label->setStyleSheet("QLabel{"
                              "border-radius: 5px transparent;"
                              "background: rgba(0,0,0,0);"
                              "color: rgb(50,50,50);"
                              "}");
    account_label->setStyleSheet("QLabel{"
                                 "border-radius: 5px transparent;"
                                 "background: rgba(0,0,0,0);"
                                 "color: rgb(50,50,50);"
                                 "}");
}


QString Person::get_name()
{
    return name;
}

QString Person::get_account()
{
    return account;
}

QString Person::get_passwordkey()
{
    return passwordkey;
}

int Person::get_state()
{
    return state;
}
