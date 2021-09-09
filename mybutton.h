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
    void setName(QString name);
    void removeHoverIcon();
    void removePressIcon();

    QString getName();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    bool showhovericon;
    bool showpressedicon;
    QIcon normalicon;
    QIcon hovericon;
    QIcon pressedicon;
    QString name;
};

#endif // MYBUTTON_H
