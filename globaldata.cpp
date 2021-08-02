#include "globaldata.h"

GlobalData::GlobalData()
{

    srand(time(0));
    connect_state = false;
    login_state = false;
    online_state = 0;
    log_state = false;
    user_db_state = false;
    remember_pass_state = false;
    LOGO = new QIcon(":/image/icon/res/image/icon/hi.png");
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

bool GlobalData::get_Remember_Pass_State()
{
    return remember_pass_state;
}

QIcon GlobalData::get_LOGO()
{
    return *LOGO;
}

Person* GlobalData::get_user_info()
{
    return user;
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

void GlobalData::set_Remember_Pass_State(bool state)
{
    remember_pass_state = state;
}

void GlobalData::set_user_info(Person *user)
{
    this->user = user;
}





