#include "mybutton.h"

MyButton::MyButton(QWidget *parent):QPushButton(parent)
{
    showhovericon = false;
    showpressedicon = false;
    name = "";
    this->setAttribute(Qt::WA_Hover,true);
    this->installEventFilter(this);
    iconsize = this->size();
}

void MyButton::setNormalIcon(QIcon ico)
{
    normalicon = ico;
    this->setIcon(normalicon);
    iconsize = this->size();
    this->setIconSize(iconsize);
}

void MyButton::setNormalIcon(QIcon ico,QSize size)
{
    normalicon = ico;
    this->setIcon(normalicon);
    iconsize = size;
    this->setIconSize(iconsize);
}

void MyButton::setHoverIcon(QIcon ico)
{
    hovericon = ico;
    showhovericon = true;
}

void MyButton::setPressedIcon(QIcon ico)
{
    pressedicon = ico;
    showpressedicon = true;
}

void MyButton::setName(QString name)
{
    this->name = name;
    if(name!="")
    {
        this->setToolTip(name);
    }
}

void MyButton::removeHoverIcon()
{
    showhovericon = false;
}

void MyButton::removePressIcon()
{
    showpressedicon = false;
}

QString MyButton::getName()
{
    return name;
}

bool MyButton::eventFilter(QObject *object, QEvent *event)
{
    this->setIconSize(iconsize);
    if(event->type() == QEvent::HoverEnter)
    {
        if(showhovericon)
        {
            this->setIcon(hovericon);
        }
    }else if(event->type() == QEvent::HoverLeave)
    {
        this->setIcon(normalicon);
    }else if(event->type() == QEvent::MouseButtonPress)
    {
        if(showpressedicon)
        {
            this->setIcon(pressedicon);
        }
    }else if(event->type() == QEvent::MouseButtonRelease)
    {
        this->setIcon(normalicon);
    }
    return QPushButton::eventFilter(object,event);
}

