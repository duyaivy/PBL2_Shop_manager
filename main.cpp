#include "person.h"
#include <iostream>
int person::nextID = 1;  // tao ID dau tien là 1
std::vector<person*> person::obj;

int main() {
    person person1("John Doe", "123456789", "john@example.com", "password123");
    person person2("Jane Smith", "987654321", "jane@example.com", "password456");

    
   // tao 1 nguoi moi va nhap thong tin
    person a;
    person::setInfor(a);
    a.setPass();
    person1.display();
    // delete vector nguoi
    person::clearPerson();
    person::display();
    
    cout<<"may nhin cai cho gi"<<endl;
    


    return 0;
}
