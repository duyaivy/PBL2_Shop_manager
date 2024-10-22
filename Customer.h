#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "person.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Customer : public person {
public:
    Customer(const string& name, const string& phone, const string& email, const string& password);

    void updateInfo();
    static void saveToFile(const vector<person*>& persons, const string& filename);
    static void loadFromFile(const string& fileName, vector<person*>& persons); // Thay đổi vector thành vector<person*>);
    void display();
    void setInfor(person& a) override;
};

#endif
