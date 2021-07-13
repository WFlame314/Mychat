#include "basecontrol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    baseControl w;
    w.show();
    return a.exec();
}
