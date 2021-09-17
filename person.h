#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QLabel>
#include <QLabel>
#include <QPushButton>
#include "mybutton.h"
#include "personinfo.h"
#include <QDateTime>

class Person : public QWidget
{
    Q_OBJECT
public:
    explicit Person(QWidget *parent = nullptr);
    Person(QString account,QString name,QString passwordkey,int state,QWidget *parent = nullptr);
    Person(QString account,QString passwordkey,int state,QWidget *parent = nullptr);
    Person(personinfo person,QString account,int type,QWidget *parent = nullptr);

    void init_userlist_buddy();
    void init_chatting_buddy();
    void init_friend_buduy();
    QString get_account();
    QString get_name();
    QString get_passwordkey();
    QString get_sign();
    int get_state();

    void set_name(QString name);
    void set_password(QString password);
    void set_account(QString account);
    void set_sign(QString sign);

    personinfo info;



private:
    QLabel *face_image;
    QLabel *name_label;
    QLabel *account_label;
    QLabel *time_label;
    QLabel *sign_words_label;
    QLabel *textmask;
    MyButton *noreadcount_btn;
    MyButton *delete_btn;

    QString passwordkey;
    QString account;
    QString name;
    QString sign;
    int state;

    QPixmap maskpix;

signals:
    void deleteuser_btn_clicked(QString);

public slots:
    void delete_btn_clicked();


};

#endif // PERSON_H
