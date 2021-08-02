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
    setWindowIcon(basedata->get_LOGO());
    this->basedata = basedata;
    this->log = log;
    loading_flash = NULL;
    model = 1;
    logintype = 0;

    show_user = false;
    remember_pass = false;

    //关闭按钮
    close_btn = new QPushButton(this);
    connect(close_btn,SIGNAL(clicked()),this,SLOT(close_window()));

    //二维码按钮
    QR_btn = new QPushButton(this);
    connect(QR_btn,SIGNAL(clicked()),this,SLOT(user_QRcode()));


    //头像
    face_image = new QLabel(this);

    //账号输入框
    account_edit = new QLineEdit(this);
    userAction = new QAction(account_edit);


    //密码输入框
    password_edit = new QLineEdit(this);
    passwordAction = new QAction(password_edit);
    connect(account_edit,SIGNAL(returnPressed()),password_edit,SLOT(setFocus()));
    connect(password_edit,SIGNAL(returnPressed()),this,SLOT(login_btn_clicked()));

    //登录按钮
    login_btn = new QPushButton(this);
    connect(login_btn,SIGNAL(clicked()),this,SLOT(login_btn_clicked()));

    //显示保存用户
    show_user_list_btn = new QPushButton(this);
    connect(show_user_list_btn,SIGNAL(clicked()),this,SLOT(show_user_btn_clicked()));

    //设置记住密码
    remember_btn = new QPushButton(this);
    connect(remember_btn,SIGNAL(clicked()),this,SLOT(remember_btn_clicked()));

    account_edit->installEventFilter(this);
    password_edit->installEventFilter(this);

    note = new QLabel(this);
    note->hide();

    //保存的用户
    box = new QListWidget(this);
    box->setFixedSize(200,80);
    userlist = new PersonList(box);
    userlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    connect(userlist,SIGNAL(user_selected(Person*)),this,SLOT(user_selected(Person *)));
    connect(userlist,SIGNAL(user_delete(Person*)),this,SLOT(user_delete(Person *)));
    userlist->setFixedSize(box->width(),box->height());
    userlist->move(0,0);
    QFile stylefile(":/qss/userliststyle.qss");
    stylefile.open(QFile::ReadOnly);
    userlist->setStyleSheet(stylefile.readAll());
    stylefile.close();
    box->setStyleSheet("QListWidget{"
                       "background: rgba(255,255,255,0.5);"
                       "border: none;"
                       "}");
    box->hide();
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(43, 43, 43));
    shadow_effect->setBlurRadius(8);
    box->setGraphicsEffect(shadow_effect);

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
    this->setFixedSize(250,300);
    close_btn->setFixedSize(20,20);
    QR_btn->setFixedSize(25,25);
    face_image->setFixedSize(80,80);
    account_edit->setFixedSize(180,30);
    password_edit->setFixedSize(180,30);
    login_btn->setFixedSize(130,30);
    show_user_list_btn->setFixedSize(20,20);
    remember_btn->setFixedSize(20,20);
    note->setFixedSize(this->width()-10,30);
}

