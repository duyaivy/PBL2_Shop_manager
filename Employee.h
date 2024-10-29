#ifndef EMPLOYEE_H 
#define EMPLOYEE_H
#include"person.h"

class Employee : public person {
protected:
    string generateID() override;
    static int nextEmpID;
public:
    Employee(const string& name, const string& phone, const string& email, const string& password, const string& role = "SALES");
    void display() override;
    void updateInfo();
    int deleteEmployee();
    void saveToFile( const string& filename); 
    int loadFromFile(const string& filename) ; 
    void manageCustomers();
    void manageEmployees();
    void manageProduct();
    static void handleManagerMenu(Employee& manager); 
    static void handleEmployeeMenu(Employee& sale);
    static void displayCustomers(); 
    void setInfor() override;
    static Employee*getEmpById(const string id);
    int searchEmployeeByID();
};
#endif
