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
    this->basedata = basedata;
    this->log = log;
    if(!bg.load(":/image/windows/res/image/windows/def_background.jpeg"))
    {
        log->error("background load failed!");
    }

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::init()
{
    init_Size();
    init_Pos();
    init_Style();
}

void MainWidget::init_Pos()
{

}

void MainWidget::init_Size()
{

}

void MainWidget::init_Style()
{

}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(5, 5, this->width()-10, this->height()-10);

    QPainter painter(this);
    painter.drawPixmap(5,5,width()-10,height()-10,bg);

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


