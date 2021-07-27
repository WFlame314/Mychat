#include "widgetmanage.h"

WidgetManage::WidgetManage(QWidget *parent) : QWidget(parent)
{

}

bool WidgetManage::open_Loginwindow()
{
    if((loginwindow = new LoginWidget()))
    {
        loginwindow->show();
        return true;
    }
    return false;
}
