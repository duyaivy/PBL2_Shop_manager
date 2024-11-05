#include "person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include "vector.h"
using namespace std;

// ham dung constructor
person::person(const string& _name, const string& _phone, const string& _email, const string& _pass, const string& _role) {
    name = _name; phone = _phone;
    email = _email; pass = _pass;
    role = _role;
    obj.push_back(this);

}
//  ham dung destructor
void person::clearPerson() {

    for (person* p : obj) {
        delete p;  // Delete 
    }
    obj.clear();  // Clear the vector
    obj.shrink_to_fit();// 

}

// name
string person::getName() {
    return name;
}
// phải sửa lại các hàm setName, set.... để tái sử dụng lại khi làm giao diện. 
// Những hàm này phải có tham số truyền vào là một string, trong hàm chỉ làm việc set từ string truyền vào thôi. 
//ở đây thì chỉ là this->name = name truyền vào.tươgn tự sửa hết các hàm set
void person::setName(const string& t_name) {
    name = t_name;
};

// ID
string person::getID() {
    return ID;
}
// phone
string person::getPhone() {
    return phone;
}
void person::setPhone(const string& t_phone) {
    phone = t_phone;
};
// email
string person::getEmail() {
    return email;
}
void person::setEmail(const string& t_email) {
    email = t_email;
};
// pass
// ham hien thi dau * cho pass
string person::hidenPass() {
    string password = "";
    char ch;
  
    while ((ch = _getch()) != 13) {
        if (ch == 8) {  
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
string person::getPass() {
    return pass;
}
string person::getRole() {
    return role;
}

void person::setPass(const string& _pass) {
    this->pass = _pass;
}




void person::printInfor(const person* a) {
    cout << left << setw(10) << "ID:" << setw(10) << a->ID << endl
        << left << setw(10) << "FullName:" << setw(20) << a->name << endl
        << left << setw(10) << "Email:" << setw(30) << a->email << endl
        << left << setw(10) << "Phone:" << setw(15) << a->phone << endl
        << "----------------------------------------" << endl;
}

int person::login(string id, string pw, person* p) {
    for (person* person : obj) {
        if ((person->getID()) == id) {
            if (person->getPass() == pw) {
                *p = *person;
                return 1;
            }
            else return 0;
        }
    }
    return 0;
}

void person::printTableHeader() {
    cout << left << setw(10) << "ID"
         << setw(20) << "Full Name"
         << setw(30) << "Email"
         << setw(15) << "Phone"
         << endl;
    cout << "-----------------------------------------------------------------------" << endl;
}