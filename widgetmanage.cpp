#include "widgetmanage.h"

WidgetManage::WidgetManage(GlobalData *basedata,Logfiles *log,QWidget *parent) : QWidget(parent)
{
    this->basedata = basedata;
    this->log = log;
}

bool WidgetManage::open_Loginwindow()
{
    if((loginwindow = new LoginWidget(basedata,log)))
    {
        connect(loginwindow,SIGNAL(trylogin(int,bool)),this,SLOT(trylogin_slot(int,bool)));
        connect(loginwindow,&LoginWidget::login_finished,this,&WidgetManage::login_finished_slot);
        cout<<"yes";
        loginwindow->show();
        return true;
    }
    return false;
}

bool WidgetManage::open_Mainwindow()
{
    if((mainwindow = new MainWidget(basedata,log)))
    {
        cout<<"yes";
        mainwindow->show();
        return true;
    }
    return false;
}

void WidgetManage::trylogin_slot(int type,bool ifremember)
{
    emit trylogin_signal(type,ifremember);
}

void WidgetManage::sendinfo_to_loginwindow(int type, QJsonObject msg)
{
    if(loginwindow != nullptr)
    {
        loginwindow->getinfo(type,msg);
    }else
    {
        log->error("Loginwindow does not open!");
    }
}

void WidgetManage::login_finished_slot()
{
    loginwindow->close();
    emit login_finished();
}
