#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "person.h"
#include <vector>
#include <string>
using namespace std;

class Employee : public person {
protected:
    string role;
public:
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password);

    void display();
    void updateInfo();
    static void saveToFile(const vector<Employee*>& employees);
    static void loadFromFile(vector<Employee*>& employees);
    string getRole() const;
};

#endif
