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
    Customer(const string& _name, const string& _phone, const string& _email, const string& _password,const bool & _isDelete,const string& _address);
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
    void viewAllInfor();
    int handleThisCustomer();
    int addCaft(string cart);
    int getInforCart();
    static int searchCustomerById();
    static int searchCustomerByName();
};

#endif