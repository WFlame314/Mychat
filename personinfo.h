#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QString>

class personinfo
{
public:
    personinfo();
    personinfo(QString account,QString name,QString remarkname,QString sign,QString lastwords,QString datetime,int groupid,int noreadcount,bool chatflag);


    QString account;
    QString name;
    QString remarkname;
    QString sign;
    QString lastwords;
    QString datetime;
    int groupid;
    int noreadcount;
    bool chatflag;

};

#endif // PERSONINFO_H
