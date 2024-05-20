#ifndef MACHINE_ROOM_RESERVATION_SYSTEM_ORDERFILE_H
#define MACHINE_ROOM_RESERVATION_SYSTEM_ORDERFILE_H
#include <iostream>
using namespace std;

#include "globalFile.h"
#include <fstream>
#include <map>
#include <string>

class orderFile {
public:

    //constructor:
    orderFile();

    //update reservation record:
    void updateOrder();

    //record reservation times:
    int m_size;

    //all reservation container (explain in p306):
    //key: m_size; value: <string, string>
    map<int, map<string, string>> m_orderData;



};


#endif //MACHINE_ROOM_RESERVATION_SYSTEM_ORDERFILE_H
