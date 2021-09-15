#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(GlobalData *basedata,Logfiles *log,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //窗口去边框
    setWindowFlag(Qt::FramelessWindowHint);
    //设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(basedata->get_LOGO());
    setWindowTitle("Hi");
    this->basedata = basedata;
    this->log = log;
    setFixedSize(800,500);
    init();
//    if(!bg.load(":/image/windows/res/image/windows/def_background.jpeg"))
//    {
//        log->error("background load failed!");
//    }

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    //LOGO
    LOGO.load(":/image/icon/res/image/icon/hi.png");
    LOGO_label = new QLabel(this);

    //关闭按钮
    close_btn = new MyButton(this);
    close_btn->setName("关闭");
    connect(close_btn,&MyButton::clicked,this,[=](){emit readytoclose();});

    //最大化按钮
    maxsize_btn = new MyButton(this);
    maxsize_btn->setName("最大化");

    //最小化按钮
    minisize_btn = new MyButton(this);
    minisize_btn->setName("最小化");

    //折叠按钮
    hide_show_btn = new MyButton(this);
    hide_show_btn->setName("分体模式");

    //头像按钮
    face_btn = new MyButton(this);
    face_btn->setCursor(Qt::PointingHandCursor);

    //昵称标签
    name_label = new QLabel(this);

    //签名按钮
    sign_btn = new QPushButton(this);
    connect(sign_btn,&QPushButton::clicked,this,[=](){sign_edit->show();sign_edit->selectAll();});

    //签名编辑框
    sign_edit = new QLineEdit(this);

    //应用区域
    appbox = new QListWidget(this);
    appbox->show();

    chating_btn = new MyButton();
    connect(chating_btn,&MyButton::clicked,this,&MainWidget::chatting_select);
    friends_btn = new MyButton();
    connect(friends_btn,&MyButton::clicked,this,&MainWidget::friends_select);
    groups_btn = new MyButton();
    connect(groups_btn,&MyButton::clicked,this,&MainWidget::groups_select);
    search_btn = new MyButton();
    connect(search_btn,&MyButton::clicked,this,&MainWidget::search_select);
    apps_btn = new MyButton();
    connect(apps_btn,&MyButton::clicked,this,&MainWidget::apps_select);
    setting_btn = new MyButton();
    connect(setting_btn,&MyButton::clicked,this,&MainWidget::setting_select);


    init_Size();
    init_Pos();
    init_Style();
}


void MainWidget::init_Size()
{
    //LOGO
    LOGO_label->setFixedSize(25,25);

    //关闭按钮
    close_btn->setFixedSize(25,25);

    //最大化按钮
    maxsize_btn->setFixedSize(25,25);

    //最小化按钮
    minisize_btn->setFixedSize(25,25);

    //折叠按钮
    hide_show_btn->setFixedSize(25,25);

    //头像
    face_btn->setFixedSize(50,50);

    //昵称标签
    name_label->setFixedSize(100,25);

    //签名按钮
    sign_btn->setFixedSize(130,20);

    //签名编辑框
    sign_edit->setFixedSize(sign_btn->width(),sign_btn->height());

    //应用区域
    appbox->setFixedSize(40,this->height()-126);

    chating_btn->setFixedSize(appbox->width(),appbox->width());
    friends_btn->setFixedSize(appbox->width(),appbox->width());
    groups_btn->setFixedSize(appbox->width(),appbox->width());
    search_btn->setFixedSize(appbox->width(),appbox->width());
    apps_btn->setFixedSize(appbox->width(),appbox->width());
    setting_btn->setFixedSize(appbox->width(),appbox->width());

}


