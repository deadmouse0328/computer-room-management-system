#ifndef MACHINE_ROOM_RESERVATION_SYSTEM_MANAGER_H
#define MACHINE_ROOM_RESERVATION_SYSTEM_MANAGER_H

#include <iostream>
#include "identity.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "computerRoom.h"



class manager : public identity
{
public:
    manager();

    manager(string name, string passcode);

    //show menu:
    virtual void operMenu();

    //add a new account:
    void add_person();

    //show account:
    void show_person();

    //check machine room reservation information:
    void show_computer();

    //clean reservation records:
    void clean_file();

    //initialize the container:
    void init_vector();

    //check repetition:
    bool check_repeat(int id, int type);

    //student vector:
    vector<Student> v_Stu;

    //professor vector:
    vector<teacher> v_Tea;

    //computer room information:
    vector<ComputerRoom>vCom;


};


#endif //MACHINE_ROOM_RESERVATION_SYSTEM_MANAGER_H
