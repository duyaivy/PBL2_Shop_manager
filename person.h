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
protected:
    string personID, name, phone, email, pass, role;
    static int nextID;
    string generateID();
public:
    
    person(const string _name = "unknown", const string _phone = "unknown", const string _email = "unknown", const string _pass = "unknown", const string _role = "customer");

    static void clearPerson();
    virtual void display()=0;
    string getName(); void setName();
    string getID();  string getRole();
    string getPhone(); void setPhone();
    string getEmail(); void setEmail();
    string getPass(); void setPass(); string hidenPass();
    virtual void setInfor(person& a)=0;  static void printTableHeader();
    static void printInfor(const person* person);
    static int login(string id, string pw, person* p);
};
#endif