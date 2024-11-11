#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "person.h"

using namespace std;

class Customer : public Person {
protected:
    string generateID() override;
    string address;
    cvector<string> idCart;
    static int nextCusID;
public:
    Customer(const string& _name, const string& _phone, const string& _email, const string& _password,const string& _address);
    void updateInfo();
    string getAddress(); 
    void setAddress(const string&);
    
    static void saveToFile(const string& filename);
    static int loadFromFile(const string& fileName) ; 
    void display() override;
    void setInfor() override;
    static Customer*getCusById(const string&);
    int deleteCustomer();
    static void printTableHeader() ; 
    int static regis();

    int addCaft(string cart);
    int getInforCart();
    int getInforInvoice();
};

#endif