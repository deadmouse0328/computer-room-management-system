#ifndef MACHINE_ROOM_RESERVATION_SYSTEM_STUDENT_H
#define MACHINE_ROOM_RESERVATION_SYSTEM_STUDENT_H
#include <iostream>
#include "identity.h"
#include <string>
#include <vector>
#include "computerRoom.h"
#include <fstream>
#include "globalFile.h"
#include "orderFile.h"

using namespace std;

//student class:
class Student : public identity
{
public:
    //default constructor：
    Student();

    //para-constructor:
    Student(int id, string name, string passcode);

    //menu:
    virtual void operMenu();

    //apply reservation：
    void apply_reservation();

    //check-self reservation:
    void show_my_reservation();

    //check all reservation:
    void check_all_reservation();

    //cancel reservation:
    void cancel_reservation();

    //student id:
    int m_id;

    //computer room container:
    vector<ComputerRoom> vCom;

};

#endif //MACHINE_ROOM_RESERVATION_SYSTEM_STUDENT_H
