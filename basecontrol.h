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
#include "tcpserver.h"


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
    TcpServer *login_socket;
    int login_type;
    bool ifremember;
    bool ifsavemsg;
    QString savedmsg;


public slots:
    void trylogin_slot(int type,bool ifremember);
    void datareceved_login(QString,int);
    void connected_to_server_login();

};
#endif // BASECONTROL_H
