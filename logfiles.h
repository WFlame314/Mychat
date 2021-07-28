#ifndef LOGFILES_H
#define LOGFILES_H

#include <QWidget>
#include <QString>
#include <QtDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include "globaldata.h"

#define cout qDebug()


class Logfiles : public QWidget
{
    Q_OBJECT
public:
    Logfiles(GlobalData *basedata,QWidget *parent = nullptr);
    ~Logfiles();
    void InsertLog(QString type,QString msg);
    void init();
    void info(QString msg);
    void error(QString msg);

private:
    QFile *logfile;
    QTextStream *out;
    GlobalData *basedata;

signals:


};

#endif // LOGFILES_H
