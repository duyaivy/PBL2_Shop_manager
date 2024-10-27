#include<iostream>
#include"invoiceDetail.h"
#include"product.h"
#include"invoice.h"
using namespace std;
int product::nextPrdID = 1;
int invoiceDetail::nextDetailID = 1;
int invoice::nextInvoiceID = 1;

int main(){
  product* p1 = new product("Laptop A", "Brand A", "Detail A", 1000, 10);
  product* p2 = new product("Laptop c", "Brand A", "Detail B", 1500, 5);
  product* p3 = new product("Gaming Laptop", "Brand A", "Detail B", 2500, 5);

invoiceDetail::loadFromFile(".\\csv\\detail.csv");
invoice::loadFromFile(".\\csv\\invoice.csv");
// invoice::getInvoiceByID("IN00002")->setQuantityInvoice("DE00002", 12);
invoice::getInvoiceByID("IN00001")->setQuantityInvoice("DE00001", 500);
// invoice::getInvoiceByID("IN00001")->deleteInvoice();
// cout<<invoice::getInvoiceByID("IN00001")->getTotalPrice();


invoice::display();

// OK invoiceDetail::getDetailByID("DE00003")->setQuantity(10);

invoiceDetail::saveToFile(".\\csv\\detail.csv");
invoice::saveToFile(".\\csv\\invoice.csv");

return 0;
}