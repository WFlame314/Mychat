#include "globaldata.h"

GlobalData::GlobalData()
{

    srand(time(0));
    connect_state = false;
    login_state = false;
    online_state = 0;
    log_state = false;
    user_db_state = false;

    ID = rand()%10000;

}

bool GlobalData::get_Login_State()
{
    return login_state;
}

bool GlobalData::get_Connect_State()
{
    return connect_state;
}

int GlobalData::get_Online_State()
{
    return online_state;
}

bool GlobalData::get_Log_State()
{
    return log_state;
}

int GlobalData::get_ID()
{
    return ID;
}

bool GlobalData::get_user_db_state()
{
    return user_db_state;
}




void GlobalData::set_Login_State(bool state)
{
    login_state = state;
}

void GlobalData::set_Connect_State(bool state)
{
    connect_state = state;
}

void GlobalData::set_Online_State(int state)
{
    online_state = state;
}

void GlobalData::set_Log_State(bool state)
{
    log_state = state;
}

void GlobalData::set_User_Db_State(bool state)
{
    user_db_state = state;
}









