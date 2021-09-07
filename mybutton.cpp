#include "mybutton.h"

MyButton::MyButton(QWidget *parent):QPushButton(parent)
{
    showhovericon = false;
    showpressedicon = false;
    this->setAttribute(Qt::WA_Hover,true);
    this->installEventFilter(this);
}

void MyButton::setNormalIcon(QIcon ico)
{
    normalicon = ico;
    this->setIcon(normalicon);
    this->setIconSize(this->size());
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

void MyButton::removeHoverIcon()
{
    showhovericon = false;
}

void MyButton::removePressIcon()
{
    showpressedicon = false;
}

bool MyButton::eventFilter(QObject *object, QEvent *event)
{
    this->setIconSize(this->size());
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

