#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include <QLabel>
#include <QLabel>
#include <QPushButton>

class Person : public QWidget
{
    Q_OBJECT
public:
    explicit Person(QWidget *parent = nullptr);
    Person(QString account,QString name,QString passwordkey,int state,QWidget *parent = nullptr);


    void init_userlist_buddy();
    QString get_account();
    QString get_name();
    QString get_passwordkey();
    int get_state();



private:
    QLabel *face_image;
    QLabel *name_label;
    QLabel *account_label;
    QPushButton *delete_btn;
    QString passwordkey;
    QString account;
    QString name;
    int state;

signals:

public slots:
    void delete_btn_clicked();


};

#endif // PERSON_H
