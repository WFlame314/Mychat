#include "basecontrol.h"

BaseControl::BaseControl(QWidget *parent)
    : QWidget(parent)
{
    basedata = new GlobalData();
    log = new Logfiles(basedata);
    log->init();
    ifsavemsg = false;
    filemodel = false;
    savedmsg = "";
    widgetmanager = new WidgetManage(basedata,log);
    login_socket = new Socket(this);
    connect(login_socket,&QTcpSocket::connected,this,&BaseControl::connected_to_server_login);
    connect(login_socket,&Socket::H_dataReceived,this,&BaseControl::datareceved_login);
    connect(login_socket,&Socket::H_fileReceived,this,&BaseControl::filereceved_login);
    connect(widgetmanager,SIGNAL(trylogin_signal(int,bool)),this,SLOT(trylogin_slot(int,bool)));
    connect(widgetmanager,&WidgetManage::login_finished,this,&BaseControl::login_finished);
    if(widgetmanager->open_Loginwindow())
    {
        widgetmanager->open_Mainwindow();
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
//    login_socket->connectToHost("99.15.216.71",3000);
    this->login_type = type;
    this->ifremember = ifremember;
}

void BaseControl::connected_to_server_login()
{
    cout<<"connected";
    QJsonObject data;
    widgetmanager->sendinfo_to_loginwindow(1,data);
    data.insert("account",basedata->get_user_info()->get_account());
    data.insert("uuid",basedata->get_uuid());
    data.insert("hostname",QHostInfo::localHostName());
    data.insert("password",basedata->get_user_info()->get_passwordkey());
    data.insert("logintype",basedata->get_Login_Type());
    data.insert("loginstate",basedata->get_user_info()->get_state());
    data.insert("ifremember",ifremember);
    QJsonObject body;
    body.insert("type","login");
    body.insert("data",data);
    QJsonDocument msg;
    msg.setObject(body);
    log->info("try login");
    login_socket->send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3));
}

void BaseControl::datareceved_login(QByteArray msg,int length)
{
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(msg,&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        log->error("解析json文件错误！"+parseJsonErr.errorString());
        return;
    }
    QJsonObject body = document.object();
    QJsonObject data = body["data"].toObject();
    if(body["type"].toString()=="login_return")
    {
        if(data["state"].toString() != "login_success" && data["state"].toString() != "key_login_success" )
        {
            login_socket->disconnectFromHost();
            widgetmanager->sendinfo_to_loginwindow(2,data);
        }else
        {
            if(data["state"].toString() == "key_login_success")
            {
                widgetmanager->sendinfo_to_loginwindow(3,data);
            }else
            {
                widgetmanager->sendinfo_to_loginwindow(4,data);
            }
        }

    }if(body["type"].toString()=="login_file_size")
    {
        int fsize = data["filesize"].toInt();
        login_socket->setfile_size(data["filesize"].toInt());
        QJsonObject data;
        data.insert("filesize",fsize);
        data.insert("account",basedata->get_user_info()->get_account());
        QJsonObject body;
        body.insert("type","login_file_size_recevied");
        body.insert("data",data);
        QJsonDocument msg;
        msg.setObject(body);
        login_socket->send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3));
    }

    cout<<msg<<length;

}


void BaseControl::filereceved_login(QByteArray buf,int)
{
    QDir dir;
    if(dir.mkpath("./files/"+basedata->get_user_info()->get_account()+"/images"))
    {
        tcpinfile.setFileName("./files/"+basedata->get_user_info()->get_account()+"/images/loginfiles.tcpout");
        if(tcpinfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            tcpinfile.write(buf);
        }
        tcpinfile.close();
        cout<<"文件接收完成！";
        widgetmanager->sendinfo_to_loginwindow(5,QJsonObject());
    }
}

void BaseControl::login_finished()
{
    if(widgetmanager->open_Mainwindow())
    {
        if(basedata->get_Log_State())
        {
            log->info("MAINWINDOW OPENED!");
        }
        else
        {
            QMessageBox::warning(this,"日志文件错误","日志文件打开失败！");
        }
    }else
    {
        log->error("MAINWINDOW OPEN FAILED!");
    }
}
