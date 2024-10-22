#ifndef EMPLOYEE_H 
#define EMPLOYEE_H

#include "person.h"
#include "Customer.h"
#include <vector>
#include <string>
using namespace std;

class Employee : public person {
protected:
    string role;
public:
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password);

    void display() override;
    void updateInfo();
    static void saveToFile(const vector<person*>& persons, const string& filename); 
    static void loadFromFile(const string& filename, vector<person*>& persons); 
    string getRole() const;

    void manageCustomers(vector<person*>& persons);
    void manageEmployees(vector<person*>& persons);
    static std::string getUserRole();
    static void handleManagerMenu(Employee& manager, vector<person*>& persons); 
    static void displaySalesCustomers(const vector<person*>& persons); 
    static void handleUserRole(string role, vector<person*>& persons); 
    void setInfor(person& a) override;

private:
    void searchCustomerByID(const vector<person*>& persons);
    void addCustomer(vector<person*>& persons);
    void deleteCustomer(vector<person*>& persons);
    void editCustomer(vector<person*>& persons);
    void addEmployee(vector<person*>& persons);
    void updateEmployee(vector<person*>& persons);
    void deleteEmployee(vector<person*>& persons);
    void editEmployee(vector<person*>& persons);
    void addCustomersFromFile(const string& fileName, vector<person*>& persons);
};

#endif
