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

    //昵称按钮
    sign_btn->setFixedSize(130,20);
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

    //昵称按钮
    sign_btn->setText(basedata->get_user_info()->get_sign());
    sign_btn->setStyleSheet("QPushButton{"
                            "background-color:rgba(1,1,1,0.2);"
                            "font-size: 17px;"
                            "font-weight: 400;"
                            "color: rgb(255,255,255);"
                            "}");

}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(5, 5, this->width()-10, this->height()-10);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
//    painter.drawPixmap(5,5,width()-10,height()-10,bg);

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
    }
}


