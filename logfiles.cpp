#include "logfiles.h"

Logfiles::Logfiles(QWidget *parent)
    : QWidget(parent)
{

}

Logfiles::~Logfiles()
{
    logfile->close();
    delete out;
    delete logfile;
}

void Logfiles::init()
{
    QDir dir;
    if(dir.mkpath("./log"))
    {
        logfile = new QFile("./log/"
                            +QDateTime::currentDateTime().date().toString(Qt::ISODate)
                            +".log");
        if(logfile->open(QIODevice::WriteOnly| QIODevice::Append))
        {
            out = new QTextStream(logfile);
            InsertLog("Info","open logfile success!");
            emit log_ready();
        }else
        {
            emit logfile_open_fail();
        }
    }else
    {
        emit logdir_make_fail();
    }
}

void Logfiles::InsertLog(QString type, QString msg)
{
    cout<<QDateTime::currentDateTime().toString(Qt::ISODate)<<"  [ "<<type<<" ]:  "<<msg<<"\n";
    *out<<QDateTime::currentDateTime().toString(Qt::ISODate)<<"  [ "<<type<<" ]:  "<<msg<<"\n";
}
