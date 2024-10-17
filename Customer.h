#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include <vector>
#include <string>
using namespace std;

class Customer : public person {
public:
    Customer(const string& name, const string& phone, const string& email, const string& password);

    void updateInfo();
    static void saveToFile(const vector<Customer*>& customers);
    static void loadFromFile(vector<Customer*>& customers);
    void display();
};

#endif
