#include "person.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>  // Thư viện để sử dụng regex
#include "person.h"
#include <conio.h> 
using namespace std;

class Customer : public person {
public:
    Customer(const string& name, const string& phone, const string& email, const string& password)
        : person(name, phone, email, password) {}

    void updateInfo() {
        setPhone();
        setEmail();
    }

    static void saveToFile(const vector<Customer*>& customers) {
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

    static void loadFromFile(vector<Customer*>& customers) {
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

    void display() {
        cout << setw(10) << getID()
             << setw(20) << getName()
             << setw(30) << getEmail()
             << setw(20) << getPhone() << endl;
    }
};

class Employee : public person {
protected:
    string role;
public:
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password)
        : person(name, phone, email, password), role(role) {}

    void display()  {
        cout << setw(10) << getID()
             << setw(20) << getName()
             << setw(30) << getEmail()
             << setw(20) << getPhone()
             << setw(15) << role << endl;
    }

    void updateInfo() {
        setPhone();
        setEmail();
        cout << "Enter new role: ";
        getline(cin, role);
    }

    static void saveToFile(const vector<Employee*>& employees) {
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

    static void loadFromFile(vector<Employee*>& employees) {
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

    string getRole() const { return role; }
};


class Manager : public Employee {
public:
    Manager(const string& name, const string& phone, const string& email, const string& password)
        : Employee(name, phone, email, "MANAGER", password) {}

    void manageCustomer(vector<Customer*>& customers) {
        int option;
        cout << "1. View customers\n2. Search customer\n3. Add new customer\n4. Delete customer\n5. Edit customer\nChoose: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                person::printTableHeader();
                for (Customer* cust : customers) {
                    cust->display();
                }
                break;
            case 2:
                searchCustomerByID(customers);
                break;
            case 3:
                addCustomer(customers);
                break;
            case 4:
                deleteCustomer(customers);
                break;
            case 5:
                editCustomer(customers);
                break;
            default:
                cout << "Invalid option\n";
        }
    }

    void manageEmployee(vector<Employee*>& employees) {
        int option;
        cout << "1. View employees\n2. Add new employee\n3. Update employee info\n4. Delete employee\n5. Edit employee\nChoose: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                person::printTableHeader();
                for (Employee* emp : employees) {
                    emp->display();
                }
                break;
            case 2:
                addEmployee(employees);
                break;
            case 3:
                updateEmployee(employees);
                break;
            case 4:
                deleteEmployee(employees);
                break;
            case 5:
                editEmployee(employees);
                break;
            default:
                cout << "Invalid option\n";
        }
    }

private:
    void searchCustomerByID(const vector<Customer*>& customers) {
        string searchID;
        cout << "Enter customer ID to search: ";
        cin >> searchID;
        cin.ignore();
        bool found = false;
        for (Customer* cust : customers) {
            if (cust->getID() == searchID) {
                cust->display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Customer with this ID not found.\n";
        }
    }

    void addCustomer(vector<Customer*>& customers) {
        int num;
        cout << "Enter number of new customers: ";
        cin >> num;
        cin.ignore(); // Clear input buffer

        for (int i = 0; i < num; ++i) {
            string name, phone, email, password, confirmPass;

            cout << "Enter details for customer " << (i + 1) << ":" << endl;

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter phone: ";
            getline(cin, phone);

            cout << "Enter email: ";
            getline(cin, email);

            // Nhập và xác nhận mật khẩu
            do {
                cout << "Enter password: ";
                password = hidenPass();

                cout << "Confirm password: ";
                confirmPass = hidenPass();

                if (password != confirmPass) {
                    cout << "Passwords do not match. Please try again." << endl;
                }
            } while (password != confirmPass);

            // Thêm khách hàng vào danh sách
            customers.push_back(new Customer(name, phone, email, password));
            cout << "Customer " << (i + 1) << " added successfully!" << endl;
        }

        // Lưu khách hàng vào file sau khi thêm mới
        Customer::saveToFile(customers);
    }

    void deleteCustomer(vector<Customer*>& customers) {
    string id;
    cout << "Enter customer ID to delete: ";
    cin >> id;
    cin.ignore();

    int initialSize = customers.size();  // Lưu kích thước ban đầu
    auto it = remove_if(customers.begin(), customers.end(), [&](Customer* cust) {
        if (cust->getID() == id) {
            delete cust;
            return true;
        }
        return false;
    });
    customers.erase(it, customers.end());
    Customer::saveToFile(customers);

    // Hiển thị số lượng khách hàng bị xóa
    int deletedCount = initialSize - customers.size();
    if (deletedCount > 0) {
        cout << deletedCount << " customer(s) deleted successfully!" << endl;
    } else {
        cout << "No customer found with this ID.\n";
    }
}

// Thêm vào phần chỉnh sửa khách hàng trong hàm editCustomer
void editCustomer(vector<Customer*>& customers) {
    string id;
    cout << "Enter customer ID to edit: ";
    cin >> id;
    cin.ignore();

    auto it = find_if(customers.begin(), customers.end(), [&](Customer* cust) {
        return cust->getID() == id;
    });

    if (it != customers.end()) {
        Customer* cust = *it;
        cout << "Editing customer with ID: " << id << endl;
        cust->updateInfo();
        Customer::saveToFile(customers);
        cout << "1 customer edited successfully!" << endl;
    } else {
        cout << "Customer with this ID not found.\n";
    }
}

    void addEmployee(vector<Employee*>& employees) {
        int num;
        cout << "Enter number of new employees: ";
        cin >> num;
        cin.ignore(); // Clear input buffer

        for (int i = 0; i < num; ++i) {
            string name, phone, email, role, password;

            cout << "Enter details for employee " << (i + 1) << ":" << endl;

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter phone: ";
            getline(cin, phone);

            cout << "Enter email: ";
            getline(cin, email);

            cout << "Enter role: ";
            getline(cin, role);

            cout << "Enter password: ";
            password = hidenPass();

            employees.push_back(new Employee(name, phone, email, role, password));
            cout << "Employee " << (i + 1) << " added successfully!" << endl;
        }

        Employee::saveToFile(employees);
    }

    void updateEmployee(vector<Employee*>& employees) {
        string id;
        cout << "Enter employee ID to update: ";
        cin >> id;
        cin.ignore();

        auto it = find_if(employees.begin(), employees.end(), [&](Employee* emp) {
            return emp->getID() == id;
        });

        if (it != employees.end()) {
            Employee* emp = *it;
            cout << "Updating employee with ID: " << id << endl;
            emp->updateInfo();
            Employee::saveToFile(employees);
        } else {
            cout << "Employee with this ID not found.\n";
        }
    }

    void deleteEmployee(vector<Employee*>& employees) {
        string id;
        cout << "Enter employee ID to delete: ";
        cin >> id;
        cin.ignore();
        auto it = remove_if(employees.begin(), employees.end(), [&](Employee* emp) {
            if (emp->getID() == id) {
                delete emp;
                return true;
            }
            return false;
        });
        employees.erase(it, employees.end());
        Employee::saveToFile(employees);
    }

    void editEmployee(vector<Employee*>& employees) {
        string id;
        cout << "Enter employee ID to edit: ";
        cin >> id;
        cin.ignore();

        auto it = find_if(employees.begin(), employees.end(), [&](Employee* emp) {
            return emp->getID() == id;
        });

        if (it != employees.end()) {
            Employee* emp = *it;
            cout << "Editing employee with ID: " << id << endl;
            emp->updateInfo();
            Employee::saveToFile(employees);
        } else {
            cout << "Employee with this ID not found.\n";
        }
    }
};

string getUserRole() {
    string role;
    while (true) {
        cout << "Enter your role(MANAGER/SALES): ";
        cin >> role;
        cin.ignore();  // Xóa bộ đệm sau khi nhập

        // Kiểm tra nếu vai trò hợp lệ
        if (role == "MANAGER" || role == "SALES") {
            break;  // Vai trò hợp lệ, thoát khỏi vòng lặp
        } else {
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

// Hàm chính
int main() {
    vector<Customer*> customers;
    vector<Employee*> employees;

    // Tải dữ liệu từ file CSV
    Customer::loadFromFile(customers);
    Employee::loadFromFile(employees);

    // Lấy vai trò người dùng
    string role = getUserRole();

    // Xử lý theo vai trò
    if (role == "MANAGER") {
        Manager manager("Manager", "0123456789", "manager@example.com", "managerpass");
        handleManagerMenu(manager, customers, employees);
    } else if (role == "SALES") {
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
