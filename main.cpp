#include <iostream>
#include <fstream>
#include <string>

#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

/*
 *
void printCurrentWorkingDirectoryAndFileName(const string& fileName) {
    char* cwd = getenv("PWD"); // 获取当前工作目录
    if (cwd) {
        cout << "Current working directory: " << cwd << endl;
        cout << "Trying to open file: " << cwd << "/" << fileName << endl;
    } else {
        cout << "Could not get current working directory." << endl;
        cout << "Trying to open file: " << fileName << endl;
    }
}
*
*/

//the sub student menu:
void studentMenu(identity* &student){
    while (true){
        //student choice menu:
        student->operMenu();

        //Student * stu = (Student* )student;
        Student * stu = dynamic_cast<Student*>(student);

        int select = 0;

        if (!(cin >> select)) {
            cin.clear(); // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入之后的字符，直到遇到新的一行
            cout << "Invalid input. Please enter a number: \n" << endl;
            continue; // 返回循环的开始
        }

        switch (select) {
            case 1:
                //apply reservation：
                stu->apply_reservation();
                break;
            case 2:
                //check-self reservation:
                stu->show_my_reservation();
                break;
            case 3:
                //check all reservation:
                stu->check_all_reservation();
                break;
            case 4:
                //cancel reservation:
                stu->cancel_reservation();
                break;
            case 5:
                //logout:
                delete student;
                student = nullptr;
                cout << "Logout Success" << endl;

                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");
                return;
            default:
                cout << "Error input, try it again!" << endl;
                break;
        }
    }
}
//enter the teacher sub menu:
void teacherMenu(identity * &teachers){

    while (true){
        //sub menu:
        teachers->operMenu();

        teacher * tea = dynamic_cast<teacher*>(teachers);

        int select = 0;

        if (!(cin >> select)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: \n" << endl;
            continue;
        }

        switch (select) {
            case 1:
                tea->check_reservation();
                break;
            case 2:
                tea->valid_reservation();
                break;
            case 0:
                delete teachers;
                teachers = nullptr;

                cout << "\nLogout Success" << endl;

                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");
                return;
            default:
                cout << "Error input, try it again!" << endl;
                break;
        }

    }
}

//the sub manager menu:
void managerMenu(identity * &man) {
    while (true) {
        //sub menu, use polymorphism:
        man->operMenu();

        //manager * man = dynamic_cast<manager*>(man);
        //manager *man = (manager*)man;

        manager* mgr = dynamic_cast<manager*>(man);
        if (!mgr) {
            cout << "Invalid manager type." << endl;
            break; // Or handle error appropriately
        }

        int select = 0;
        //cin >> select;
        if (!(cin >> select)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Skip bad input
            continue; // Skip the rest of this iteration
        }

        if (select == 1) {
            //add account:
            //cout << "Add account" << endl;
            mgr->add_person();
        } else if (select == 2) {
            //check account:
            //cout << "check account" << endl;
            mgr->show_person();
        } else if (select == 3) {
            //check machine room:
            //cout << "check machine room" << endl;
            mgr->show_computer();
        } else if (select == 4) {
            //empty reservation:
            //cout << "empty reservation" << endl;
            mgr->clean_file();
        }
        else {
            //log-out
            delete mgr;
            cout << "Logout Success!" << endl;
            system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
            getchar();
            system("TERM=xterm-256color;clear");
            break;
            return;
        }
    }
}


//log in:
//file name and identification type:
void LoginIn(string fileName, int type) {
    //printCurrentWorkingDirectoryAndFileName(fileName);

    //father printer to son:
    identity * person = NULL;

    //read file:
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //determine file exist or not:
    if (!ifs.is_open()) {
        cout << "File doesn't exist!" << endl;
        ifs.close();
        return;
    }

    //read file, receive info:
    int id = 0;
    string name;
    string passcode;

    if (type == 1) {
        //student:
        cout << "Please Enter you student ID: ";
        cin >> id;

    } else if (type == 2) {
        cout << "Please Enter your professor ID: ";
        cin >> id;
    }

    cout << "Please Enter your Name: ";
    cin >> name;

    cout << "Please Enter your Passcode: ";
    cin >> passcode;


    if (type == 1) {
        bool found = false;
        //student id check:
        int file_Id;
        string file_Name;
        string file_passcode;

        while (ifs >> file_Id && ifs >> file_Name && ifs >> file_passcode) {
            //compare with user information:
            if (file_Id == id && file_Name == name && file_passcode == passcode) {
                cout << "\nStudent Login Success!\n" << endl;

                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");

                person = new Student(id, name, passcode);

                //Login to student sub menu:
                studentMenu(person);
                return;

            }

        }

    } else if (type == 2) {
        //teacher id check:
        int file_Id;
        string file_Name;
        string file_passcode;

        while(ifs >> file_Id && ifs >> file_Name && ifs >> file_passcode) {
            if (file_Id == id && file_Name == name && file_passcode == passcode){
                cout << "\nTeacher Login Success!\n" << endl;

                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");

                person = new teacher(id, name, passcode);

                //Login to teacher sub menu:
                teacherMenu(person);
                return;
            }
        }



    } else if (type == 3) {
        //machine manager id check:
        string file_Name;
        string file_passcode;

        while(ifs >> file_Name && ifs >> file_passcode){
            if (file_Name == name && file_passcode == passcode){
                cout << "\nMachine Manager Login Success!\n" << endl;

                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");

                person = new manager(name, passcode);

                //Login to manager sub menu:
                managerMenu(person);

                return;
            }
        }


    }

    cout << "\nLogin Fail!\n" << endl;
    system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
    getchar();
    system("TERM=xterm-256color;clear");

}


int main() {
    //用于接收用户的选择：
    int select = 0;

    while (true)
    {

        cout << "Welcome to the machine room reservation system:" << endl;
        cout << "Please enter your identification: " << endl;
        cout << "1. Student" << endl;
        cout << "2. Professor" << endl;
        cout << "3. Library Manager " << endl;
        cout << "0. Exit " << endl;
        cout << "Your choice: ";

        cin >> select;

        switch (select) {
            case 1:
                //Student:
                LoginIn(STUDENT_FILE, 1);
                break;
            case 2:
                //Professor:
                LoginIn(TEACHER_FILE, 2);
                break;
            case 3:
                //Library Manager:
                LoginIn(ADMIN_FILE, 3);
                break;
            case 0:
                //Exit:
                //system( "\nread -n 1 -s -p \"; echo" );
                cout << "Bye!" << endl;
                getchar();
                return 0;
            default:
                //else:
                cout << "Error Input! Please Try it again!" << endl;
                system( "\nread -n 1 -s -p \"Press any key to continue...\"; echo" );
                getchar();
                system("TERM=xterm-256color;clear");
                break;
            
        }

    }

}