void MainWidget::init_Pos()
{
    //LOGO
    LOGO_label->move(10,10);

    //关闭按钮
    close_btn->move(this->width()-10-close_btn->width(),10);

    //最大化按钮
    maxsize_btn->move(close_btn->x()-maxsize_btn->width()-2,10);

    //最小化按钮
    minisize_btn->move(maxsize_btn->x()-minisize_btn->width()-2,10);

    //折叠按钮
    hide_show_btn->move(235-hide_show_btn->width()-2,10);

    //头像按钮
    face_btn->move(20,50);

    //昵称标签
    name_label->move(face_btn->x()+face_btn->width()+10,face_btn->y()+2);

    //签名按钮
    sign_btn->move(name_label->x(),name_label->y()+28);

    //签名编辑框
    sign_edit->move(sign_btn->x(),sign_btn->y());

    //应用区域
    appbox->move(6,face_btn->y()+face_btn->height()+20);

    QListWidgetItem *chatting_Item = new QListWidgetItem();
    appbox->addItem(chatting_Item);
    chatting_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(chatting_Item,chating_btn);
    QListWidgetItem *friends_Item = new QListWidgetItem();
    appbox->addItem(friends_Item);
    friends_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(friends_Item,friends_btn);
    QListWidgetItem *groups_Item = new QListWidgetItem();
    appbox->addItem(groups_Item);
    groups_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(groups_Item,groups_btn);
    QListWidgetItem *search_Item = new QListWidgetItem();
    appbox->addItem(search_Item);
    search_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(search_Item,search_btn);
    QListWidgetItem *apps_Item = new QListWidgetItem();
    appbox->addItem(apps_Item);
    apps_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(apps_Item,apps_btn);

    QListWidgetItem *setting_Item = new QListWidgetItem();
    appbox->addItem(setting_Item);
    setting_Item->setSizeHint(QSize(chating_btn->width(),chating_btn->width()));
    appbox->setItemWidget(setting_Item,setting_btn);


}


void MainWidget::init_Style()
{
    //LOGO
    LOGO_label->setPixmap(pix.fromImage(LOGO));
    LOGO_label->setScaledContents(true);

    //关闭按钮
    close_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/close.png"));
    close_btn->setHoverIcon(QIcon(":/image/btn/res/image/btn/close_hover.png"));
    close_btn->setPressedIcon(QIcon(":/image/btn/res/image/btn/close_pressed.png"));
    close_btn->setStyleSheet("QPushButton{"
                             "border-radius: 5px transparent;"
                             "}");

    //最大化按钮
    maxsize_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/maxsize.png"));
    maxsize_btn->setHoverIcon(QIcon(":/image/btn/res/image/btn/maxsize_hover.png"));
    maxsize_btn->setPressedIcon(QIcon(":/image/btn/res/image/btn/maxsize_pressed.png"));
    maxsize_btn->setStyleSheet("QPushButton{"
                               "border-radius: 5px transparent;"
                               "}");

    //最小化按钮
    minisize_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/minisize.png"));
    minisize_btn->setHoverIcon(QIcon(":/image/btn/res/image/btn/minisize_hover.png"));
    minisize_btn->setPressedIcon(QIcon(":/image/btn/res/image/btn/minisize_pressed.png"));
    minisize_btn->setStyleSheet("QPushButton{"
                                "border-radius: 5px transparent;"
                                "}");

    //折叠按钮
    hide_show_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/hide.png"));
    hide_show_btn->setHoverIcon(QIcon(":/image/btn/res/image/btn/hide_hover.png"));
    hide_show_btn->setPressedIcon(QIcon(":/image/btn/res/image/btn/hide_pressed.png"));
    hide_show_btn->setStyleSheet("QPushButton{"
                                 "border-radius: 5px transparent;"
                                 "}");
    face_btn->setNormalIcon(QIcon("./files/All_user/image/faces/" + basedata->get_user_info()->get_account() + ".jpg"));
    //face_btn->setNormalIcon(QIcon(QString("./files/All_user/image/faces/10001.jpg")));

    //昵称标签
    name_label->setText(basedata->get_user_info()->get_name());
    name_label->setStyleSheet("QLabel{"
                              "font-size: 20px;"
                              "font-weight: 600;"
                              "}");

    //签名按钮
    sign_btn->setText(basedata->get_user_info()->get_sign());
    sign_btn->setStyleSheet("QPushButton{"
                            "background-color:rgba(0,0,0,0);"
                            "font-size: 15px;"
                            "font-weight: 400;"
                            "text-align: left;"
                            "color: rgb(255,255,255);"
                            "}"
                            "QPushButton:hover{"
                            "border: 1px solid;"
                            "border-color: rgba(50,50,50,0.7);"
                            "}");

    //签名编辑框
    sign_edit->hide();
    sign_edit->setText(basedata->get_user_info()->get_sign());
    sign_edit->setStyleSheet("QLineEdit{"
                             "border: none;"
                             "font-size: 15px;"
                             "font-weight: 400;"
                             "}");

    //应用区域
    QFile stylefile(":/qss/appboxstyle.qss");
    stylefile.open(QFile::ReadOnly);
    appbox->setStyleSheet(stylefile.readAll());
    stylefile.close();
    appbox->setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    appbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭
    /*appbox->setStyleSheet("QListWidget{"
                          "background: rgba(255,255,255,0.2);"
                          "border: none;"
                          "}");*/
    chatting_select();
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(5, 5, this->width()-10, this->height()-10);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(QColor(200,200,200)));
//    painter.drawPixmap(5,5,width()-10,height()-10,bg);
    painter.setPen(QColor(50,50,50,180));
    painter.drawLine(240,6,240,this->height()-6);

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

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos()-p);
    }
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton)
    {
        p=event->globalPos()-frameGeometry().topLeft();
        if(sign_edit->isVisible())
        {
            if(sign_edit->text()=="")
            {
                sign_btn->setText("点击编辑签名");
            }else
            {
                sign_btn->setText(sign_edit->text());
            }
            sign_edit->hide();
        }
    }
}

