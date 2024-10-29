#ifndef PRODUCT_H
#define PRODUCT_H
#include<iostream>
#include <string>
using namespace std;
// get infor 1; create 1 prd; set(update) 1 prd, search by ID, search by name, 
// search by brand; show all; delete 1 prd ; input from csv; thay doi so luong 
// 
class product
{
protected:
string productID, prdName,prdBrand,prdDetail;
long long unitPrice;
int quantity;
static int nextPrdID;
string generatePrdID(); 

public:
    product(const string name ="unknown",const string brand ="unknown",const string detail="unknown",const long long unitPrice = 0, const int quantity= 0);
    static void getInfor(const product *p);
    void printInfor();
    static void setInfor(product&p); 
    void setQuantity( const int count);
    int searchByID(string id = "" ); 
    int static searchByBrand(string brand = ""); 
    int static searchByName(string name  = "");
    int deletePrd();
    static void displayPrd(); 
    void setUnitPrice(const long long price);
    static int saveToFile(string fileName);
    static int loadFromFile(string fileName);
    static product* getPrdByID(const string id= "");
    string getPrdID();
    string getPrdName();
    string getPrdBranch();
    string getPrdDetail();
    long long getUnitPrice();
    int getQuantity();
};
static vector<product*> prd;

#endif
