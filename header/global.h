#ifndef GLOBAL_H
#define GLOBAL_H
#include<string>
#include "Employee.h"
#include "Product.h"
#include "Person.h"
#include "Customer.h"
#include"InvoiceDetail.h"
#include"Invoice.h"
int setUpDataBase();
int saveDataBase();

using namespace std;
string toLowerCase(const string& str);
string formatCurrency(long long number);

#endif