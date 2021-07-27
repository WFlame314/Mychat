#include "basecontrol.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(false);

    BaseControl w;
    //w.show();

    return a.exec();
}
