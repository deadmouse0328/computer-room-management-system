#ifndef MACHINE_ROOM_RESERVATION_SYSTEM_TEACHER_H
#define MACHINE_ROOM_RESERVATION_SYSTEM_TEACHER_H

#include <iostream>
#include <string>
#include <vector>
#include "identity.h"
#include "orderFile.h"
using namespace std;

class teacher : public identity
{
public:

    teacher();
    teacher(int emplement_id, string name, string passcode);

    //ID;
    int m_emplement_id;


    //menu:
    virtual void operMenu();

    //check reservation:
    void check_reservation();

    //valid reservation:
    void valid_reservation();


};


#endif //MACHINE_ROOM_RESERVATION_SYSTEM_TEACHER_H
