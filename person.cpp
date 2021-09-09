#include "person.h"
#include <QtDebug>

Person::Person(QWidget *parent) : QWidget(parent)
{
    this->account ="";
    this->passwordkey="";
    this->name="";
    this->state = 0;
    this->sign="";
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
    delete_btn = new MyButton(this);
    connect(delete_btn,SIGNAL(clicked()),this,SLOT(delete_btn_clicked()));
    init_userlist_buddy();
}

Person::Person(QString account,QString passwordkey,int state,QWidget *parent) : QWidget(parent)
{
    this->account = account;
    this->state = state;
    this->passwordkey = passwordkey;
    face_image = new QLabel(this);
    name_label = new QLabel(this);
    account_label = new QLabel(this);
    delete_btn = new MyButton(this);
    init_userlist_buddy();
}

void Person::delete_btn_clicked()
{
    emit deleteuser_btn_clicked(this->account);
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
                                      "border-image: url(./files/All_user/image/faces/%1.jpg);"
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
    delete_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/delete.png"));
    delete_btn->setHoverIcon(QIcon(":/image/btn/res/image/btn/delete_hover.png"));
    delete_btn->setPressedIcon(QIcon(":/image/btn/res/image/btn/delete_pressed.png"));
    delete_btn->setStyleSheet("QPushButton{"
                              "border-radius: 10px transparent;"
                              "}");
//    delete_btn->setStyleSheet("QPushButton{"
//                              "border-image: url(:/image/btn/res/image/btn/delete.png);"
//                              "border-radius: 10px transparent;"
//                              "}"
//                              "QPushButton:hover{"
//                              "border-image: url(:/image/btn/res/image/btn/delete_hover.png);"
//                              "}"
//                              "QPushButton:pressed{"
//                              "border-image: url(:/image/btn/res/image/btn/delete_pressed.png);"
//                              "}");
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

QString Person::get_sign()
{
    return sign;
}

int Person::get_state()
{
    return state;
}

void Person::set_name(QString name)
{
    this->name = name;
}

void Person::set_password(QString password)
{
    passwordkey = password;
}

void Person::set_account(QString account)
{
    this->account = account;
}

void Person::set_sign(QString sign)
{
    this->sign = sign;
}
