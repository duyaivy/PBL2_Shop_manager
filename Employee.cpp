#include "Employee.h"
#include "Customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

Employee::Employee(const string& name, const string& phone, const string& email, const string& role, const string& password)
    : person(name, phone, email, password), role(role) {}

void Employee::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(20) << getPhone()
        << setw(15) << role << endl;
}
// tương tự hàm set của person. Ở đây không nên cho update role bởi vì khách hàng là kahcs hàng mà nhân viên là nhân viên.
// mỗi role có những giá trị chứa khác nhau, đổi là sẽ lỗi. bài toán thực tế thì có nhưng nếu có thì họ sẽ tạo một tài khoàn nhân viên mới chứ không thay đổi thế này.

void Employee::updateInfo() {
    setPhone();
    setEmail();
    cout << "Enter new role: ";
    getline(cin, role);
}

void Employee::saveToFile(const vector<person*>& persons, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for ( person* p : persons) {
        Employee* emp = dynamic_cast< Employee*>(p); // Chỉ lưu thông tin nhân viên
        if (emp) {
            file << emp->getID() << "," << emp->getName() << "," << emp->getPhone() << "," << emp->getEmail() << "," << emp->getRole() << endl;
        }
    }

    file.close();
}
// lỗi tương tự cus.h
void Employee::loadFromFile(const string& filename, vector<person*>& persons) {
    ifstream file(filename);
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

        persons.push_back(new Employee(name, phone, email, role, "")); // Thêm vào vector chung
    }
    file.close();
}

string Employee::getRole() const {
    return role;
}

// Các chức năng quản lý khách hàng và nhân viên, chỉ khả dụng nếu role là  "MANAGER"
//sửa lại role "adimin" thêm câu lệnh if(this->role() == "admin"){thì làm trong này}else{cout<<" không được phép...."}
void Employee::manageCustomers(vector<person*>& persons) {\
// rồi đã kiểm tra nếu nó là role "sale chưa? "
    int option;
    cout << "1. View customers\n2. Search customer\n3. Add new customer\n4. Delete customer\n5. Edit customer\nChoose: ";
    cin >> option;
    cin.ignore();

    switch (option) {
    case 1:
        person::printTableHeader();
        for (person* p : persons) {
            Customer* cust = dynamic_cast< Customer*>(p); // Chỉ hiển thị khách hàng
            if (cust) {
                cust->display();
            }
        }
        break;
    case 2:
    
        searchCustomerByID(persons);
        break;
    case 3:
        addCustomer(persons);
        break;
    case 4:
        deleteCustomer(persons);
        break;
    case 5:
        editCustomer(persons);
        break;
    default:
        cout << "Invalid option\n";
    }
    //nên xây dựng while nhập vào 0 nếu muốn thoát chế độ quản lí cus, còn lại cứ nhập vào những số khác thì cứ để làm rồi quay lại bắt chọn tính năng
}
// tương tự phải kiểm tra role
void Employee::manageEmployees(vector<person*>& persons) {
    int option;
    cout << "1. View employees\n2. Add new employee\n3. Update employee info\n4. Delete employee\n5. Edit employee\nChoose: ";
    cin >> option;
    cin.ignore();

    switch (option) {
    case 1:
        person::printTableHeader();
        for (person* p : persons) {
             Employee* emp = dynamic_cast<Employee*>(p); // Chỉ hiển thị nhân viên
            if (emp) {
                emp->display();
            }
        }
        break;
    case 2:
        addEmployee(persons);
        break;
    case 3:
        updateEmployee(persons);
        break;
    case 4:
        deleteEmployee(persons);
        break;
    case 5:
        editEmployee(persons);
        break;
    default:
        cout << "Invalid option\n";
    }
}

// Các hàm phụ trợ để quản lý khách hàng và nhân viên
// thêm các hàm khác để tìm kiếm như tìm kiếm theo tên. Hàm theo tìm theo từ khoá có xuất hiện trong tên t có gửi bên zalo rồi. vào tham khảo
void Employee::searchCustomerByID(const vector<person*>& persons) {
    string searchID;
    cout << "Enter customer ID to search: ";
    cin >> searchID;
    cin.ignore();
    bool found = false;

    for (person* p : persons) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ tìm kiếm trong đối tượng Customer
        if (cust && cust->getID() == searchID) {
            cust->display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer with this ID not found.\n";// không xử lí in ra thông báo ở đây, trả về 0 hoặc 1 để làm việc đó ở ngoài. ở đâyc chỉ tìm kiếm nếu có thì in ra trả về 1, không có thì trả về 0
    }
}


void Employee::addCustomer(vector<person*>& persons) {
    int choice;
    cout << "Choose how to add a customer:\n";
    cout << "1. Add customer manually\n";
    cout << "2. Add customers from file\n";
    cout << "Choose an option: ";
    cin >> choice;
    cin.ignore(); // Clear input buffer

    switch (choice) {
    case 1: {
        // Thêm khách hàng thủ công
        // nên thay đổi tên biến sao cho khác với tên biến trong person.h vì nếu xử lý không kĩ tại hàm getline(ci,name) sẽ lấy giá trị nhập vào để gán nhập vào cho name của đói tượng đang gọi hàm hày
        string name, phone, email, password, confirmPass;

        cout << "Enter details for the new customer:" << endl;

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
        persons.push_back(new Customer(name, phone, email, password));
        cout << "Customer " << name << " added successfully.\n";
        break;
    }
    case 2: {
        // Thêm khách hàng từ file
        string fileName;
        cout << "Enter the filename: ";
        getline(cin, fileName);
        addCustomersFromFile(fileName, persons);
        break;
    }
    default:
        cout << "Invalid option. Please choose 1 or 2.\n";
        break;
    }
}

