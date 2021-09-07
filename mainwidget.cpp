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
    setFixedSize(700,500);
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

    //最大化按钮
    maxsize_btn = new MyButton(this);

    //最小话按钮
    minisize_btn = new MyButton(this);

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


