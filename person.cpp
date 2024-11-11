#include "./header/Person.h"
#include "./header/Invoice.h"
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <iostream>
cvector<Person*> Person::obj;

using namespace std;

// ham dung constructor
Person::Person(const string& _name, const string& _phone, const string& _email, const string& _pass, const string& _role) {
    name = _name; phone = _phone;
    email = _email; pass = _pass;
    role = _role;
    isDelete = 0;
    // obj.push_back(this);
}
//  ham dung destructor
void Person::clearPerson() {

    for (Person* p : obj) {
        delete p;  // Delete 
    }
    obj.clear();  // Clear the vector
    obj.shrink_to_fit();// 

}

// name
string Person::getName() {
    return name;
}

void Person::setName(const string& t_name) {
    name = t_name;
};

// ID
int Person::addInvoice(string inv){
    this->idInvoice.push_back(inv);
    return 1;
}
cvector<string> Person::getInvoice(){
    return this->idInvoice;
}

string Person::getID() {
    return ID;
}
// phone
string Person::getPhone() {
    return phone;
}
void Person::setPhone(const string& t_phone) {
    phone = t_phone;
};
// email
string Person::getEmail() {
    return email;
}
void Person::setEmail(const string& t_email) {
    email = t_email;
};
// pass
// ham hien thi dau * cho pass
string Person::hidenPass() {
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
string Person::getRole() {
    return role;
}
string Person::getPass() {
    return pass;
}

void Person::setPass(const string& _pass) {
    this->pass = _pass;
}




void Person::printInfor(const Person* a) {
    cout << left << setw(10) << "ID:" << setw(10) << a->ID << endl
        << left << setw(10) << "FullName:" << setw(20) << a->name << endl
        << left << setw(10) << "Email:" << setw(30) << a->email << endl
        << left << setw(10) << "Phone:" << setw(15) << a->phone << endl
        << "----------------------------------------" << endl;
}
void Person::printAllInvoice(const Person* Person){
    for(string inv: Person->idInvoice){
        Invoice *i = Invoice::getInvoiceByID(inv);
        if(i!=nullptr){
           i->getInfor(i);
        }
        // cout<<inv<<endl;
    }
   

}


int Person::login(string phone, string pw, cvector<Person*> &obj, Person* &p) {
    for (Person* Person : obj) {
        if ((Person->getPhone()) == phone) {
           
            if (( pw == Person->Person::getPass()) ) {
               p = Person;
                return 1;
            }
            else return 0;
        }
    }
    return 0;
}

void Person::printTableHeader() {
    cout << left << setw(10) << "ID"
        << setw(20) << "Full Name"
        << setw(30) << "Email"
        << setw(15) << "Phone"
        << endl;
    cout << "-----------------------------------------------------------------------" << endl;
}
int Person::getDelete(){
    return this->isDelete;
}
void Person::setDelete(int del){
    this->isDelete = del;
}

