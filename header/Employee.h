#ifndef EMPLOYEE_H 
#define EMPLOYEE_H
#include"person.h"

class Employee : public Person {
protected:
    string dayToWork;
    string generateID() override;
    static int nextEmpID;
public:
    Employee(const string& name, const string& phone, const string& email, const string& password, const string& role = "SALES",const bool & _isDelete = false, const string &dayToWork="");
    void display() override;
    void updateInfo();
    int deleteEmployee();
    int setDayToWork(string day);
    string getDayToWork();
    long long calcRevenue();
    static Employee*getMaxRevenue();
    static void saveToFile( const string& filename); 
    static int loadFromFile(const string& filename) ; 
    void manageCustomers();
    void manageEmployees();
    void manageProduct();
    static void handleManagerMenu(Employee& manager); 
    static void handleEmployeeMenu(Employee& sale);
    static void displayCustomers(); 
    void setInfor() override;
    static Employee*getEmpById(const string id);
    static int searchEmployeeByID();
    static int searchEmployeeByName();
    int regisEmployee();
    int deleteEmployee(string empID);
    int deleteCustomer(string cusID);
    static void printTableHeader();
    static void handleOneCus();
    static void handleOneEmp();
    static void handleOnePrd();
    void handleThisEmployee();
    void viewAllInfor();

};
#endif

