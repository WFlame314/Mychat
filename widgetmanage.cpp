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
        connect(loginwindow,SIGNAL(trylogin(int)),this,SLOT(trylogin_slot(int)));
        cout<<"yes";
        loginwindow->show();
        return true;
    }
    return false;
}

void WidgetManage::trylogin_slot(int type)
{
    emit trylogin_signal(type);
}
