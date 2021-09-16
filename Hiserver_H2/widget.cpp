#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    srand(time(0));
    setWindowTitle("-服务器-");
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel("端口号：");
    PortLineEdit = new QLineEdit(this);
    CreateBtn = new  QPushButton("-开启-");
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);
    port=3000;
    PortLineEdit->setText(QString::number(port));
    PortLineEdit->setDisabled(true);
    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *)
{
    if(flashsql)
    {
        QSqlQuery query;
        QString s= "select * from users where account=0;";
        if(query.exec(s))
        {
            //ContentListWidget->addItem(QDateTime::currentDateTime().toString(Qt::ISODate)+":数据库活动刷新！");
        }else
        {
            ContentListWidget->addItem(QDateTime::currentDateTime().toString(Qt::ISODate)+":数据库活动丢失！\n尝试再次连接...");
            mysql->trytoconnect("QODBC","localhost","Mychatserver","root","+2314Wyx");
        }
    }
    flashsql=true;
}

void Widget::slotCreateServer()
{
    H_server = new Server(this,port);
    connect(H_server,&Server::get_msg,this,&Widget::dataReceived);
    connect(H_server,&Server::sendok,this,&Widget::getok);
    mysql = new SQL(this);
    connect(mysql,SIGNAL(connecttomysql(int)),this,SLOT(connecttomysql(int)));
    mysql->trytoconnect("QODBC","localhost","Mychatserver","root","+2314Wyx");
    //mysql->trytoconnect("QODBC","localhost","QTMYSQL","root","+2314Wyx");
    CreateBtn->setEnabled(false);
    flashsql=true;
    this->startTimer(60000);
}

void Widget::connecttomysql(int type)
{
    if(type==1)
    {
        ContentListWidget->addItem(QString("数据库连接成功！"));
    }
    else
    {
        ContentListWidget->addItem(QString("数据库连接失败！"));
    }
}

