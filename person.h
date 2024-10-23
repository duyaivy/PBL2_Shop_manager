#ifndef PERSON_H
#define PERSON_H
// chỉ nên include những thư viện cần thiết để tạo 1 class. Những thư viện khi viết code mới dùng thì nên include bên file .cpp
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <sstream> // Để sử dụng stringstream

using namespace std;


class person {
protected:
    string personID, name, phone, email, pass, role;
    static int nextID;
    string generateID();
public:
    
    person(const string _name = "unknown", const string _phone = "unknown", const string _email = "unknown", const string _pass = "unknown", const string _role = "customer");

    static void clearPerson();
    virtual void display()=0;//ham ao
    // phải sửa lại các hàm setName, set.... để tái sử dụng lại khi làm giao diện. 
    // Những hàm này phải có tham số truyền vào là một string, trong hàm chỉ làm việc set từ string truyền vào thôi. 
    string getName(); void setName();
    string getID();  string getRole();
    string getPhone(); void setPhone();
    string getEmail(); void setEmail();
    string getPass(); void setPass(); string hidenPass();
    virtual void setInfor(person& a)=0;  static void printTableHeader();// ham ao
    static void printInfor(const person* person);
    static int login(string id, string pw, person* p);
    // thêm hàm ảo load/ save từ file. 
};
static vector<person*> obj;
#endif