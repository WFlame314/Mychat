#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPainter>
#include <QtMath>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include "globaldata.h"
#include "logfiles.h"
#include "personlist.h"
#include "Loading.h"
#include "mytools.h"
#include "mybutton.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(GlobalData *basedata,Logfiles *log,QWidget *parent = nullptr);
    ~MainWidget();
    void init();
    void init_Size();
    void init_Pos();
    void init_Style();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWidget *ui;
    GlobalData *basedata; //公共数据
    QPoint p;//记录鼠标在窗口中的位置
    Logfiles *log;
    QPixmap pix;
    QImage LOGO;

    /*
     * 窗口中组件
     */
    QLabel *LOGO_label;
    MyButton *minisize_btn;
    MyButton *close_btn;
    MyButton *maxsize_btn;
    MyButton *hide_btn;

};

#endif // MAINWIDGET_H