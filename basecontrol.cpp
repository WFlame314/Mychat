#include "basecontrol.h"

BaseControl::BaseControl(QWidget *parent)
    : QWidget(parent)
{
    basedata = new GlobalData();
    log = new Logfiles(basedata);
    log->init();
    widgetmanager = new WidgetManage(basedata,log);
    connect(widgetmanager,SIGNAL(trylogin_signal(int)),this,SLOT(trylogin_slot(int)));
    if(widgetmanager->open_Loginwindow())
    {
        if(basedata->get_Log_State())
        {
            log->info("LOGWINDOW OPENED!");
        }
        else
        {
            QMessageBox::warning(this,"日志文件错误","日志文件打开失败！");
        }
    }else
    {
        log->error("LOGWINDOW OPEN FAILED!");
    }
}

BaseControl::~BaseControl()
{
    log->info("ALL CLOSED!");
    delete basedata;
    delete log;
    delete widgetmanager;
}

void BaseControl::trylogin_slot(int type)
{
    cout<<basedata->get_user_info()->get_account()<<basedata->get_user_info()->get_name()<<basedata->get_user_info()->get_passwordkey()<<type;
}
