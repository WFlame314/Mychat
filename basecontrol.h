#ifndef BASECONTROL_H
#define BASECONTROL_H

#include <QWidget>
#include <QMessageBox>
#include "globaldata.h"
#include "widgetmanage.h"
#include "logfiles.h"


class BaseControl : public QWidget
{
    Q_OBJECT

public:
    BaseControl(QWidget *parent = nullptr);
    ~BaseControl();



private:

    GlobalData *basedata;
    WidgetManage *widgetmanager;
    Logfiles *log;


public slots:
    void trylogin_slot(int type);

};
#endif // BASECONTROL_H
