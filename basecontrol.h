#ifndef BASECONTROL_H
#define BASECONTROL_H

#include <QWidget>

class baseControl : public QWidget
{
    Q_OBJECT

public:
    baseControl(QWidget *parent = nullptr);
    ~baseControl();
};
#endif // BASECONTROL_H
