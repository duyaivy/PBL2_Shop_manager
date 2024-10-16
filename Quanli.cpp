#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <regex>  // Thư viện để sử dụng regex
#include "person.h"
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
        for (const Customer* cust : customers) {
            file << cust->getID() << "," << cust->getName() << "," << cust->getPhone() << "," << cust->getEmail() << "," << cust->getPass() << endl;
        }
        file.close();
    }

    static void loadFromFile(vector<Customer*>& customers) {
        ifstream file("customers.csv");
        string id, name, phone, email, password;
        while (getline(file, id, ',') && getline(file, name, ',') && getline(file, phone, ',') && getline(file, email, ',') && getline(file, password)) {
            customers.push_back(new Customer(name, phone, email, password));
        }
        file.close();
    }
};

class Employee : public person {
protected:
    string role;
public:
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password)
        : person(name, phone, email, password), role(role) {}

    void display() const override {
        person::display();
        cout << "Role: " << role << endl;
    }

    string getRole() const { return role; }

    void updateInfo() {
        setPhone();
        setEmail();
        cout << "Enter new role: ";
        getline(cin, role);
    }

    static void saveToFile(const vector<Employee*>& employees) {
        ofstream file("employees.csv");
        for (const Employee* emp : employees) {
            file << emp->getID() << "," << emp->getName() << "," << emp->getPhone() << "," << emp->getEmail() << "," << emp->getRole() << endl;
        }
        file.close();
    }

    static void loadFromFile(vector<Employee*>& employees) {
        ifstream file("employees.csv");
        string id, name, phone, email, role;
        while (getline(file, id, ',') && getline(file, name, ',') && getline(file, phone, ',') && getline(file, email, ',') && getline(file, role)) {
            employees.push_back(new Employee(name, phone, email, role, ""));
        }
        file.close();
    }
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
        for (const Customer* cust : customers) {
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
            string name, phone, email, password;

            cout << "Enter details for customer " << (i + 1) << ":" << endl;

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter phone: ";
            getline(cin, phone);
            while (!person::isValidPhone(phone)) {
                cout << "Invalid phone number format. Enter again: ";
                getline(cin, phone);
            }

            cout << "Enter email: ";
            getline(cin, email);
            while (!person::isValidEmail(email)) {
                cout << "Invalid email format. Enter again: ";
                getline(cin, email);
            }

            cout << "Enter password: ";
            getline(cin, password);

            customers.push_back(new Customer(name, phone, email, password));
            cout << "Customer " << (i + 1) << " added successfully!" << endl;
        }

        Customer::saveToFile(customers);
    }

    void deleteCustomer(vector<Customer*>& customers) {
        string id;
        cout << "Enter customer ID to delete: ";
        cin >> id;
        cin.ignore();
        auto it = remove_if(customers.begin(), customers.end(), [&](Customer* cust) {
            if (cust->getID() == id) {
                delete cust;
                return true;
            }
            return false;
        });
        customers.erase(it, customers.end());
        Customer::saveToFile(customers);
    }

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
            getline(cin, password);

            employees.push_back(new Employee(name, phone, email, role, password));
        }

        Employee::saveToFile(employees);
    }

    void updateEmployee(vector<Employee*>& employees) {
        string id;
        cout << "Enter employee ID to update: ";
        cin >> id;
        cin.ignore();
        for (Employee* emp : employees) {
            if (emp->getID() == id) {
                emp->updateInfo();
                Employee::saveToFile(employees);
                break;
            }
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

// Hàm chính
int main() {
    vector<Customer*> customers;
    vector<Employee*> employees;

    // Tải dữ liệu từ file
    Customer::loadFromFile(customers);
    Employee::loadFromFile(employees);

    string role;
    cout << "Enter your role (MANAGER/SALES): ";
    cin >> role;
    cin.ignore(); // Clear input buffer

    if (role == "MANAGER") {
        Manager manager("Manager", "0123456789", "manager@gmail.com", "pass123");
        while (true) {
            int choice;
            cout << "1. Manage customers\n2. Manage employees\n3. Exit\nChoose: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                manager.manageCustomer(customers);
            } else if (choice == 2) {
                manager.manageEmployee(employees);
            } else if (choice == 3) {
                break;
            } else {
                cout << "Invalid choice\n";
            }
        }
    } else if (role == "SALES") {
        // Sales employee only views customer information
        cout << "Sales employee viewing customer information.\n";
        for (Customer* cust : customers) {
            cust->display();
        }
    } else {
        cout << "Invalid role.\n";
    }

    // Giải phóng bộ nhớ
    for (Customer* cust : customers) {
        delete cust;
    }
    for (Employee* emp : employees) {
        delete emp;
    }

    return 0;
}
