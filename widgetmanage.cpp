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
        loginwindow->show();
        return true;
    }
    return false;
}
