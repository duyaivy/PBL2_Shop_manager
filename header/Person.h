#ifndef PERSON_H
#define PERSON_H
#include<string>
#include "vector.h"
#include "Invoice.h"
using namespace std;

class Person {
protected:
    string ID, name, phone, email, pass, role;
    bool isDelete;
    cvector<string> idInvoice;
    virtual string generateID() = 0;
public:

    Person(const string& _name, const string& _phone, const string& _email, const string& _pass, const string& _role = "CUSTOMER",const bool & _isDelete = false);
    static void clearPerson();
    virtual void display() = 0;//ham ao
    int getDelete();
    void setDelete(int del);
    string getName(); void setName(const string&);
    string getID(); string getRole();
    string getPhone(); void setPhone(const string& );
    string getEmail(); void setEmail(const string&);
    string getPass(); void setPass(const string&); static string hidenPass();
    int addInvoice(string inv); cvector<string> getInvoice();
    virtual void setInfor() = 0;  
    static void printTableHeader(); 
    static void printInfor(const Person* Person);
    static void printAllInvoice(const Person* Person);
    static int login(string phone, string pw,cvector<Person*> &obj ,Person* &p);
    int getInforInvoice();
    static cvector<Person*> obj;
};
#endif