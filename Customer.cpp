#include "Customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Customer::Customer(const string& name, const string& phone, const string& email, const string& password)
    : person(name, phone, email, password) {}
// sua lai 2 cáse update hết toàn bộ thông tin hoặc update 1 phần thông tin. 
void Customer::updateInfo() {
    setPhone();
    setEmail();
}

void Customer::saveToFile(const vector<Customer*>& customers) {
    ofstream file("customers.csv");
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (Customer* cust : customers) {
        file << cust->getID() << "," << cust->getName() << "," << cust->getPhone() << "," << cust->getEmail() << "," << cust->getPass() << endl;
    }
    file.close();
}

void Customer::loadFromFile(vector<Customer*>& customers) {
    ifstream file("customers.csv");
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, phone, email, password;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password);

        customers.push_back(new Customer(name, phone, email, password));
    }
    file.close();
}

void Customer::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(20) << getPhone() << endl;
}
