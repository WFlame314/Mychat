#include "logfiles.h"

Logfiles::Logfiles(GlobalData *basedata,QWidget *parent)
    : QWidget(parent)
{
    this->basedata = basedata;
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
            InsertLog("INFO","OPEN LOGFILE SUCCESS!");
            logfile->close();
            basedata->set_Log_State(true);
        }else
        {
            basedata->set_Log_State(false);
        }
    }else
    {
        basedata->set_Log_State(false);
    }
}

void Logfiles::InsertLog(QString type, QString msg)
{
    cout<<"[ "
        <<QDateTime::currentDateTime().toString(Qt::ISODate)
        <<" ] "
        <<basedata->get_ID()
        <<" "
        <<"  [ "<<type<<" ]:  "
        <<msg.toUtf8()<<"\n";
    *out<<"[ "
        <<QDateTime::currentDateTime().toString(Qt::ISODate)
        <<" ] "
        <<basedata->get_ID()
        <<" "
        <<"  [ "<<type<<" ]:  "
        <<msg.toUtf8()<<"\n";
}

void Logfiles::info(QString msg)
{
    if(logfile->open(QIODevice::WriteOnly| QIODevice::Append))
    {
        out->setDevice(logfile);
        InsertLog("INFO",msg);
        logfile->close();
    }
}

void Logfiles::error(QString msg)
{
    if(logfile->open(QIODevice::WriteOnly| QIODevice::Append))
    {
        out->setDevice(logfile);
        InsertLog("ERROR",msg);
        logfile->close();
    }
}
