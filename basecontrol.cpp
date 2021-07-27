#include "basecontrol.h"

BaseControl::BaseControl(QWidget *parent)
    : QWidget(parent)
{
    data = new GlobalData();
    widgetmanager = new WidgetManage();
    log = new Logfiles();
    connect(log,SIGNAL(logfile_open_fail()),this,SLOT(logfile_open_fail()));
    connect(log,SIGNAL(logdir_make_fail()),this,SLOT(logdir_make_fail()));
    connect(log,SIGNAL(log_ready()),this,SLOT(log_ready()));
    log->init();
    if(widgetmanager->open_Loginwindow())
    {
        if(data->get_Log_State())
        {
            log->InsertLog("Info","loginwindow opened!");
        }
    }
}

BaseControl::~BaseControl()
{
    delete data;
    delete log;
    delete widgetmanager;
}

void BaseControl::logdir_make_fail()
{
    data->set_Log_State(false);
}

void BaseControl::logfile_open_fail()
{
    data->set_Log_State(false);
}

void BaseControl::log_ready()
{
    data->set_Log_State(true);
}
