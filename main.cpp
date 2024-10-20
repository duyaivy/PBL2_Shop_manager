#include "person.h"
#include <iostream>
int person::nextID = 1;  // tao ID dau tien là 1


int main() {
    person person1("John Doe", "123456789", "john@example.com", "password123","admin");
    person person2("Jane Smith", "987654321", "jane@example.com", "password456","customer");
    person p1;

    person::display();
    int login = person::login("0000001","password123", &p1);
    if(login){
       if(p1.getRole() == "admin") cout<< "admin";
       else cout<< "cus";
    }else{
        cout<<"no";
    }
    return 0;
}
