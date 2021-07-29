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

    show_user = false;
    remember_pass = false;

    //关闭按钮
    close_btn = new QPushButton(this);
    connect(close_btn,SIGNAL(clicked()),this,SLOT(close_window()));

    //二维码按钮
    QR_btn = new QPushButton(this);
    connect(QR_btn,SIGNAL(clicked()),this,SLOT());


    //头像
    face_image = new QLabel(this);

    //账号输入框
    account_edit = new QLineEdit(this);
    userAction = new QAction(account_edit);

    //密码输入框
    password_edit = new QLineEdit(this);
    passwordAction = new QAction(password_edit);

    //登录按钮
    login_btn = new QPushButton(this);

    //显示保存用户
    show_user_list_btn = new QPushButton(this);
    connect(show_user_list_btn,SIGNAL(clicked()),this,SLOT(show_user_btn_clicked()));

    //设置记住密码
    remember_btn = new QPushButton(this);
    connect(remember_btn,SIGNAL(clicked()),this,SLOT(remember_btn_clicked()));

    account_edit->installEventFilter(this);
    password_edit->installEventFilter(this);

    //保存的用户
    box = new QListWidget(this);
    box->setFixedSize(200,100);
    userlist = new PersonList(box);
    connect(userlist,SIGNAL(user_selected(Person*)),this,SLOT(user_selected(Person *)));
    userlist->setFixedSize(box->width(),box->height());
    userlist->move(0,0);
    QFile stylefile(":/qss/userliststyle.qss");
    stylefile.open(QFile::ReadOnly);
    userlist->setStyleSheet(stylefile.readAll());
    stylefile.close();
    userlist->addgroup("已保存");
    userlist->addgroup("未保存");
    box->setStyleSheet("QListWidget{"
                       "background: rgba(255,255,255,0.5);"
                       "}");
    box->hide();

    init();
}

LoginWidget::~LoginWidget()
{
    delete ui;
    delete close_btn;
    delete face_image;
    delete account_edit;
    delete password_edit;
    delete userAction;
    delete passwordAction;
    delete login_btn;
    delete show_user_list_btn;
    delete remember_btn;
}

void LoginWidget::init()
{

    init_Size();
    init_Pos();
    init_Style();
    init_Userinfo();
}

void LoginWidget::init_Size()
{
    this->setFixedSize(250,310);
    close_btn->setFixedSize(20,20);
    QR_btn->setFixedSize(25,25);
    face_image->setFixedSize(100,100);
    account_edit->setFixedSize(180,30);
    password_edit->setFixedSize(180,30);
    login_btn->setFixedSize(130,30);
    show_user_list_btn->setFixedSize(20,20);
    remember_btn->setFixedSize(20,20);
}

void LoginWidget::init_Pos()
{
    close_btn->move(this->width()-30,10);
    QR_btn->move(10,10);
    face_image->move(this->width()/2-face_image->width()/2,60);
    account_edit->move(this->width()/2-account_edit->width()/2,face_image->y()+face_image->height()+20);
    password_edit->move(this->width()/2-password_edit->width()/2,account_edit->y()+account_edit->height()+10);
    login_btn->move(this->width()/2-login_btn->width()/2,password_edit->y()+password_edit->height()+10);
    show_user_list_btn->move(account_edit->x()+account_edit->width()-30,account_edit->y()+5);
    remember_btn->move(password_edit->x()+password_edit->width()-30,password_edit->y()+5);
    box->move(this->width()/2-box->width()/2,account_edit->y()+account_edit->height()+2);
}

