#include "orderFile.h"

//constructor:
orderFile::orderFile(){
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);

    //date:
    string date;
    //time zone:
    string interval;
    //student id:
    string stuID;
    string stuName;
    string roomID;
    string status;

    this->m_size = 0;

    while (ifs >> date && ifs >> interval &&
           ifs >> stuID && ifs >> stuName &&
           ifs >> roomID && ifs >> status){

//        //test code:
//        cout << date << endl;
//        cout << interval << endl;
//        cout << stuID << endl;
//        cout << stuName << endl;
//        cout << roomID << endl;
//        cout << status << endl;
//        cout << endl;

        //date: 1
        string key;
        string value;
        map<string, string> m;

        int pos = date.find(":");
        if (pos != -1){
            key = date.substr(0,pos);
            value = date.substr(pos + 1, date.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

//        cout << "key = " << key << endl;
//        cout << "value = " << value << endl;

        pos = interval.find(":");
        if (pos != -1){
            key = interval.substr(0,pos);
            value = interval.substr(pos + 1, interval.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

        pos = stuID.find(":");
        if (pos != -1){
            key = stuID.substr(0,pos);
            value = stuID.substr(pos + 1, stuID.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

        pos = stuName.find(":");
        if (pos != -1){
            key = stuName.substr(0,pos);
            value = stuName.substr(pos + 1, stuName.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

        pos = roomID.find(":");
        if (pos != -1){
            key = roomID.substr(0,pos);
            value = roomID.substr(pos + 1, roomID.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

        pos = status.find(":");
        if (pos != -1){
            key = status.substr(0,pos);
            value = status.substr(pos + 1, status.size() - pos - 1);

            m.insert(make_pair(key,value));
        }

        //put small map to larger map:
        this->m_orderData.insert(make_pair(this->m_size, m));
        this->m_size++;

    }
    ifs.close();

    //test larger map:
//    for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++){
//        cout << "times = " << it->first << " value = " << endl;
//
//
//        //traverse small map:
//        for (map<string, string>::iterator it2 = (*it).second.begin(); it2 != it->second.end(); it2++){
//            cout << "key = " << it2->first << " value = " << it2->second << " ";
//        }
//        cout << endl;
//    }

}

//update reservation record:
void orderFile::updateOrder(){
    if (this->m_size == 0){
        //no reserve record;
        return;
    }

    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);

    for (int i = 0; i < this->m_size; i++){
        ofs << "date:" << this->m_orderData[i]["date"] << " ";
        ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
        ofs << "stuID:" << this->m_orderData[i]["stuID"] << " ";
        ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
        ofs << "roomID:" << this->m_orderData[i]["roomID"] << " ";
        ofs << "status:" << this->m_orderData[i]["status"] << endl;

    }

    ofs.close();
}