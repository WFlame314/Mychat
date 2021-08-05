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
    login_socket = new TcpServer();
    connect(login_socket,&QTcpSocket::connected,this,&BaseControl::connected_to_server_login);
    connect(login_socket,&TcpServer::datareceived,this,&BaseControl::datareceved_login);
    connect(login_socket,&TcpServer::filereceived,this,&BaseControl::filereceved_login);
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
    log->info(QString("try login /n/t---->"+msg.toJson(QJsonDocument::Compact)).toUtf8());
    login_socket->write(char(2)+msg.toJson(QJsonDocument::Compact)+char(3));
}

void BaseControl::datareceved_login(QString msg,int length)
{
    if(filemodel == false)
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

        }else if(body["type"].toString()=="login_files")
        {

            filemodel = true;
            filesize = data["filesize"].toInt();
            filename = data["filename"].toString();
            QString account = data["account"].toString();
            recevedsize = 0;
            cout<<"收到文件头"<<filesize<<" "<<filename;
            QDir dir;
            if(dir.mkpath("./files/"+account+"/images/"))
            {
                tcpinfile.setFileName("./files/"+account+"/images/"+account+".tcpout");
                if(tcpinfile.open(QIODevice::WriteOnly))
                {
                    log->info("file opened!");
                    login_socket->setfilemode(true);
                }
            }

        }
        cout<<msg<<length;
    }else
    {

    }

}


void BaseControl::filereceved_login(QByteArray buf)
{
    qint64 len = tcpinfile.write(buf);
    recevedsize += len;
    if(recevedsize == filesize)//如果接收数据长度和发送数据长度相等做接收后处理
    {
        cout<<"文件接收完成！";
        tcpinfile.close();
        login_socket->setfilemode(false);
    }
}
