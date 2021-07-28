#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(GlobalData *basedata,Logfiles *log,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    //窗口去边框
    setWindowFlag(Qt::FramelessWindowHint);
    //设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground);
    this->basedata = basedata;
    this->log = log;

    close_btn = new QPushButton(this);
    connect(close_btn,SIGNAL(clicked()),this,SLOT(close_window()));

    face_image = new QLabel(this);

    init();
}

LoginWidget::~LoginWidget()
{
    delete ui;
    delete close_btn;
    delete face_image;
}

void LoginWidget::init()
{
    close_btn->setText("X");

    init_Size();
    init_Pos();
    init_Style();
    init_Userinfo();
}

void LoginWidget::init_Size()
{
    this->setFixedSize(250,350);
    close_btn->setFixedSize(25,25);
}

void LoginWidget::init_Pos()
{
    close_btn->move(this->width()-30,5);
}

void LoginWidget::init_Style()
{
    close_btn->setStyleSheet("QPushButton{"
                             "background-color: rgba(255,255,255,0);"
                             "font-size:20px;"
                             "font-weight: 500;"
                             "color: rgb(255,255,255);"
                             "}"
                             "QPushButton:hover{"
                             "background-color: rgba(175,0,0,0.3);"
                             "font-size:20px;"
                             "}"
                             "QPushButton:pressed{"
                             "background-color: rgba(255,0,0,0.3);"
                             "font-size:20px;"
                             "}");
}

void LoginWidget::init_Userinfo()
{
    QDir dir;
    if(dir.mkpath("./Datas/All_user"))
    {
        if (QSqlDatabase::contains("all_user_connection"))
        {
            database = QSqlDatabase::database("all_user_connection");
        }
        else
        {
            database = QSqlDatabase::addDatabase("QSQLITE","all_user_connection");
            database.setDatabaseName("./Datas/All_user/Login_User_DataBase.db");
            database.setUserName("root");
            database.setPassword("AdU-Y4pVWC4ZeTb");
        }
        if (!database.open())
        {
            log->error("Failed to connect database.\n\t\t"+database.lastError().text());
        }
        else
        {
            log->info("Connected to database.");
            QSqlQuery sql_query(database);
            if(database.tables().contains("users"))
            {
                    basedata->set_User_Db_State(true);
                    QString select_sql = "select account, passwordkey, state from users";
                    if(!sql_query.exec(select_sql))
                    {
                        log->error(sql_query.lastError().text());
                    }
                    else
                    {
                        while(sql_query.next())
                        {
                            QString account = sql_query.value(0).toString();
                            QString passwordkey = sql_query.value(1).toString();
                            qDebug()<<account<<passwordkey;
                        }
                        if(!sql_query.exec("INSERT INTO users VALUES('10001','adbaud8!084/da',1)"))
                        {
                            qDebug() << sql_query.lastError();
                        }
                        else
                        {
                            qDebug() << "inserted Li!";
                        }
                    }
            }else
            {
                QString create_sql = "create table users (account varchar(11) primary key, passwordkey varchar(50),state int)";
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    basedata->set_User_Db_State(false);
                    log->error("Fail to create table.\n\t\t"+sql_query.lastError().text());
                }
                else
                {
                    basedata->set_User_Db_State(true);
                    log->info("Table created!");
                }
            }



        }



    }
}

void LoginWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(5, 5, this->width()-10, this->height()-10);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<5; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(5-i, 5-i, this->width()-(5-i)*2, this->height()-(5-i)*2);
        color.setAlpha(100 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos()-p);
    }
}

void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        p=event->globalPos()-frameGeometry().topLeft();
    }
}


void LoginWidget::close_window()
{
    this->close();
}

