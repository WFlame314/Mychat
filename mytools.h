#ifndef MYTOOLS_H
#define MYTOOLS_H

#include "qrencode.h"
#include <QString>
#include <QPixmap>
#include <QPainter>

class MyTools
{
public:
    MyTools();
    static void GernerateQRCode(const QString &text, QPixmap &qrPixmap, int scale);
};

#endif // MYTOOLS_H
