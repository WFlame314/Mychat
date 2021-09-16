#include "personinfo.h"

personinfo::personinfo()
{
    account = "";
    name = "";
    remarkname = "";
    sign = "";
    lastwords = "";
    chatflag = false;
    noreadcount = 0;
    groupid = -1;
}

personinfo::personinfo(QString account,QString name,QString remarkname,QString sign,QString lastwords,QString datetime,int groupid,int noreadcount,bool chatflag)
{
    this->account = account;
    this->name = name;
    this->remarkname = remarkname;
    this->lastwords = lastwords;
    this->groupid = groupid;
    this->noreadcount = noreadcount;
    this->chatflag = chatflag;
    this->sign = sign;
    this->datetime = datetime;
}


