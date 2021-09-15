#ifndef WIDGETMANAGE_H
#define WIDGETMANAGE_H

#include <QWidget>
#include "logfiles.h"
#include "loginwidget.h"
#include "globaldata.h"
#include "mainwidget.h"

class WidgetManage : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetManage(GlobalData *basedata,Logfiles *log,QWidget *parent = nullptr);

    bool open_Loginwindow();

    bool open_Mainwindow();

    void sendinfo_to_loginwindow(int type,QJsonObject msg);

private:
    LoginWidget *loginwindow;
    MainWidget *mainwindow;
    GlobalData *basedata;
    Logfiles *log;

signals:
    void trylogin_signal(int type,bool ifremember);
    void login_finished();
    void getfriends();
    void maincloseed();

public slots:
    void trylogin_slot(int type,bool ifremember);
    void login_finished_slot();
    void file_done();
    void mainreadytoclose();

};

#endif // WIDGETMANAGE_H
