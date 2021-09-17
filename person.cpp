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

Person::Person(personinfo info,QString account,int type,QWidget *parent) : QWidget(parent)
{
    face_image = new QLabel(this);
    name_label = new QLabel(this);
    sign_words_label = new  QLabel(this);
    textmask = new QLabel(this);
    textmask->show();
    maskpix.fromImage(QImage(":/image/icon/res/image/icon/mask2.png"));
    this->info = info;
    this->account = account;
    if(type==1)
    {
        noreadcount_btn = new MyButton(this);
        time_label = new QLabel(this);
        init_chatting_buddy();
    }else if(type == 0)
    {
        init_friend_buduy();
    }

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
}

void Person::init_chatting_buddy()
{
    face_image->setFixedSize(40,40);
    name_label->setFixedSize(140,20);
    sign_words_label->setFixedSize(110,20);
    noreadcount_btn->setFixedSize(20,20);
    time_label->setFixedSize(40,20);
    textmask->setFixedSize(30,this->height());

    face_image->move(10,5);
    name_label->move(10+face_image->width()+10,5);
    sign_words_label->move(10+face_image->width()+10,5+name_label->height());
    noreadcount_btn->move(10+face_image->width()+10+name_label->width()-35,sign_words_label->y());
    time_label->move(noreadcount_btn->x()-5,name_label->y());
    textmask->move(60,0);
    textmask->setText("11111111111111");

    name_label->setText(info.remarkname==""?info.name:info.remarkname);
    sign_words_label->setText(info.lastwords);
    noreadcount_btn->setText(QString("%1").arg(info.noreadcount));
    QDateTime dt;
    dt=QDateTime::fromString(info.datetime,Qt::ISODate);
    if(dt.date()==QDateTime::currentDateTime().date())
    {
        time_label->setText(dt.time().toString("h:mm"));
    }else if(dt.date().dayOfYear()==QDateTime::currentDateTime().date().dayOfYear()-1)
    {
        time_label->setText("昨天");
    }else
    {
        time_label->setText(dt.date().toString("M-d"));
    }


    face_image->setStyleSheet(QString("QLabel{"
                                      "border-image: url(./files/%1/images/faces/%2.jpg);"
                                      "border-radius: 20px;"
                                      "border: none;"
                                      "}").arg(account).arg(info.account));
    name_label->setStyleSheet("QLabel{"
                              "border-radius: 5px transparent;"
                              "background: rgba(0,0,0,0);"
                              "color: rgb(0,0,0);"
                              "font-size: 15px;"
                              "font-weight: 600;"
                              "}");
    sign_words_label->setStyleSheet("QLabel{"
                                    "border-radius: 5px transparent;"
                                    "background: rgba(0,0,0,0);"
                                    "color: rgb(100,100,100);"
                                    "font-size: 11px;"
                                    "font-weight: 200;"
                                    "}");
    time_label->setStyleSheet("QLabel{"
                              "color: rgb(50,50,50);"
                              "font-size: 12px"
                              "}");
    //noreadcount_btn->setNormalIcon(QIcon(":/image/icon/res/image/icon/notice.png"));
    noreadcount_btn->setStyleSheet("QPushButton{"
                                   "background: rgb(216,30,6);"
                                   "border-radius: 10px transparent;"
                                   "border: 1px;"
                                   "color: rgb(255,255,255);"
                                   "}");

}

void Person::init_friend_buduy()
{

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