//trả về 0 hoặc 1
void Employee::addCustomersFromFile(const string& fileName, vector<person*>& persons) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email, password;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password); // Assuming password is the last field

        // Thêm khách hàng vào danh sách
        persons.push_back(new Customer(name, phone, email, password));
        cout << "Customer " << name << " added successfully from file.\n";
    }

    file.close();
}


void Employee::deleteCustomer(vector<person*>& persons) {
    string id;
    cout << "Enter customer ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(persons.begin(), persons.end(), [&](person* p) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ xóa đối tượng là Customer
        return cust && cust->getID() == id;
        });

    if (it != persons.end()) {
        delete* it;
        persons.erase(it, persons.end());
        cout << "Customer deleted successfully.\n";
    }
    else {
        cout << "Customer not found.\n";
    }
}


void Employee::editCustomer(vector<person*>& persons) {
    string id;
    cout << "Enter customer ID to edit: ";
    cin >> id;
    cin.ignore();

    for (person* p : persons) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ chỉnh sửa đối tượng Customer
        if (cust && cust->getID() == id) {
            cust->updateInfo();
            cout << "Customer info updated successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}


void Employee::addEmployee(vector<person*>& persons) {
    string name, phone, email, role, password;

    // Nhập thông tin của nhân viên mới
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";
    password = hidenPass();  

    cout << "Enter Role: ";
    getline(cin, role);

    // Tạo đối tượng Employee mới và thêm vào danh sách
    persons.push_back(new Employee(name, phone, email, password, role));

    cout << "Employee " << name << " added successfully.\n";
}

void Employee::updateEmployee(vector<person*>& persons) {
    string id;
    cout << "Enter employee ID to update: ";
    cin >> id;
    cin.ignore();

    for (person* p : persons) {
        Employee* emp = dynamic_cast<Employee*>(p);  // Chỉ cập nhật đối tượng Employee
        if (emp && emp->getID() == id) {
            emp->updateInfo();
            cout << "Employee info updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

void Employee::deleteEmployee(vector<person*>& persons) {
    string id;
    cout << "Enter employee ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(persons.begin(), persons.end(), [&](person* p) {
        Employee* emp = dynamic_cast<Employee*>(p);  // Chỉ xóa đối tượng là Employee
        return emp && emp->getID() == id;
        });

    if (it != persons.end()) {
        delete* it;
        persons.erase(it, persons.end());
        cout << "Employee deleted successfully.\n";
    }
    else {
        cout << "Employee not found.\n";
    }
}


void Employee::editEmployee(vector<person*>& persons) {
    string id;
    cout << "Enter employee ID to edit: ";
    cin >> id;
    cin.ignore();

    for (person* p : persons) {
        Employee* emp = dynamic_cast<Employee*>(p);  // Chỉ chỉnh sửa đối tượng Employee
        if (emp && emp->getID() == id) {
            emp->updateInfo();
            cout << "Employee info updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}
void Employee::setInfor(person& a) {
    Employee& emp = dynamic_cast<Employee&>(a); // Chuyển đổi sang Customer
    emp.setName();
    emp.setPhone();
    emp.setEmail();
    emp.setPass();
}

// xoá hàm này vì chỉ có 1 quản lý nếu một nhân viên được thay đổi role tự ý lên quản lí thì bài toán thực tế không có cái này
string Employee::getUserRole() {
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
void Employee::handleManagerMenu(Employee& manager, vector<person*>& persons) {
    while (true) {
        int choice;
        cout << "\n--- Manager Menu ---\n";
        cout << "1. Manage Customers\n";
        cout << "2. Manage Employees\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();  // Xóa bộ đệm

        switch (choice) {
        case 1:
            manager.manageCustomers(persons);  // Gọi phương thức quản lý khách hàng
            break;
        case 2:
            manager.manageEmployees(persons);  // Gọi phương thức quản lý nhân viên
            break;
        case 3:
            cout << "Exiting...\n";
            // Giải phóng bộ nhớ trước khi thoát
            for (person* p : persons) {
                delete p;
            }
            persons.clear();

            return;  // Thoát khỏi hàm
        default:
            cout << "Invalid option. Please select again.\n";
        }
    }
}

// tên hàm này là sao hiển thị bán hàng và khách hàng?
void Employee::displaySalesCustomers(const vector<person*>& persons) {
    cout << "\n--- Customer List ---\n";
    person::printTableHeader();  // Giả định bạn có hàm này trong lớp person
    for (person* p : persons) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ hiển thị nếu là Customer
        if (cust) {
            cust->display();  // Hiển thị thông tin khách hàng
        }
    }
}


// Hàm xử lý theo vai trò người dùng
void Employee::handleUserRole(string role, vector<person*>& persons) {
    if (role == "MANAGER") {
        // đối tượng admin không tạo ở đây. Nếu tạo mới thì sẽ có personID bởi vì này kế thừa từ person và id của person thì tăng đều. Như vậy đâu biết được id để đăng nhập đâu
        // Tạo đối tượng Employee cho quản lý
        Employee manager("Default", "0000000000", "default@example.com", role, "default123");
        handleManagerMenu(manager, persons);  // Gọi hàm menu cho Manager
    }
    else if (role == "SALES") {
        displaySalesCustomers(persons);  // Hiển thị danh sách khách hàng
    }
}
