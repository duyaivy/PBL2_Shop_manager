#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include "Customer.h"
#include <vector>

class Manager : public Employee {
public:
    Manager(const string& name, const string& phone, const string& email, const string& password);
    void manageCustomer(vector<Customer*>& customers);
    void manageEmployee(vector<Employee*>& employees);


private:
    void searchCustomerByID(const vector<Customer*>& customers);
    void addCustomer(vector<Customer*>& customers);
    void deleteCustomer(vector<Customer*>& customers);
    void editCustomer(vector<Customer*>& customers);
    void addEmployee(vector<Employee*>& employees);
    void updateEmployee(vector<Employee*>& employees);
    void deleteEmployee(vector<Employee*>& employees);
    void editEmployee(vector<Employee*>& employees);
};

#endif // MANAGER_H
