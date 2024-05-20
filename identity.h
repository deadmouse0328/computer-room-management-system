#ifndef MACHINE_ROOM_RESERVATION_SYSTEM_IDENTITY_H
#define MACHINE_ROOM_RESERVATION_SYSTEM_IDENTITY_H

#include <iostream>
#include <string>
using namespace std;

//identity abstract class:
class identity
{
public:
    //name, passcode:
    string m_Name;
    string m_Passcode;

    //操作菜单，子类必须要写父类中的纯虚函数：
    virtual void operMenu() = 0;

    virtual ~identity() = default;
};
#endif
