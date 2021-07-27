#include "globaldata.h"

GlobalData::GlobalData()
{
    connect_state = false;
    login_state = false;
    online_state = 0;
    log_state = false;

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
