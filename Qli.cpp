#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
#include <iostream>
#include <vector>
#include <iomanip>  // Thư viện cho setw

using namespace std;

// Hàm lấy vai trò người dùng
string getUserRole() {
    string role;
    while (true) {
        cout << "Enter your role (MANAGER/SALES): ";
        cin >> role;
        cin.ignore();  

        // Kiểm tra nếu vai trò hợp lệ
        if (role == "MANAGER" || role == "SALES") {
            break;  
        }
        else {
            cout << "Invalid. Please select again.\n";
        }
    }
    return role;
}

// Hàm hiển thị và xử lý menu cho Manager
void handleManagerMenu(Manager& manager, vector<Customer*>& customers, vector<Employee*>& employees) {
    while (true) {
        int choice;
        cout << "1. Manager customer\n";
        cout << "2. Manager employee\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();  // Xóa bộ đệm

        switch (choice) {
        case 1:
            manager.manageCustomer(customers);
            break;
        case 2:
            manager.manageEmployee(employees);
            break;
        case 3:
            cout << "Exiting...\n";
            // Giải phóng bộ nhớ trước khi thoát
            for (Customer* cust : customers) {
                delete cust;
            }
            customers.clear();

            for (Employee* emp : employees) {
                delete emp;
            }
            employees.clear();

            return;  // Thoát khỏi hàm
        default:
            cout << "Invalid. Please select again.\n";
        }
    }
}

// Hàm hiển thị thông tin khách hàng cho Sales
void displaySalesCustomers(const vector<Customer*>& customers) {
    for (Customer* cust : customers) {
        cust->display();  // Hiển thị thông tin khách hàng
    }
}

int main() {
    // sudung chung 1 vector của person để trỏ đến từng customer và employee
    vector<Customer*> customers;
    vector<Employee*> employees;

    // Tải dữ liệu từ file CSV
    Customer::loadFromFile(customers);
    Employee::loadFromFile(employees);

    // Lấy vai trò người dùng
    string role = getUserRole();

    // Xử lý theo vai trò
    if (role == "MANAGER") {
        Manager manager("Admin", "123456789", "admin@example.com", "admin123");
        handleManagerMenu(manager, customers, employees);
    }
    else if (role == "SALES") {
        person::printTableHeader();
        displaySalesCustomers(customers);
    }

    // Giải phóng bộ nhớ và thoát
    for (Customer* cust : customers) {
        delete cust;
    }
    customers.clear();

    for (Employee* emp : employees) {
        delete emp;
    }
    employees.clear();

    return 0;
}
