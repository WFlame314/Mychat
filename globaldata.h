#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include <QWidget>
#include <QIcon>
#include <QProcess>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include "person.h"
#include "personinfo.h"

class GlobalData
{
private:
    /*
     * 状态变量
     */
    bool connect_state;//联网状态
    bool login_state;//登录状态
    int online_state;//在线状态--->0:离线、1:在线、2:忙碌、3:隐身
    int login_type;//登录模式--->0:手动模式
    bool log_state;
    bool user_db_state;
    bool remember_pass_state;

    /*
     * 标识变量
     */
    int ID; //用于日志中标识本次运行
    QString account;//账号

    /*
     * 资源
     */
    QIcon *LOGO;
    Person *user;
    QMap<int,QString> groups;
    QMap<int,int> groupstype;
    QMap<QString,personinfo> friendsinfo;
    QMap<QString,personinfo> chattingfriendinfo;

public:
    GlobalData();
    bool get_Connect_State();
    bool get_Login_State();
    int get_Online_State();
    bool get_Log_State();
    int get_ID();
    bool get_user_db_state();
    bool get_Remember_Pass_State();
    QIcon get_LOGO();
    Person * get_user_info();
    int get_Login_Type();
    QString get_uuid();
    QMap<int,QString> get_groups();
    QMap<QString,personinfo> get_friendsinfo();
    QMap<QString,personinfo> get_chattingfriendsinfo();

    void set_Connect_State(bool state);
    void set_Login_State(bool state);
    void set_Online_State(int state);
    void set_Log_State(bool state);
    void set_User_Db_State(bool state);
    void set_Remember_Pass_State(bool state);
    void set_user_info(Person *user);
    void set_Login_Type(int type);
    void set_groups(QJsonArray data);
    void set_friendsinfo(QJsonArray data);

};

#endif // GLOBALDATA_H
