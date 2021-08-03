#include "basecontrol.h"

BaseControl::BaseControl(QWidget *parent)
    : QWidget(parent)
{
    basedata = new GlobalData();
    log = new Logfiles(basedata);
    log->init();
    ifsavemsg = false;
    savedmsg = "";
    widgetmanager = new WidgetManage(basedata,log);
    login_socket = new TcpServer();
    connect(login_socket,&QTcpSocket::connected,this,&BaseControl::connected_to_server_login);
    connect(login_socket,&TcpServer::datareceived,this,&BaseControl::datareceved_login);
    connect(widgetmanager,SIGNAL(trylogin_signal(int,bool)),this,SLOT(trylogin_slot(int,bool)));
    if(widgetmanager->open_Loginwindow())
    {
        if(basedata->get_Log_State())
        {
            log->info("LOGWINDOW OPENED!");
        }
        else
        {
            QMessageBox::warning(this,"日志文件错误","日志文件打开失败！");
        }
    }else
    {
        log->error("LOGWINDOW OPEN FAILED!");
    }
}

BaseControl::~BaseControl()
{
    log->info("ALL CLOSED!");
    delete basedata;
    delete log;
    delete widgetmanager;
}

void BaseControl::trylogin_slot(int type,bool ifremember)
{
    cout<<basedata->get_user_info()->get_account()<<basedata->get_user_info()->get_passwordkey()<<basedata->get_user_info()->get_state()<<type<<ifremember;
    login_socket->connectToHost("8.135.40.232",3000);
    //login_socket->connectToHost("99.15.216.125",3000);
    this->login_type = type;
    this->ifremember = ifremember;
}

void BaseControl::connected_to_server_login()
{
    cout<<"connected";
    widgetmanager->sendinfo_to_loginwindow(1);
    QJsonObject data;
    data.insert("account",basedata->get_user_info()->get_account());
    data.insert("password",basedata->get_user_info()->get_passwordkey());
    data.insert("loginstate",basedata->get_user_info()->get_state());
    data.insert("ifremember",ifremember);
    QJsonObject body;
    body.insert("type","login");
    body.insert("data",data);
    QJsonDocument msg;
    msg.setObject(body);
    login_socket->write(char(0)+msg.toJson(QJsonDocument::Compact)+char(1));
}

void BaseControl::datareceved_login(QString msg,int length)
{
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        log->error("解析json文件错误！"+parseJsonErr.errorString());
        cout<<tr("解析json文件错误！");
        return;
    }
    QJsonObject body = document.object();
    QJsonObject data = body["data"].toObject();
    if(body["type"].toString()=="login_return")
    {
        if(data["state"].toString() != "login_success")
        {
            login_socket->disconnectFromHost();
        }
        widgetmanager->sendinfo_to_loginwindow(2,data["state"].toString());
    }
    cout<<msg<<length;
}