void LoginWidget::init_Style()
{
    close_btn->setStyleSheet("QPushButton{"
                             "border-image: url(:/image/btn/res/image/btn/login_close.png);"
                             "border-radius: 10px transparent;"
                             "}"
                             "QPushButton:hover{"
                             "border-image: url(:/image/btn/res/image/btn/login_close_hover.png);"
                             "}"
                             "QPushButton:pressed{"
                             "border-image: url(:/image/btn/res/image/btn/login_close_pressed.png);"
                             "}");
    QR_btn->setStyleSheet("QPushButton{"
                          "border-image: url(:/image/btn/res/image/btn/QR.png);"
                          "}"
                          "QPushButton:hover{"
                          "border-image: url(:/image/btn/res/image/btn/QR_hover.png);"
                          "}");
    QImage image(":/image/faces/res/image/faces/boy_1.png");
    face_image->setPixmap(pix.fromImage(image));
    face_image->setScaledContents(true);
    QRegExp regx("[0-9]+$");
    QValidator* validator = new QRegExpValidator(regx, account_edit);
    account_edit->setValidator(validator);
    account_edit->setMaxLength(12);
    userAction->setIcon(QIcon(":/image/icon/res/image/icon/user.png"));
    account_edit->addAction(userAction,QLineEdit::LeadingPosition);
    account_edit->setFont(QFont("Yu Gothic UI"));
    account_edit->setStyleSheet("QLineEdit{"
                                "background-color: rgba(255,255,255,0.5);"
                                "border-top:0px  solid ;"
                                "border-bottom:1px  solid #707070;"
                                "border-left:0px  solid;"
                                "border-right: 0px  solid;"
                                "font-size: 20px;"
                                "font-weight: 600;"
                                "}");
    password_edit->setEchoMode(QLineEdit::Password);
    passwordAction->setIcon(QIcon(":/image/icon/res/image/icon/password.png"));
    password_edit->addAction(passwordAction,QLineEdit::LeadingPosition);
    password_edit->setStyleSheet("QLineEdit{"
                                 "background-color: rgba(255,255,255,0.5);"
                                 "border-top:0px  solid ;"
                                 "border-bottom:1px  solid #707070;"
                                 "border-left:0px  solid;"
                                 "border-right: 0px  solid;"
                                 "font-size: 15px;"
                                 "font-weight: 600;"
                                 "}");
    login_btn->setText("登  录");
    login_btn->setFont(QFont("楷体"));
    login_btn->setStyleSheet("QPushButton{"
                             "border-radius: 10px;"
                             "background-color:rgb(17,174,243);"
                             "font-size: 20px;"
                             "font-weight: 400;"
                             "color: rgb(255,255,255);"
                             "}"
                             "QPushButton:hover{"
                             "background-color:rgb(34,189,243);"
                             "}"
                             "QPushButton:pressed{"
                             "background-color:rgb(10,160,243);"
                             "}");
    show_user_list_btn->setStyleSheet("QPushButton{"
                                      "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                      "border-radius: 10px transparent;"
                                      "}");
    remember_btn->setStyleSheet("QPushButton{"
                                "border-image: url(:/image/btn/res/image/btn/remember.png);"
                                "border-radius: 10px transparent;"
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
                    QString select_sql = "select account, name, passwordkey, state from users";
                    if(!sql_query.exec(select_sql))
                    {
                        log->error(sql_query.lastError().text());
                    }
                    else
                    {
                        while(sql_query.next())
                        {
                            QString account = sql_query.value(0).toString();
                            QString name = sql_query.value(1).toString();
                            QString passwordkey = sql_query.value(2).toString();
                            int state = sql_query.value(3).toInt();
                            qDebug()<<account<<passwordkey<<state;
                            Person *user = new Person(account,name,passwordkey,state);
                            if(passwordkey!="")
                            {
                                userlist->addperson("已保存",user);
                            }else
                            {
                                userlist->addperson("未保存",user);
                            }

                        }
                        /*if(!sql_query.exec("INSERT INTO users VALUES('10001','adbaud8!084/da',1)"))
                        {
                            qDebug() << sql_query.lastError();
                        }
                        else
                        {
                            qDebug() << "inserted Li!";
                        }*/
                    }
            }else
            {
                QString create_sql = "create table users (account varchar(11) primary key,name varchar(11), passwordkey varchar(50),state int)";
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

bool LoginWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == account_edit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            userAction->setIcon(QIcon(":/image/icon/res/image/icon/user_select.png"));
            account_edit->setStyleSheet("QLineEdit{"
                                        "background-color: rgba(255,255,255,0.5);"
                                        "border-top:0px  solid ;"
                                        "border-bottom:1px  solid #7dc5eb;"
                                        "border-left:0px  solid;"
                                        "border-right: 0px  solid;"
                                        "font-size: 16px;"
                                        "font-weight: 600;"
                                        "}");
            if(show_user == false)
            {
                show_user_list_btn->setStyleSheet("QPushButton{"
                                                  "border-image: url(:/image/btn/res/image/btn/show_user_select.png);"
                                                  "border-radius: 10px transparent;"
                                                  "}");
            }else
            {
                show_user_list_btn->setStyleSheet("QPushButton{"
                                                  "border-image: url(:/image/btn/res/image/btn/show_user_select_pressed.png);"
                                                  "border-radius: 10px transparent;"
                                                  "}");
            }
        }
        if(event->type() == QEvent::FocusOut)
        {
            userAction->setIcon(QIcon(":/image/icon/res/image/icon/user.png"));
            account_edit->setStyleSheet("QLineEdit{"
                                        "background-color: rgba(255,255,255,0.5);"
                                        "border-top:0px  solid ;"
                                        "border-bottom:1px  solid #707070;"
                                        "border-left:0px  solid;"
                                        "border-right: 0px  solid;"
                                        "font-size: 16px;"
                                        "font-weight: 600;"
                                        "}");
            if(show_user == false)
            {
                show_user_list_btn->setStyleSheet("QPushButton{"
                                                  "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                                  "border-radius: 10px transparent;"
                                                  "}");
            }else
            {
                show_user_list_btn->setStyleSheet("QPushButton{"
                                                  "border-image: url(:/image/btn/res/image/btn/show_user_pressed.png);"
                                                  "border-radius: 10px transparent;"
                                                  "}");
            }
        }
    }
    if(object == password_edit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            passwordAction->setIcon(QIcon(":/image/icon/res/image/icon/password_select.png"));
            password_edit->setStyleSheet("QLineEdit{"
                                         "background-color: rgba(255,255,255,0.5);"
                                         "border-top:0px  solid ;"
                                         "border-bottom:1px  solid #7dc5eb;"
                                         "border-left:0px  solid;"
                                         "border-right: 0px  solid;"
                                         "font-size: 16px;"
                                         "font-weight: 600;"
                                         "}");

            if(remember_pass == false)
            {
                remember_btn->setStyleSheet("QPushButton{"
                                            "border-image: url(:/image/btn/res/image/btn/remember_select.png);"
                                            "border-radius: 10px transparent;"
                                            "}");
            }else
            {
                remember_btn->setStyleSheet("QPushButton{"
                                                "border-image: url(:/image/btn/res/image/btn/remember_select_choose.png);"
                                                "border-radius: 10px transparent;"
                                                "}");
            }
        }
        if(event->type() == QEvent::FocusOut)
        {
            passwordAction->setIcon(QIcon(":/image/icon/res/image/icon/password.png"));
            password_edit->setStyleSheet("QLineEdit{"
                                         "background-color: rgba(255,255,255,0.5);"
                                         "border-top:0px  solid ;"
                                         "border-bottom:1px  solid #707070;"
                                         "border-left:0px  solid;"
                                         "border-right: 0px  solid;"
                                         "font-size: 16px;"
                                         "font-weight: 600;"
                                         "}");
            if(remember_pass == false)
            {
                remember_btn->setStyleSheet("QPushButton{"
                                            "border-image: url(:/image/btn/res/image/btn/remember.png);"
                                            "border-radius: 10px transparent;"
                                            "}");
            }else
            {
                remember_btn->setStyleSheet("QPushButton{"
                                                "border-image: url(:/image/btn/res/image/btn/remember_choose.png);"
                                                "border-radius: 10px transparent;"
                                                "}");
            }
        }
    }
    return QWidget::eventFilter(object, event);
}

