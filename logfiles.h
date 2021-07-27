#ifndef LOGFILES_H
#define LOGFILES_H

#include <QWidget>
#include <QString>
#include <QtDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>

#define cout qDebug()


class Logfiles : public QWidget
{
    Q_OBJECT
public:
    Logfiles(QWidget *parent = nullptr);
    ~Logfiles();
    void InsertLog(QString type,QString msg);
    void init();

    QFile *logfile;
    QTextStream *out;

signals:
    void logfile_open_fail();
    void logdir_make_fail();
    void log_ready();

};

#endif // LOGFILES_H
