#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QWidget *parent = nullptr);
    void setNormalIcon(QIcon ico);
    void setHoverIcon(QIcon ico);
    void setPressedIcon(QIcon ico);
    void removeHoverIcon();
    void removePressIcon();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    bool showhovericon;
    bool showpressedicon;
    QIcon normalicon;
    QIcon hovericon;
    QIcon pressedicon;
};

#endif // MYBUTTON_H
