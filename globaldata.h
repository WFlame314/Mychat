#ifndef GLOBALDATA_H
#define GLOBALDATA_H


class GlobalData
{
private:
    /*
     * @author:状态变量
     */
    bool connect_state;//联网状态
    bool login_state;//登录状态
    int online_state;//在线状态--->0:离线、1:在线、2:忙碌、3:隐身
    bool log_state;




public:
    GlobalData();
    bool get_Connect_State();
    bool get_Login_State();
    int get_Online_State();
    bool get_Log_State();

    void set_Connect_State(bool state);
    void set_Login_State(bool state);
    void set_Online_State(int state);
    void set_Log_State(bool state);

};

#endif // GLOBALDATA_H