void MainWidget::initAppBox()
{
    chating_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/chatting.png"),QSize(chating_btn->width()-10,chating_btn->height()-10));
    chating_btn->setStyleSheet("QPushButton{"
                               "border-radius: 1px transparent;"
                               "}");
    friends_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/friends.png"),QSize(friends_btn->width()-10,friends_btn->height()-10));
    friends_btn->setStyleSheet("QPushButton{"
                               "border-radius: 1px transparent;"
                               "}");
    groups_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/groups.png"),QSize(groups_btn->width()-10,groups_btn->height()-10));
    groups_btn->setStyleSheet("QPushButton{"
                              "border-radius: 1px transparent;"
                              "}");
    search_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/search.png"),QSize(search_btn->width()-10,search_btn->height()-10));
    search_btn->setStyleSheet("QPushButton{"
                              "border-radius: 1px transparent;"
                              "}");
    apps_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/apps.png"),QSize(apps_btn->width()-10,apps_btn->height()-10));
    apps_btn->setStyleSheet("QPushButton{"
                            "border-radius: 1px transparent;"
                            "}");
    setting_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/setting.png"),QSize(setting_btn->width()-10,setting_btn->height()-10));
    setting_btn->setStyleSheet("QPushButton{"
                               "border-radius: 1px transparent;"
                               "}");
}

void MainWidget::chatting_select()
{
    initAppBox();
    chating_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/chatting_select.png"),QSize(chating_btn->width()-10,chating_btn->height()-10));
}

void MainWidget::friends_select()
{
    initAppBox();
    friends_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/friends_select.png"),QSize(friends_btn->width()-10,friends_btn->height()-10));
}

void MainWidget::groups_select()
{
    initAppBox();
    groups_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/groups_select.png"),QSize(groups_btn->width()-10,groups_btn->height()-10));
}

void MainWidget::search_select()
{
    initAppBox();
    search_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/search_select.png"),QSize(search_btn->width()-10,search_btn->height()-10));
}

void MainWidget::apps_select()
{
    initAppBox();
    apps_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/apps_select.png"),QSize(apps_btn->width()-10,apps_btn->height()-10));
}

void MainWidget::setting_select()
{
    initAppBox();
    setting_btn->setNormalIcon(QIcon(":/image/btn/res/image/btn/setting_select.png"),QSize(setting_btn->width()-10,setting_btn->height()-10));
}
