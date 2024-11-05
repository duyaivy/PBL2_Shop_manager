#include "Employee.h"
#include "product.h"
#include "person.h"
#include "Customer.h"
#include <iostream>
#include "vector.h"  
#include <string>

using namespace std;

int product::nextPrdID = 1; 
int Employee::nextEmpID = 1;
int Customer::nextCusID = 1;

int main() {
    // Nạp dữ liệu từ các file CSV
    if (Employee::loadFromFile("employees.csv") == 0) {
        cerr << "Failed to load employee data.\n";
    }
    if (Customer::loadFromFile("customers.csv") == 0) {
        cerr << "Failed to load customer data.\n";
    }
    if (product::loadFromFile("product.csv") == 0) {
        cerr << "Failed to load product data.\n";
    }

    string id, password;

    while (true) {
        cout << "Enter your ID: ";
        cin >> id;
        cin.ignore();
        
    
;
        // Kiểm tra nếu người dùng muốn thoát
        if (id == "0") {
            cout << "Exiting...\n";
            return 0; // Thoát chương trình
        }

        Employee* emp = Employee::getEmpById(id);
        if (!emp) {
            cout << "Invalid ID. Please try again or enter '0' to exit.\n";
            continue; // Yêu cầu nhập lại ID
        }

        cout << "Enter your password: ";
        cin >> password;
        cin.ignore();
       
       

        // Kiểm tra mật khẩu
        if (emp->getPass() == password) {
            // Đăng nhập thành công
            if (emp->getRole() == "MANAGER") {
                Employee::handleManagerMenu(*emp);
            } else if (emp->getRole() == "SALES") {
                Employee::handleEmployeeMenu(*emp);
            }
            break; // Thoát khỏi vòng lặp khi đăng nhập thành công
        } else {
            cout << "Invalid password. Please try again or enter '0' to exit.\n";
        }
    }

    // Sau khi thực hiện các tác vụ, lưu dữ liệu lại vào các file CSV
    Employee::saveToFile("employees.csv");
    Customer::saveToFile("customers.csv");
    product::saveToFile("products.csv");

    // Giải phóng bộ nhớ cho các đối tượng trong obj và prd
    for (auto p : obj) {
        delete p;
    }
    for (auto p : prd) {
        delete p;
    }

    return 0;
}