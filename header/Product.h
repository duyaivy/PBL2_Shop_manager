#ifndef PRODUCT_H
#define PRODUCT_H
#include<iostream>
#include <string>
#include "Vector.h"

using namespace std;
// get infor 1; create 1 prd; set(update) 1 prd, search by ID, search by name, 
// search by brand; show all; delete 1 prd ; input from csv; thay doi so luong 
// 
class Product
{
protected:
string productID, prdName,prdBrand,prdDetail;
long long unitPrice,importPrice;
int quantity, qntSell;
bool isDelete;
static int nextPrdID;

string generatePrdID(); 

public:
    Product(const string name ="unknown",const string brand ="unknown",const string detail="unknown",const long long unitPrice = 0,const long long importPrice = 0, const int quantity= 0, const int qntSell= 0, const bool isDelete= false);
    static void getInfor(const Product *p);
    static void getInforToManager(const Product *p);
    void printInfor();
    static void setInfor(Product *p); 
    void setQuantity( const int count);
    int searchByID(string id); 
    int static searchByBrand(string brand); 
    int static searchByName(string name);
    bool deletePrd();
    static void displayAllPrd(); 
    static void displayAllPrdToManager(); 
    void setUnitPrice(const long long price);
    static int saveToFile(string fileName);
    static int loadFromFile(string fileName);
    static Product* getPrdByID(const string id );
    string getPrdID();
    string getPrdName();
    string getPrdBranch();
    string getPrdDetail();
    long long getUnitPrice();
    int getQuantity();
    void setImportPrice(long long price);
    void setQuantitySell(int qnt);
    void setDelete(bool del);
    long long getImportPrice();
    int getQuantitySell();
    bool getDelete();
    void handleThisProduct();

    static vector<Product*> prd;

};
#endif