#include "mainwidget.h"
#include <QThread>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
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
        QString s= "select * from user where account=0;";
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

void MainWidget::updataServer(QString msg,int length,int descriptor)
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
        QString s= "select password from user where account=" + data["account"].toString() + ";";
        qDebug()<<s;
        flashsql=false;
        if(query.exec(s))
        {
            query.next();
            if(query.value(0).toString() != data["password"].toString())
            {
                QJsonObject backbody,backdata;
                backdata.insert("state","wrong_password");
                backbody.insert("type","login_return");
                backbody.insert("data",backdata);
                QJsonDocument msg;
                msg.setObject(backbody);
                send(char(0)+msg.toJson(QJsonDocument::Compact)+char(1),descriptor);
                ContentListWidget->addItem(data["account"].toString()+":密码错误");
            }
            else if(query.value(0).toString() == data["password"].toString())
            {
                QJsonObject backbody,backdata;
                backdata.insert("state","login_success");
                backbody.insert("type","login_return");
                backbody.insert("data",backdata);
                QJsonDocument msg;
                msg.setObject(backbody);
                send(char(0)+msg.toJson(QJsonDocument::Compact)+char(1),descriptor);
                ContentListWidget->addItem(data["account"].toString()+":登录成功");
            }
            else
            {
                QJsonObject backbody,backdata;
                backdata.insert("state","wrong_account");
                backbody.insert("type","login_return");
                backbody.insert("data",backdata);
                QJsonDocument msg;
                msg.setObject(backbody);
                send(char(0)+msg.toJson(QJsonDocument::Compact)+char(1),descriptor);
                ContentListWidget->addItem(data["account"].toString()+":用户名不存在");
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
            ContentListWidget->addItem(QString(backmsg)+QString("-----%1").arg(descriptor));
            qDebug()<<backmsg;
            return;
        }
    }
}

