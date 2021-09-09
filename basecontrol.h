#ifndef BASECONTROL_H
#define BASECONTROL_H

#include <QWidget>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHostInfo>
#include "globaldata.h"
#include "widgetmanage.h"
#include "logfiles.h"
#include "socket.h"


class BaseControl : public QWidget
{
    Q_OBJECT

public:
    BaseControl(QWidget *parent = nullptr);
    ~BaseControl();



private:

    GlobalData *basedata;
    WidgetManage *widgetmanager;
    Logfiles *log;
    Socket *login_socket;
    int login_type;
    bool ifremember;
    bool ifsavemsg;
    bool filemodel;
    QString savedmsg;

    QFile tcpinfile;


public slots:
    void trylogin_slot(int type,bool ifremember);
    void datareceved_login(QByteArray,int);
    void filereceved_login(QByteArray,int);
    void connected_to_server_login();
    void login_finished();
    void getfriends();

};
#endif // BASECONTROL_H
