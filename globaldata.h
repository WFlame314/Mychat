#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include <QWidget>

class GlobalData
{
private:
    /*
     * 状态变量
     */
    bool connect_state;//联网状态
    bool login_state;//登录状态
    int online_state;//在线状态--->0:离线、1:在线、2:忙碌、3:隐身
    bool log_state;
    bool user_db_state;
    bool remember_pass_state;

    /*
     * 标识变量
     */
    int ID; //用于日志中标识本次运行
    QString account;//账号





public:
    GlobalData();
    bool get_Connect_State();
    bool get_Login_State();
    int get_Online_State();
    bool get_Log_State();
    int get_ID();
    bool get_user_db_state();
    bool get_Remember_Pass_State();

    void set_Connect_State(bool state);
    void set_Login_State(bool state);
    void set_Online_State(int state);
    void set_Log_State(bool state);
    void set_User_Db_State(bool state);
    void set_Remember_Pass_State(bool state);

};

#endif // GLOBALDATA_H
