#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QPainter>
#include <QtMath>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include "globaldata.h"
#include "logfiles.h"
#include "personlist.h"
#include "Loading.h"
#include "mytools.h"
#include "mybutton.h"
#include "personinfo.h"

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
    void initAppBox();
    void initchattingbox();

protected slots:
    void chatting_select();
    void friends_select();
    void groups_select();
    void search_select();
    void apps_select();
    void setting_select();

signals:
    void readytoclose();

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
    QLabel *name_label;

    QLineEdit *sign_edit;

    QPushButton *sign_btn;
    MyButton *minisize_btn;
    MyButton *close_btn;
    MyButton *maxsize_btn;
    MyButton *hide_show_btn;
    MyButton *face_btn;
    MyButton *chating_btn;
    MyButton *friends_btn;
    MyButton *groups_btn;
    MyButton *search_btn;
    MyButton *apps_btn;
    MyButton *setting_btn;

    QStackedWidget *rightspace;

    QListWidget *appbox;
    QListWidget *chattingbox;

    PersonList *chattingarea;

};

#endif // MAINWIDGET_H
