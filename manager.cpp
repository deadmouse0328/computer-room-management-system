#include "manager.h"


manager::manager(){

}

manager::manager(string name, string passcode){
    this->m_Name = name;
    this->m_Passcode = passcode;

    //initialize the container, and get stu and pro info:
    this->init_vector();

    //initialize the computer room information:
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;

    while(ifs >> com.m_computer_id && ifs >> com.m_room_maxNumber){
        vCom.push_back(com);
    }
    ifs.close();

    cout << "The Computer Room number is: " << vCom.size() << endl;
}

//show menu:
void manager::operMenu(){

    cout << "\nWelcome manager: '" << this->m_Name << "' Login! " << endl;
    cout << "\n1. Add Account " << endl;
    cout << "2. Check Account " << endl;
    cout << "3. Check Machine Room " << endl;
    cout << "4. Clean Reservation" << endl;
    cout << "0. Logout" << endl;
    cout << "\nPlease enter your choose: ";

}

//add a new account:
void manager::add_person(){

    while (true) {
        cout << "\nPlease Enter your add account type: " << endl;
        cout << "1. Student " << endl;
        cout << "2. Professor " << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";

        string fileName;
        string tip;
        string errorTip; //when replicated;

        int select = 0;

        cin >> select;

        if (select == 1) {
            //student:
            fileName = STUDENT_FILE;
            tip = "\nPlease enter student ID: ";
            errorTip = "Student ID replicated, please try it again!\n";
        } else if (select == 2) {
            //professor:
            fileName = TEACHER_FILE;
            tip = "\nPlease enter professor number: ";
            errorTip = "Professor ID replicated, please try it again!\n";
        } else if (select == 0) {
            break;
        } else {
            //incorrect:
            cout << "Invalid input, try it again!\n" << endl;
            continue;
        }

        ofstream ofs;
        ofs.open(fileName, ios::out | ios::app);

        int id;
        string name;
        string password;

        cout << tip;
        //cin >> id;

        while (true){
            cin >> id;
            bool ret = check_repeat(id, select);
            if (ret) {
                //replicated
                cout << errorTip << endl;
            } else {
                break;
            }

        }

        cout << "Please Enter Your Name: ";
        cin >> name;

        cout << "Please Enter Your Password: ";
        cin >> password;

        //add data to local file:
        ofs << id << " " << name << " " << password << " " << endl;
        cout << "\nAdd Success! " << endl;

//        cout << "\nPress any key to continue...";
//        cin.ignore(numeric_limits<streamsize>::max(),'\n');
//        cin.get();

        system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
        getchar();
        system("TERM=xterm-256color;clear");

        ofs.close();

        //initialize:
        this->init_vector();
    }
}

void print_student(Student &s){
    cout << "ID: " << s.m_id << "  Name: " << s.m_Name << "  Passcode: " << s.m_Passcode << endl;
}

void print_teacher(teacher &s){
    cout << "Employee ID: " << s.m_emplement_id << "  Name: " << s.m_Name << "  Passcode: " << s.m_Passcode  << endl;
}
//show account:
void manager::show_person(){
    cout << "\nPlease select check information: " << endl;
    cout << "1. All Student List " << endl;
    cout << "2. All Professor List" << endl;
    cout << "Your choice: ";

    int select = 0;
    cin >> select;

    if (select == 1) {
        //student:
        cout << "All student information: \n" << endl;
        for_each(v_Stu.begin(), v_Stu.end(), print_student);
        cout << endl;
    } else {
        //professor:
        cout << "All Professor information: \n" << endl;
        for_each(v_Tea.begin(), v_Tea.end(), print_teacher);
        cout << endl;
    }

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");
}

//check machine room reservation information:
void manager::show_computer(){
    //traverse this container:
    for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
        //room num, room max:
        cout << "Computer Room ID: " << it->m_computer_id << " Computer Room Max Size: " << it->m_room_maxNumber << endl;
    }

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");

}

//clean reservation records:
void manager::clean_file(){
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "\nClean success!" << endl;

    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");
}

//initialize the container:
void manager::init_vector(){
    //read file: 1. student 2. professor

    //make sure this two vector is empty:
    v_Stu.clear();
    v_Tea.clear();

    ifstream ifs;

    //read student file:
    ifs.open(STUDENT_FILE, ios::in);

    if(!ifs.is_open()) {
        cout << " File load fail! " << endl;
        return;
    }

    Student s;
    while (ifs >> s.m_id && ifs >> s.m_Name && ifs >> s.m_Passcode) {
        v_Stu.push_back(s);
    }

    //test:
    cout << "Current student number is: " << v_Stu.size() << endl;
    ifs.close();


    //read professor file:
    ifs.open(TEACHER_FILE, ios::in);
    teacher t;

    while (ifs >> t.m_emplement_id && ifs >> t.m_Name && ifs >> t.m_Passcode){
        v_Tea.push_back(t);
    }

    //test:
    cout << "Current teacher number is: " << v_Tea.size() << endl;
    ifs.close();

}

//check repetition:
bool manager::check_repeat(int id, int type){
    if (type == 1){
        //check student:
        for (vector<Student>::iterator it = v_Stu.begin(); it != v_Stu.end(); it++){
            if (id == it->m_id){
                return true;
            }
        }

    } else {
        //check professor:
        for (vector<teacher>::iterator it = v_Tea.begin(); it != v_Tea.end(); it++){
            if (id == it->m_emplement_id){
                return true;
            }
        }
    }

    return false;
}