#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QTime>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

class SQL : public QObject
{
    Q_OBJECT
public:
    explicit SQL(QObject *parent = nullptr);
    void trytoconnect(QString sqltype,QString HostName,QString DatabaseName,QString Username,QString Password);
    void connectback(int);

signals:
    void connecttomysql(int);

protected:
    QSqlDatabase db;

};

#endif // SQL_H
