#ifndef INVOICEDETAIL_H
#define INVOICEDETAIL_H
#include<iostream>
#include <string>
#include"vector.h"
using namespace std;

class product;

class InvoiceDetail
{
protected:
string detailID, invoiceID, prdID;
int quantity;
long long price;
static int nextDetailID;
string generateDetailID(); 
public:
    InvoiceDetail(const string invoiceID ="unknown", const int quantity= 0,const string prdID="unknown");
    static void getInfor(const InvoiceDetail *detail);
    void setQuantity(int number); 
    static InvoiceDetail* getDetailByID(const string id ); 
    void deleteDetail();
    static void displayDetail(); 
    static int saveToFile(string fileName);
    static int loadFromFile(string fileName);
    string getDetailID();
    string getInvoiceID();
    string getPrdID();
    int getQuantity();
    long long getPrice();
    long long getImportPrice();
    static cvector<InvoiceDetail*> detail;
};

#endif

// them, sua, xoa 1 detail, ham dung detail id, search by id, 
// in ra 1 detail getinfor, in ra file, tai tu file