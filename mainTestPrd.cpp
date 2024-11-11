#include<iostream>
#include"./header/InvoiceDetail.h"
#include"./header/Product.h"
#include"./header/Invoice.h"
#include"./header/Employee.h"
#include"./header/Customer.h"
using namespace std;
int Product::nextPrdID = 1;
int InvoiceDetail::nextDetailID = 1;
int Invoice::nextInvoiceID = 1;
int Employee::nextEmpID = 1;
int Customer::nextCusID = 1;

int main(){
  Product::loadFromFile(".\\csv\\products.csv");
  InvoiceDetail::loadFromFile(".\\csv\\detail.csv");
  Invoice::loadFromFile(".\\csv\\invoice.csv");
  Employee::loadFromFile(".\\csv\\employees.csv");
  Customer::loadFromFile(".\\csv\\customers.csv");
  // Product *pro = Product::prd[0];
  // pro->displayAllPrdToManager();
  // Employee *emp = dynamic_cast<Employee*>(Person::obj[0]);
  // cout<<emp->calcRevenue(); //OK
  // Employee *e = Employee::getMaxRevenue();
  // e->printInfor(e);
cout<<"cc";
// Invoice::display();
Product::saveToFile("products.csv");
InvoiceDetail::saveToFile(".\\csv\\detail.csv");
Invoice::saveToFile(".\\csv\\Invoice.csv");
Employee::saveToFile(".\\csv\\employees.csv");
Customer::saveToFile(".\\csv\\customers.csv");


return 0;
}
//g++ mainTestPrd.cpp Product.cpp InvoiceDetail.cpp Invoice.cpp -o m
//g++ mainTestPrd.cpp Product.cpp InvoiceDetail.cpp Invoice.cpp Employee.cpp Person.cpp Customer.cpp -o m