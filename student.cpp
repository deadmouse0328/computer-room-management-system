#include "student.h"

//default constructor：
Student::Student(){

}

//para-constructor:
Student::Student(int id, string name, string passcode){
    this->m_id = id;
    this->m_Name = name;
    this->m_Passcode = passcode;

    //init computer room:
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_computer_id && ifs >> com.m_room_maxNumber){
        //put the read information to the container:
        vCom.push_back(com);
    }

    ifs.close();
}

//menu:
void Student::operMenu(){
    cout << "Welcome Student: " << this->m_Name << " Login" << endl;
    cout << "1. Apply reservation " << endl;
    cout << "2. Show my reservation " << endl;
    cout << "3. Check all reservation " << endl;
    cout << "4. Cancel reservation" << endl;
    cout << "5. Logout" << endl;
    cout << "Your choose: ";
}

//apply reservation：
void Student::apply_reservation(){
    cout << "\nComputer Room open time is: Monday -- Friday!" << endl;
    cout << "Select reservation time: " << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tuesday" << endl;
    cout << "3. Wednesday" << endl;
    cout << "4. Thursday" << endl;
    cout << "5. Friday" << endl;
    cout << "Choose: ";

    //date:
    int date = 0;
    //time zone:
    int interval = 0;
    //room number
    int room = 0;

    while (true){
        cin >> date;
        if (date >= 1 && date <= 5){
            //date is work(around 1 to 5)
            break;
        }
        cout << "Error input, try it again!\n" << endl;
        cout << "Choose: ";
    }

    cout << "\nSelect reservation Time Zone: " << endl;
    cout << "1. 8:00 AM - 11：00 AM " << endl;
    cout << "2. 1:00 PM - 4：00 PM" << endl;
    cout << "Choose: ";

    while (true){
        cin >> interval;
        if (interval >= 1 && interval <= 2){
            break;
        }
        cout << "Error input, try it again!\n" << endl;
        cout << "Choose: ";
    }

    cout << "\nSelect Computer Room information:" << endl;

    for (int i = 0; i < vCom.size(); i++){
        //20, 50, 100
        cout << "Computer Room " << vCom[i].m_computer_id << ", capability is: " << vCom[i].m_room_maxNumber << endl;
    }

    cout << "Choose: ";
    while (true){
        cin >> room;
        if (room >= 1 && room <= 3){
            break;
        }
        cout << "Error input, try it again!\n" << endl;
        cout << "Choose: ";
    }

    cout << "\nReserve Success!" << endl;
    cout << "Waiting Manager to verify...\n" << endl;

    //write to file:
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuID:" << this->m_id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomID:" << room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");
}

//check-self reservation:
void Student::show_my_reservation(){
    orderFile of;
    if (of.m_size == 0){
        cout << "No reservation record!" << endl;

        system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
        getchar();
        system("TERM=xterm-256color;clear");
        return;
    }

    for (int i = 0; i < of.m_size; i++){
        //use atoi convert string to int:
        if (this->m_id == atoi(of.m_orderData[i]["stuID"].c_str())){
            cout << "Reservation data: Week " << of.m_orderData[i]["date"] << ";";
            cout << " Time Zone: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 AM - 11：00 AM" : "1:00 PM - 4：00 PM") << ";";
            cout << " Computer Room Number: " << of.m_orderData[i]["roomID"] << "; ";

            string status = "status: ";
            //1-(still verify) 2-(verify success) -1-(reservation fail) 0-(cancel reserve);

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
    }

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");
}

//check all reservation:
void Student::check_all_reservation(){
    orderFile of;
    if (of.m_size == 0){
        cout << "No Reservation Record Now!" << endl;

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

//cancel reservation:
void Student::cancel_reservation(){
    orderFile of;
    if (of.m_size == 0){
        cout << "No Reservation Record Now!" << endl;

        system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
        getchar();
        system("TERM=xterm-256color;clear");
        return;
    }

    cout << "\nOnly verifying and verified Reservation Can be Canceled!" << endl;
    cout << "Which reservation you want to canceled: \n\n";

    //the vector store in the largest container index:
    vector<int> v;
    int index = 1;
    for (int i = 0; i < of.m_size; i++){
        //only self reservation can be canceled:
        if (this->m_id == atoi(of.m_orderData[i]["stuID"].c_str())){
            if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2"){
                v.push_back(i);
                cout << index++ << ".";
                cout << "Reservation data: Week " << of.m_orderData[i]["date"] << ";";
                cout << " Time Zone: " << (of.m_orderData[i]["interval"] == "1" ? "8:00 AM - 11：00 AM" : "1:00 PM - 4：00 PM") << ";";
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
        }

    }

    cout << "\nEnter reservation you want to canceled (0 to return): ";
    int select = 0;

    while (true){
        cin >> select;

        if (select >= 0 && select <= v.size()){
            if (select == 0) break;

            else {
                of.m_orderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "Reservation has been canceled successfully!" << endl;
                break;
            }
        }

        //wrong:
        cout << "Error input, please try it again: ";
    }

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");
}
