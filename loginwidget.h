#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "globaldata.h"
#include "logfiles.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(GlobalData *basedata,Logfiles *log,QWidget *parent = nullptr);
    ~LoginWidget();
    void init();
    void init_Size();
    void init_Pos();
    void init_Style();
    void init_Userinfo();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    Ui::LoginWidget *ui;
    GlobalData *basedata; //公共数据
    QPoint p;//记录鼠标在窗口中的位置
    Logfiles *log;
    QSqlDatabase database;

    /*
     * 窗口中组件
     */
    QPushButton *close_btn;
    QLabel *face_image;


public slots:
    void close_window();


};

#endif // LOGINWIDGET_H
