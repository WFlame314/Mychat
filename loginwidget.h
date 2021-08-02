#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPainter>
#include <QtMath>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include "globaldata.h"
#include "logfiles.h"
#include "personlist.h"
#include "Loading.h"
#include "mytools.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(GlobalData *basedata,Logfiles *log,QWidget *parent = nullptr);
    ~LoginWidget();
    void init();
    void init_Size();
    void init_Pos();
    void init_Style();
    void init_Userinfo();
    void start_loading();
    void stop_loading();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::LoginWidget *ui;
    GlobalData *basedata; //公共数据
    QPoint p;//记录鼠标在窗口中的位置
    Logfiles *log;
    QSqlDatabase database;
    QPixmap pix;
    QAction *userAction;
    QAction *passwordAction;
    bool show_user;
    bool remember_pass;
    int model;
    QImage faceimage;
    int logintype;

    /*
     * 窗口中组件
     */
    QPushButton *close_btn;
    QPushButton *QR_btn;
    QLabel *face_image;
    PersonList *userlist;
    QListWidget *box;
    QLineEdit *account_edit;
    QLineEdit *password_edit;
    QPushButton *login_btn;
    QPushButton *show_user_list_btn;
    QPushButton *remember_btn;
    Loading *loading_flash;
    QLabel *note;
    //QRcode *qrcode;


public slots:
    void close_window();
    void user_selected(Person *user);
    void show_user_btn_clicked();
    void remember_btn_clicked();
    void login_btn_clicked();
    void user_delete(Person *user);
    void user_QRcode();


signals:
    void trylogin(int type);
};

#endif // LOGINWIDGET_H
