#ifndef INVOICE_H
#define INVOICE_H
#include<iostream>
#include <string>
#include "vector.h"
using namespace std;

class InvoiceDetail;

class Invoice
{
protected:
string InvoiceID, staffID, customerID, time;
long long totalPrice;
static int nextInvoiceID;
cvector<string> detailID;
string generateInvoiceID(); 

public:
    Invoice(const string staffID ="unknown", const string customerID ="unknown", const string time= "01/01/2024", const string detailID="unknown");
    static void getInfor(const Invoice *);
    int addDetailID(string detailID);
    long long calcTotalPrice();
    void setQuantityInvoice(string detailID, int number); 
    static Invoice* getInvoiceByID(const string id); 
    void deleteInvoice();
    static void display(); 
    static int saveToFile(string fileName);
    static int loadFromFile(string fileName);
    string getInvoiceID();
    string getStaffID();
    string getCustomerID();
    string getTime();
    cvector<string> getDetailID();
    long long getTotalPrice();
    static cvector<Invoice*> inv;

};

#endif
// them sua xoa 1 hoa don, them, xoa 1 chi tiet hoa don, thay doi so luong trong 1 chi tiet hoa don
// lay ra 1 hoa don,