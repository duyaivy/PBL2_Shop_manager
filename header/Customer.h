#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "person.h"
#include "Product.h"

using namespace std;

class Customer : public Person {
protected:
    string generateID() override;
    string address;
    vector<string> idCart;
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
    void addToCart(Product *product, int quantity);
    void customerProduct(Product *product);
    int getInforCart();
    void viewProducts();
    void viewAllProducts();
    void searchByIdProduct();
    void SortByBrand();
    void createInvoice();
    void processCashPayment();
    void processBankTransferPayment();
    void proceedToPayment();
    void searchProductByName();
    static int searchCustomerById();
    static int searchCustomerByName();
};

#endif