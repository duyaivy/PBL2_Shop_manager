#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "person.h"

using namespace std;

class Customer : public person {
protected:
    string generateID() override;
    string address;
    static int nextCusID;
public:
    Customer(const string& name, const string& phone, const string& email, const string& password,const string& _address);
    void updateInfo();
    string getAddress(); 
    void setAddress(const string&);
    
    static void saveToFile(const string& filename);
    static int loadFromFile(const string& fileName) ; 
    void display() override;
    void setInfor() override;
    static Customer*getCusById(const string&);
    int deleteCustomer();
};

#endif