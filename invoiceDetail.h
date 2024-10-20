#ifndef INVOICEDETAIL_H
#define INVOICEDETAIL_H
#include<iostream>
#include <string>
#include<vector>
using namespace std;

class product;

class invoiceDetail
{
protected:
string detailID, invoiceID, prdID;
int quantity;
long long price;
static int nextDetailID;
string generateDetailID(); 

public:
    invoiceDetail(const string invoiceID ="unknown", const int quantity= 0,const string prdID="unknown");
    static void getInfor(const invoiceDetail *detail);
    void setQuantity(int number); 
    static invoiceDetail* getDetailByID(const string id = "" ); 
    int deleteDetail();
    static void displayDetail(); 
    static int saveToFile(string fileName);
    static int loadFromFile(string fileName);
    string getDetailID();
    string getInvoiceID();
    string getPrdID();
    int getQuantity();
    long long getPrice();

};
static vector<invoiceDetail*> detail;

#endif

// them, sua, xoa 1 detail, ham dung detail id, search by id, 
// in ra 1 detail getinfor, in ra file, tai tu file