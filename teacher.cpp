#include "teacher.h"

teacher::teacher(){

}
teacher::teacher(int emplement_id, string name, string passcode){
    this->m_emplement_id = emplement_id;
    this->m_Name = name;
    this->m_Passcode = passcode;

}

//menu:
void teacher::operMenu(){
    cout << "Welcome Professor: " << this->m_Name << " Login.\n" << endl;
    cout << "1. Check all reservation. " << endl;
    cout << "2. Verity reservation." << endl;
    cout << "0. Logout" << endl;
    cout << "Your choice: ";

}

//check reservation:
void teacher::check_reservation(){
    orderFile of;
    if (of.m_size == 0){
        cout << "No Reservation Record..." << endl;
        system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
        getchar();
        system("TERM=xterm-256color;clear");
        return;
    }

    for (int i = 0; i < of.m_size; i++){
        cout << i + 1 << ".";
        cout << "Reservation data: Week " << of.m_orderData[i]["date"] << ";";
        cout << " Time Zone: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 AM - 11：00 AM" : "1:00 PM - 4：00 PM") << ";";
        cout << " Student ID: " << of.m_orderData[i]["stuID"] << ";";
        cout << " Student Name: " << of.m_orderData[i]["stuName"] << ";";
        cout << " Computer Room Number: " << of.m_orderData[i]["roomID"] << "; ";

        string status = "status: ";
        if (of.m_orderData[i]["status"] == "1"){
            status += " Still verity...";
        } else if (of.m_orderData[i]["status"] == "2"){
            status += " Verify success! ";
        }else if (of.m_orderData[i]["status"] == "-1"){
            status += " Reservation Failed, verity cannot passed! ";
        } else {
            status += " Reservation Canceled.";
        }
        cout << status << endl;
    }
    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");

}

//valid reservation:
void teacher::valid_reservation(){
    orderFile of;
    if (of.m_size == 0){
        cout << "No Reservation Record..." << endl;
        system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
        getchar();
        system("TERM=xterm-256color;clear");
        return;
    }

    cout << "\nThe waiting verifying reservation as follows: " << endl;

    vector<int> v;
    int index = 0;
    for (int i = 0; i < of.m_size; i++){
        if (of.m_orderData[i]["status"] == "1"){
            //still waiting:
            v.push_back(i);
            cout << ++index << ". ";
            cout << "Reservation data: Week " << of.m_orderData[i]["date"] << ";";
            cout << " Time Zone: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 AM - 11：00 AM" : "1:00 PM - 4：00 PM") << ";";
            cout << " Student ID: " << of.m_orderData[i]["stuID"] << ";";
            cout << " Student Name: " << of.m_orderData[i]["stuName"] << ";";
            cout << " Computer Room Number: " << of.m_orderData[i]["roomID"] << "; ";

            string status = " status: verifying...";
            cout << status << endl;
        }
    }

    cout << "Enter verify number (0 - return): ";
    int select = 0;
    int ret = 0; // verify result

    while (true) {
        cin >> select;

        if (select >= 0 && select <= v.size()){
            //logout
            if (select == 0) break;

            else {// pass or not
                cout << "Enter verify result." << endl;
                cout << "1. Pass" << endl;
                cout << "2. No Pass" << endl;
                cout << "Choice: ";

                cin >> ret;

                if (ret == 1){
                    //pass:
                    of.m_orderData[v[select - 1]]["status"] = "2";
                } else {
                    //no pass:
                    of.m_orderData[v[select - 1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "\nVerify Finish!" << endl;
                break;
            }
        }
        cout << "Invalid input, try it again: ";
    }
    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");

}