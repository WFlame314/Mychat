#ifndef WIDGETMANAGE_H
#define WIDGETMANAGE_H

#include <QWidget>
#include "loginwidget.h"

class WidgetManage : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetManage(QWidget *parent = nullptr);

    bool open_Loginwindow();

private:
    LoginWidget *loginwindow;

signals:

};

#endif // WIDGETMANAGE_H