void LoginWidget::init_Pos()
{
    close_btn->move(this->width()-30,10);
    QR_btn->move(10,10);
    face_image->move(this->width()/2-face_image->width()/2,60);
    account_edit->move(this->width()/2-account_edit->width()/2,face_image->y()+face_image->height()+25);
    password_edit->move(this->width()/2-password_edit->width()/2,account_edit->y()+account_edit->height()+10);
    login_btn->move(this->width()/2-login_btn->width()/2,password_edit->y()+password_edit->height()+15);
    show_user_list_btn->move(account_edit->x()+account_edit->width()-25,account_edit->y()+5);
    remember_btn->move(password_edit->x()+password_edit->width()-25,password_edit->y()+5);
    box->move(this->width()/2-box->width()/2,account_edit->y()+account_edit->height()+2);
    note->move(5,password_edit->y()+password_edit->height()+15);
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
    faceimage.load(":/image/faces/res/image/faces/boy_1.png");
    face_image->setPixmap(pix.fromImage(faceimage));
    face_image->setScaledContents(true);
    QRegExp regx("[0-9]+$");
    QValidator* validator = new QRegExpValidator(regx, account_edit);
    account_edit->setValidator(validator);
    account_edit->setMaxLength(12);
    userAction->setIcon(QIcon(":/image/icon/res/image/icon/user.png"));
    QAction *maskAction1;
    maskAction1 = new QAction(account_edit);
    maskAction1->setIcon(QIcon(":/image/icon/res/image/icon/mask.png"));
    account_edit->addAction(userAction,QLineEdit::LeadingPosition);
    account_edit->addAction(maskAction1,QLineEdit::TrailingPosition);
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
    QAction *maskAction2;
    maskAction2 = new QAction(password_edit);
    maskAction2->setIcon(QIcon(":/image/icon/res/image/icon/mask.png"));
    password_edit->addAction(passwordAction,QLineEdit::LeadingPosition);
    password_edit->addAction(maskAction2,QLineEdit::TrailingPosition);
    password_edit->setFont(QFont("Yu Gothic UI"));
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
                             "}"
                             "QPushButton:disabled{"
                             "background-color:rgb(17,174,243);"
                             "color: rgb(0,0,0);"
                             "}");
    show_user_list_btn->setStyleSheet("QPushButton{"
                                      "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                      "border-radius: 10px transparent;"
                                      "}");
    remember_btn->setStyleSheet("QPushButton{"
                                "border-image: url(:/image/btn/res/image/btn/remember.png);"
                                "border-radius: 10px transparent;"
                                "}");
    note->setFont(QFont("楷体"));
    note->setAlignment(Qt::AlignHCenter);
    note->setStyleSheet("QLabel{"
                        "font-size: 15px;"
                        "font-weight: 400;"
                        "color: rgb(0,0,0);"
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
                        userlist->addgroup("已保存");
                        userlist->addgroup("未保存");
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
                        /*if(!sql_query.exec("INSERT INTO users VALUES('10001','测试1','adbaud8!084/da',1)"))
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

void LoginWidget::start_loading()
{
    if(loading_flash == NULL)
    {
        account_edit->hide();
        password_edit->hide();
        show_user_list_btn->hide();
        remember_btn->hide();
        login_btn->hide();
        loading_flash=new Loading(this);
        loading_flash->setDotColor(Qt::gray);
        loading_flash->setFixedSize(65,65);
        loading_flash->setDotCount(10);
        loading_flash->setMaxDiameter(10);
        loading_flash->setMinDiameter(5);
        loading_flash->move(this->width()/2-loading_flash->width()/2,account_edit->y());
        loading_flash->start();
        loading_flash->show();
    }
}

void LoginWidget::stop_loading()
{
    delete loading_flash;
    loading_flash=NULL;
    account_edit->show();
    password_edit->show();
    show_user_list_btn->show();
    remember_btn->show();
    login_btn->show();
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
    if(show_user == true)
    {
        show_user = false;
        box->hide();
    }
    QEvent *ev = new QEvent(QEvent::FocusOut);
    eventFilter(account_edit,ev);
    eventFilter(password_edit,ev);
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
                                        "font-size: 20px;"
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
                                        "font-size: 20px;"
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
                                         "font-size: 15px;"
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
                                         "font-size: 15px;"
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
    basedata->set_user_info(user);
    show_user = false;
    show_user_list_btn->setStyleSheet("QPushButton{"
                                      "border-image: url(:/image/btn/res/image/btn/show_user.png);"
                                      "border-radius: 10px transparent;"
                                      "}");
    box->hide();
    account_edit->setText(user->get_account());
    if(user->get_passwordkey()!="")
    {
        remember_pass = true;
        password_edit->setText("--------");
        logintype = 1;
    }else
    {
        remember_pass = false;
        password_edit->setText("");
        logintype = 0;
    }
    faceimage.load(QString("./files/All_user/image/faces/%1.jpg").arg(user->get_account()));
    face_image->setPixmap(pix.fromImage(faceimage));
    QEvent *ev = new QEvent(QEvent::FocusIn);
    eventFilter(password_edit,ev);
    password_edit->setFocus();
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

void LoginWidget::login_btn_clicked()
{
    start_loading();
    note->setText("正在连接到服务器...");
    note->show();
    emit trylogin(logintype);
}

void LoginWidget::user_delete(Person *user)
{
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
            QString select_sql = "delete from users where account = "+user->get_account();
            if(!sql_query.exec(select_sql))
            {
                log->error(sql_query.lastError().text());
            }
            else
            {
                log->info("delete user->>"+user->get_account());
            }
        }
    }
    userlist->clear();
    userlist->clearitem();
    init_Userinfo();
}

void LoginWidget::user_QRcode()
{
    if(model == 1)
    {
        account_edit->hide();
        password_edit->hide();
        show_user_list_btn->hide();
        remember_btn->hide();
        login_btn->hide();
        this->setFixedSize(250,250);
        face_image->setFixedSize(150,150);
        face_image->move(this->width()/2-face_image->width()/2,this->height()/2-face_image->height()/2);
        QPixmap qrPixmap;
        int width = face_image->width();
        int height = face_image->height();
        MyTools::GernerateQRCode("http://www.baidu.com?id=dakdjkadbad8a7d9adsndlkadnalkdadaod900adska", qrPixmap, 10);
        qrPixmap = qrPixmap.scaled(QSize(width, height),
                                   Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        face_image->setPixmap(qrPixmap);
        model = 2;
    }else
    {
        account_edit->show();
        password_edit->show();
        show_user_list_btn->show();
        remember_btn->show();
        login_btn->show();
        this->setFixedSize(250,300);
        face_image->setFixedSize(80,80);
        face_image->move(this->width()/2-face_image->width()/2,60);
        face_image->setPixmap(pix.fromImage(faceimage));
        model = 1;
    }
}


