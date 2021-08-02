#ifndef WIDGETMANAGE_H
#define WIDGETMANAGE_H

#include <QWidget>
#include "logfiles.h"
#include "loginwidget.h"
#include "globaldata.h"

class WidgetManage : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetManage(GlobalData *basedata,Logfiles *log,QWidget *parent = nullptr);

    bool open_Loginwindow();

private:
    LoginWidget *loginwindow;
    GlobalData *basedata;
    Logfiles *log;

signals:
    void trylogin_signal(int type);

public slots:
    void trylogin_slot(int type);

};

#endif // WIDGETMANAGE_H