void LoginWidget::close_window()
{
    this->close();
}

void LoginWidget::user_selected(Person *user)
{
    show_user = false;
    show_user_list_btn->setStyleSheet("QPushButton{"
                                      "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                      "border-radius: 10px transparent;"
                                      "}");
    box->hide();
    cout<< user->get_account();
}

void LoginWidget::show_user_btn_clicked()
{
    if(show_user == false)
    {
        show_user = true;
        show_user_list_btn->setStyleSheet("QPushButton{"
                                          "border-image: url(:/image/btn/res/image/btn/show_user_select_pressed.png);"
                                          "border-radius: 10px transparent;"
                                          "}");
        box->show();
    }else
    {
        show_user = false;
        show_user_list_btn->setStyleSheet("QPushButton{"
                                          "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                          "border-radius: 10px transparent;"
                                          "}");
        box->hide();
    }
}

void LoginWidget::remember_btn_clicked()
{
    if(remember_pass == false)
    {
        remember_pass = true;
        remember_btn->setStyleSheet("QPushButton{"
                                    "border-image: url(:/image/btn/res/image/btn/remember_choose.png);"
                                    "border-radius: 10px transparent;"
                                    "}");
    }else
    {
        remember_pass = false;
        remember_btn->setStyleSheet("QPushButton{"
                                    "border-image: url(:/image/btn/res/image/btn/remember.png);"
                                    "border-radius: 10px transparent;"
                                    "}");

    }
}
