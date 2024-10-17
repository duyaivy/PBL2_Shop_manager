#include "Employee.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Employee::Employee(const string& name, const string& phone, const string& email, const string& role, const string& password)
    : person(name, phone, email, password), role(role) {}

void Employee::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(20) << getPhone()
        << setw(15) << role << endl;
}

void Employee::updateInfo() {
    setPhone();
    setEmail();
    cout << "Enter new role: ";
    getline(cin, role);
}

void Employee::saveToFile(const vector<Employee*>& employees) {
    ofstream file("employees.csv");
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (Employee* emp : employees) {
        file << emp->getID() << "," << emp->getName() << "," << emp->getPhone() << "," << emp->getEmail() << "," << emp->getRole() << endl;
    }
    file.close();
}

void Employee::loadFromFile(vector<Employee*>& employees) {
    ifstream file("employees.csv");
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, phone, email, role;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, role);

        employees.push_back(new Employee(name, phone, email, role, ""));
    }
    file.close();
}

string Employee::getRole() const {
    return role;
}
