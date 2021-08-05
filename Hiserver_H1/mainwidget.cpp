#include "mainwidget.h"
#include <QThread>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    srand(time(0));
    setWindowTitle("-服务器-");
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel("端口号：");
    PortLineEdit = new QLineEdit;
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

MainWidget::~MainWidget()
{

}

void MainWidget::timerEvent(QTimerEvent *)
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

void MainWidget::slotCreateServer()
{
    server = new class::server(this,port);
    connect(server,SIGNAL(updataServer(QString,int,int)),this,SLOT(updataServer(QString,int,int)));
    mysql = new SQL(this);
    connect(mysql,SIGNAL(connecttomysql(int)),this,SLOT(connecttomysql(int)));
    mysql->trytoconnect("QODBC","localhost","Mychatserver","root","+2314Wyx");
    //mysql->trytoconnect("QODBC","localhost","QTMYSQL","root","+2314Wyx");
    CreateBtn->setEnabled(false);
    flashsql=true;
    this->startTimer(60000);
}

void MainWidget::connecttomysql(int type)
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

void MainWidget::updataServer(QString msg,int ,int descriptor)
{
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
            s= "select password,nikcname from users where account=" + data["account"].toString() + ";";
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
                        s = "select nikcname from users where account=" + data["account"].toString() + ";";
                        if(query.exec(s))
                        {
                            query.next();
                            backdata.insert("name",query.value(0).toString());
                        }
                        backdata.insert("state","key_login_success");
                        backdata.insert("passwordkey",key);
                        backbody.insert("type","login_return");
                        backbody.insert("data",backdata);
                        QJsonDocument msg;
                        msg.setObject(backbody);
                        send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);
                        ContentListWidget->addItem(data["account"].toString()+":登录成功");
                        sendlogin_files(data["account"].toString(),descriptor);
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

    }

    ContentListWidget->scrollToBottom();
}

void MainWidget::send(QByteArray backmsg,int descriptor)
{
    for(int i=0;i<server->tcpclientSocketlist.count();i++)
    {
        QTcpSocket *item = server->tcpclientSocketlist.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            item->write(backmsg);
            item->waitForBytesWritten();
            ContentListWidget->addItem(QString(backmsg).remove(0,1).remove(backmsg.length()-1,1)+QString("-----%1").arg(descriptor));
            return;
        }
    }
}

QString MainWidget::getrandkey()
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


void MainWidget::sendlogin_files(QString account,int descriptor)
{
    creatbatfiles(account);
    QProcess p;
    p.start(".//bats//"+account+".bat");
    p.waitForFinished();
    ContentListWidget->addItem("ran");
    QFile tcpoutfile("C:/tcptemp/"+account+".tcpout");
    if(tcpoutfile.open(QIODevice::ReadOnly))
    {
        qint64 filesize=0;
        qint64 sendsize=0;
        QString filename="";

        filename = tcpoutfile.fileName();
        filesize = tcpoutfile.size();

        QJsonObject backbody,backdata;
        backdata.insert("account",account);
        backdata.insert("filename",filename);
        backdata.insert("filesize",filesize);
        backbody.insert("type","login_files");
        backbody.insert("data",backdata);
        QJsonDocument msg;
        msg.setObject(backbody);
        send(char(2)+msg.toJson(QJsonDocument::Compact)+char(3),descriptor);

        qint64 len = 0;
        do{
            // 每次发送 2kb 大小的数据，如果剩余的数据不足 2kb，就发送剩余数据的大小
            char buf[2*1024] = {0};

            len = 0;
            len = tcpoutfile.read( buf, sizeof(buf) ); //读数据
            send(buf,descriptor);    //发数据

            sendsize +=len; //已发送的文件数据大小
        }while(len > 0);

        if(sendsize == filesize)
        {
            ContentListWidget->addItem("文件发送完成");
            //关闭文件
            file.close();
        }
    }
}

void MainWidget::creatbatfiles(QString account)
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


