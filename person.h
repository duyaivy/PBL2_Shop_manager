#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <sstream> // Để sử dụng stringstream

using namespace std;

class person {
private:
    string personID, name, phone, email, pass;
    static int nextID; // Biến tĩnh cho ID kế tiếp
    static vector<person*> obj; // Biến tĩnh cho danh sách đối tượng

    string generateID(); 

public:
    person(const string _name = "unknown", const string _phone = "unknown", const string _email = "unknown", const string _pass = "unknown");

    static void clearPerson();
    static void display();
    string getName();
    void setName(); 
    string getID();  
    string getPhone();
    void setPhone(); 
    string getEmail(); 
    void setEmail(); 
    string getPass(); 
    void setPass(); 
    string hidenPass();
    static void setInfor(person &a);
    static void printInfor(const person* person);
    static void printTableHeader();

};

// Định nghĩa biến tĩnh trong cùng tệp header
int person::nextID = 0;
vector<person*> person::obj;

string person::generateID() {
    // Chuyển nextID thành chuỗi có 7 chữ số, thêm số 0 ở phía trước
    stringstream ss;
    ss << setw(7) << setfill('0') << nextID;
    nextID++; // Tăng nextID lên 1 cho người kế tiếp
    return ss.str(); // Trả về giá trị
}

person::person(const string _name, const string _phone, const string _email, const string _pass) {
    name = _name;
    phone = _phone;
    email = _email;
    pass = _pass;
    personID = generateID();
    obj.push_back(this); 
}

void person::clearPerson() {
    for (person* p : obj) {
        delete p;  // Xóa đối tượng
    }
    obj.clear();  // Xóa vector
    obj.shrink_to_fit();  
}

string person::getName() {
    return name;
}

void person::setName() {
    cout << "Enter Fullname: ";
    getline(cin, name);
} 

string person::getID() {
    return personID;
}

string person::getPhone() {
    return phone;
}

void person::setPhone() {
    cout << "Enter Phone number: ";
    getline(cin, phone);
} 

string person::getEmail() {
    return email;
}

void person::setEmail() {
    cout << "Enter your Email: ";
    getline(cin, email);
} 

string person::hidenPass() {
    string password = "";
    char ch;
    while ((ch = _getch()) != 13) {
        if (ch == 8) {  // Nếu người dùng nhấn phím Backspace
            if (!password.empty()) {
                cout << "\b \b";  
                password.pop_back();  
            }
        } else {
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

void person::setPass() {
    string password, confirmPass;  
    cout << "Enter password:\t";
    password = hidenPass();
    int todo = 1, maxTry = 3;

    while (todo < maxTry) {
        cout << "Confirm password: ";
        confirmPass = hidenPass();
        if (password == confirmPass) {
            pass = password; // Gán mật khẩu
            cout << "Password set successfully!" << endl;
            break;
        } else {
            todo++;
            if (todo < maxTry) {
                cout << "Passwords do not match. Please try again!" << endl;
            } else {
                cout << "Maximum attempts reached. Password not set." << endl;
            }   
        }
    }
}

void person::setInfor(person &a) {
    a.setName(); 
    a.setPhone();
    a.setEmail();
}
void person::printTableHeader() {
    cout << left << setw(10) << "ID"
         << setw(20) << "Full Name"
         << setw(30) << "Email"
         << setw(15) << "Phone"
         << endl;
    cout << "-----------------------------------------------------------------------" << endl;
}

void person::printInfor(const person* a)  {
    cout << left << setw(10) << a->personID   // ID cột 1
         << setw(20) << a->name               // Tên cột 2
         << setw(30) << a->email              // Email cột 3
         << setw(15) << a->phone              // Số điện thoại cột 4
         << endl;
}

void person::display() {
    if (obj.empty()) {
        cout << "The program is NULL" << endl;
    } else {
        printTableHeader();  // In tiêu đề bảng
        for (person* p : obj) {
            printInfor(p);   // In thông tin từng person
        }
    }
}



#endif // PERSON_H
