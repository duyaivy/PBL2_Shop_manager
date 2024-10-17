#include "Manager.h"
#include "Customer.h"
#include <algorithm>

using namespace std;

Manager::Manager(const string& name, const string& phone, const string& email, const string& password)
    : Employee(name, phone, email, "MANAGER", password) {}

void Manager::manageCustomer(vector<Customer*>& customers) {
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

void Manager::manageEmployee(vector<Employee*>& employees) {
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

void Manager::searchCustomerByID(const vector<Customer*>& customers) {
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

void Manager::addCustomer(vector<Customer*>& customers) {
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
        cout << "Customer " << name << " added successfully.\n";
    }
}

void Manager::deleteCustomer(vector<Customer*>& customers) {
    string id;
    cout << "Enter customer ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(customers.begin(), customers.end(), [&](Customer* cust) {
        return cust->getID() == id;
        });

    if (it != customers.end()) {
        delete* it;
        customers.erase(it, customers.end());
        cout << "Customer deleted successfully.\n";
    }
    else {
        cout << "Customer not found.\n";
    }
}

void Manager::editCustomer(vector<Customer*>& customers) {
    string id;
    cout << "Enter customer ID to edit: ";
    cin >> id;
    cin.ignore();

    for (Customer* cust : customers) {
        if (cust->getID() == id) {
            cust->updateInfo();
            cout << "Customer info updated successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void Manager::addEmployee(vector<Employee*>& employees) {
    string name, phone, email, role, password;

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
    cout << "Employee " << name << " added successfully.\n";
}

void Manager::updateEmployee(vector<Employee*>& employees) {
    string id;
    cout << "Enter employee ID to update: ";
    cin >> id;
    cin.ignore();

    for (Employee* emp : employees) {
        if (emp->getID() == id) {
            emp->updateInfo();
            cout << "Employee info updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

void Manager::deleteEmployee(vector<Employee*>& employees) {
    string id;
    cout << "Enter employee ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(employees.begin(), employees.end(), [&](Employee* emp) {
        return emp->getID() == id;
        });

    if (it != employees.end()) {
        delete* it;
        employees.erase(it, employees.end());
        cout << "Employee deleted successfully.\n";
    }
    else {
        cout << "Employee not found.\n";
    }
}

void Manager::editEmployee(vector<Employee*>& employees) {
    string id;
    cout << "Enter employee ID to edit: ";
    cin >> id;
    cin.ignore();

    for (Employee* emp : employees) {
        if (emp->getID() == id) {
            emp->updateInfo();
            cout << "Employee info updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}