void Widget::dataReceived(QByteArray msg_data,int descriptor)
{
    QString msg = msg_data;
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(),&parseJsonErr);

    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }
    qDebug()<<msg;
    QJsonObject body = document.object();
    QJsonObject data = body["data"].toObject();
    if(body["type"] == "login")
    {
        QSqlQuery query;
        QString s;
        if(data["logintype"].toInt() == 0)
        {
            QByteArray strings=data["account"].toString().toUtf8()+'H'+data["password"].toString().toUtf8();
            QByteArray Encryptedpasswords = QCryptographicHash::hash(strings, QCryptographicHash::Md5).toHex();
            s= "select password,nikcname,signature from users where account=" + data["account"].toString() + ";";
            qDebug()<<s;
            flashsql=false;
            if(query.exec(s))
            {
                query.next();
                if(query.value(0).toString() == "")
                {
                    QJsonObject backbody,backdata;
                    backdata.insert("state","wrong_account");
                    backbody.insert("type","login_return");
                    backbody.insert("data",backdata);
                    QJsonDocument msg;
                    msg.setObject(backbody);
                    send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
                    ContentListWidget->addItem(data["account"].toString()+":用户错误");
                }
                else if(query.value(0).toString() == QString(Encryptedpasswords))
                {
                    QString name = query.value(1).toString().toUtf8();
                    QString sign = query.value(2).toString().toUtf8();
                    s = "select uuid from "+ data["account"].toString()+"_devices where uuid='" + data["uuid"].toString()+"';";
                    if(query.exec(s))
                    {
                        if(query.value(0).toString() == "")
                        {
                            s = "INSERT INTO "+data["account"].toString()+"_devices (uuid, hostname, password_key) VALUES ('"
                                +data["uuid"].toString()+"','"
                                +data["hostname"].toString()+"','');";
                            query.exec(s);
                        }
                    }
                    QJsonObject backbody,backdata;
                    backdata.insert("state","login_success");
                    backdata.insert("account",data["account"].toString());
                    backdata.insert("name",name);
                    backdata.insert("sign",sign);
                    if(data["ifremember"].toBool())
                    {
                        QString key = getrandkey();
                        QByteArray strings=data["uuid"].toString().toUtf8()+'H'+key.toUtf8();
                        QByteArray newEncryptedpasswords = QCryptographicHash::hash(strings, QCryptographicHash::Md5).toHex();
                        s= "update " + data["account"].toString() + "_devices set password_key='" + QString(newEncryptedpasswords) +"' where uuid= '"+ data["uuid"].toString() +"';";
                        ContentListWidget->addItem(s);
                        if(query.exec(s))
                        {
                            backdata.insert("passwordkey",key);
                        }
                    }
                    backbody.insert("type","login_return");
                    backbody.insert("data",backdata);
                    QJsonDocument msg;
                    msg.setObject(backbody);
                    QString backmsg(msg.toJson(QJsonDocument::Compact));
                    ContentListWidget->addItem(backmsg);
                    send(char(2)+backmsg.toUtf8()+char(3),descriptor);
                    ContentListWidget->addItem(data["account"].toString()+":登录成功");
                    sendlogin_files_head(data["account"].toString(),descriptor);
                }
                else
                {
                    QJsonObject backbody,backdata;
                    backdata.insert("state","wrong_password");
                    backbody.insert("type","login_return");
                    backbody.insert("data",backdata);
                    QJsonDocument msg;
                    msg.setObject(backbody);
                    send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
                    ContentListWidget->addItem(data["account"].toString()+":密码错误");
                }

            }
        }else if(data["logintype"].toInt() == 1)
        {
            QByteArray strings=data["uuid"].toString().toUtf8()+'H'+data["password"].toString().toUtf8();
            QByteArray Encryptedpasswords = QCryptographicHash::hash(strings, QCryptographicHash::Md5).toHex();
            s= "select password_key from " + data["account"].toString() + "_devices where uuid='" + data["uuid"].toString() + "';";
            qDebug()<<s;
            flashsql=false;
            ContentListWidget->addItem(s);
            if(query.exec(s))
            {
                query.next();
                if(query.value(0).toString() == QString(Encryptedpasswords))
                {
                    QString key = getrandkey();
                    QByteArray strings=data["uuid"].toString().toUtf8()+'H'+key.toUtf8();
                    QByteArray newEncryptedpasswords = QCryptographicHash::hash(strings, QCryptographicHash::Md5).toHex();
                    s = "update " + data["account"].toString() + "_devices set password_key='" + QString(newEncryptedpasswords) +"' where uuid= '"+ data["uuid"].toString() +"';";
                    ContentListWidget->addItem(s);
                    if(query.exec(s))
                    {
                        QJsonObject backbody,backdata;
                        s = "select nikcname,signature from users where account=" + data["account"].toString() + ";";
                        if(query.exec(s))
                        {
                            query.next();
                            backdata.insert("name",query.value(0).toString());
                            backdata.insert("sign",query.value(1).toString());
                        }
                        backdata.insert("state","key_login_success");
                        backdata.insert("passwordkey",key);
                        backbody.insert("type","login_return");
                        backbody.insert("data",backdata);
                        QJsonDocument msg;
                        msg.setObject(backbody);
                        send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
                        ContentListWidget->addItem(data["account"].toString()+":登录成功");
                        sendlogin_files_head(data["account"].toString(),descriptor);
                    }
                }else
                {
                    QJsonObject backbody,backdata;
                    backdata.insert("state","passwordkey_timeout");
                    backbody.insert("type","login_return");
                    backbody.insert("data",backdata);
                    QJsonDocument msg;
                    msg.setObject(backbody);
                    send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
                    ContentListWidget->addItem(data["account"].toString()+":密钥超时");
                }
            }
        }

    }else if(body["type"] == "login_file_size_recevied")
    {
        ContentListWidget->addItem("login_file_size_recevied");
        ContentListWidget->addItem(QString("%1  %2").arg(filesize).arg(data["filesize"].toInt()));
        if(filesize == data["filesize"].toInt())
        {
            ContentListWidget->addItem("startsend");
            sendlogin_files(data["account"].toString(),descriptor);
        }
    }else if(body["type"] == "getfriends")
    {
        QJsonObject backbody,backdata;
        ContentListWidget->addItem("getfriends");
        QSqlQuery query;
        QString s;
        s = "select groupid,groupname,grouptype from " + data["account"].toString() +"_groups";
        if(query.exec(s))
        {
            QJsonArray groups;
            while(query.next())
            {
                QJsonObject group;
                group.insert("groupid",query.value(0).toInt());
                group.insert("groupname",query.value(1).toString());
                group.insert("grouptype",query.value(2).toInt());
                groups.push_back(group);
            }
            backdata.insert("groups",groups);
        }
        s = "select friendaccount,friendremark,friendname,friendgroupid,lastwords,noreadcount,chatflag,lastchattime,signature "
            "from " + data["account"].toString() +"_friends,users "
            "where friendaccount=users.account "
            "ORDER BY `lastchattime` DESC";
        if(query.exec(s))
        {
            QJsonArray friends;
            while(query.next())
            {
                QJsonObject outfriend;
                outfriend.insert("friendaccount",query.value(0).toString());
                outfriend.insert("friendremark",query.value(1).toString());
                outfriend.insert("friendname",query.value(2).toString());
                outfriend.insert("friendgroupid",query.value(3).toInt());
                outfriend.insert("lastwords",query.value(4).toString());
                outfriend.insert("noreadcount",query.value(5).toInt());
                outfriend.insert("chatflag",query.value(6).toInt());
                outfriend.insert("lastchattime",query.value(7).toDateTime().toString());
                outfriend.insert("friendsignature",query.value(8).toString());
                friends.push_back(outfriend);
            }
            backdata.insert("friends",friends);
        }
        backbody.insert("type","allfriendsinfo");
        backbody.insert("data",backdata);
        QJsonDocument msg;
        msg.setObject(backbody);
        QString backmsg(msg.toJson(QJsonDocument::Compact));
        send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
        ContentListWidget->addItem("好友信息发送成功！");
    }

    ContentListWidget->scrollToBottom();
}

