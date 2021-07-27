#ifndef BASECONTROL_H
#define BASECONTROL_H

#include <QWidget>
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

    GlobalData *data;
    WidgetManage *widgetmanager;
    Logfiles *log;
public slots:
    void logfile_open_fail();
    void logdir_make_fail();
    void log_ready();

};
#endif // BASECONTROL_H
