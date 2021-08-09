#include "sql.h"

SQL::SQL(QObject *parent) : QObject(parent)
{

}

void SQL::trytoconnect(QString sqltype, QString HostName, QString DatabaseName, QString Username, QString Password)
{
    db=QSqlDatabase::addDatabase(sqltype);
    db.setDatabaseName(DatabaseName);
    db.setPort(3306);
    db.setHostName(HostName);
    db.setUserName(Username);
    db.setPassword(Password);
    if(db.open())
    {
        connectback(1);
        qDebug()<<"yes";
    }
    else
    {
        connectback(0);
        qDebug()<<"no";
    }
}


void SQL::connectback(int type)
{
    emit connecttomysql(type);
}