int Widget::send(QByteArray backmsg,int descriptor)
{
    for(int i=0;i<H_server->tcpclientSocketlist.count();i++)
    {
        QTcpSocket *item = H_server->tcpclientSocketlist.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            int len;
            len = item->write(backmsg);
            item->waitForBytesWritten();
            ContentListWidget->addItem(QString(backmsg).remove(0,1).remove(backmsg.length()-1,1)+QString("-----%1").arg(descriptor));
            return len;
        }
    }
    return 0;
}


QString Widget::getrandkey()
{
    QString key="";
    int t;
    for(int i = 0; i < 32 ; i++)
    {
        t = (rand()%93) + 33;
        if(t == 34 || t == 39 || t == 40 || t == 41 || t == 44 || t == 47 ||t ==58 || t == 59)
        {
            i--;
            continue;
        }else
        {
            key += char(t);
        }
    }
    return key;
}


void Widget::creatbatfiles(QString account)
{
    QDir dir;
    if(dir.mkpath("./bats"))
    {
        QFile batfile("./bats/"+account+".bat");
        if(batfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream out(&batfile);
            out<<"cd /d C:\\Hi_files\\users\\" + account +"\\images\\"<<"\n";
            out<<"tar cvf C:\\tcptemp\\" + account + ".tcpout faces";
            batfile.close();
        }
    }
}

void Widget::sendlogin_files_head(QString account, int descriptor)
{
    creatbatfiles(account);
    QProcess p;
    p.start(".//bats//"+account+".bat");
    p.waitForFinished();
    ContentListWidget->addItem("ran");
    QFile file("C:/tcptemp/"+account+".tcpout");
    filesize = file.size();
    QJsonObject data;
    data.insert("filesize",file.size());
    QJsonObject body;
    body.insert("type","login_file_size");
    body.insert("data",data);
    QJsonDocument msg;
    msg.setObject(body);
    send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
}


void Widget::sendlogin_files(QString account, int descriptor)
{
    ContentListWidget->addItem("开始发送");
    H_server->sendfiles("C:/tcptemp/"+account+".tcpout",descriptor);
}

void Widget::getok(QString msg)
{
    ContentListWidget->addItem(msg);
}
