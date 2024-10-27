#include "Employee.h"
#include "Customer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <string>

using namespace std;

Employee::Employee(const string& name, const string& phone, const string& email, const string& role, const string& password)
    : person(name, phone, email, password,"unknown") {}

void Employee::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(20) << getPhone()
        << endl;
}
string Employee::generateEmpID() {
        
        stringstream ss;
        ss <<"EP"<< setw(5) << setfill('0') << nextEmpID++; 
        return ss.str();
    }
    Employee* Employee::getEmpById(const string id){
    for (Employee *Employee : Em){
        if (Employee->getEmpID() == id){   
            return Employee;
        }
    }
    return nullptr;
}
// tương tự hàm set của person. Ở đây không nên cho update role bởi vì khách hàng là kahcs hàng mà nhân viên là nhân viên.
// mỗi role có những giá trị chứa khác nhau, đổi là sẽ lỗi. bài toán thực tế thì có nhưng nếu có thì họ sẽ tạo một tài khoàn nhân viên mới chứ không thay đổi thế này.

void Employee::updateInfo() {
    string newPhone,newEmail;
    cout<<"Enter the new phone";
    getline(cin,newPhone);
    setPhone(newPhone);
    cout<<"Enter the new email";
    getline(cin,newEmail);
    setEmail(newEmail);
    
}

void Employee::saveToFile( const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for ( person* p : obj) {
        Employee* emp = dynamic_cast< Employee*>(p); // Chỉ lưu thông tin nhân viên
        if (emp) {
            file << emp->getID() << "," << emp->getName() << "," << emp->getPhone() << "," << emp->getEmail() << "," << emp->getRole() << endl;
        }
    }

    file.close();
}
// lỗi tương tự cus.h

int Employee::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        return 0;  // Không mở được file
    }

    string line;
    while (getline(file, line)) {
        string id, name, phone, email, role;

        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, role);

        try {
            // Kiểm tra tính hợp lệ của tên (chỉ chứa chữ cái và khoảng trắng)
            if (!all_of(name.begin(), name.end(), [](char c) { return isalpha(c) || isspace(c); })) {
                throw invalid_argument("Invalid name format.");
            }

            // Kiểm tra tính hợp lệ của số điện thoại (chỉ chứa số)
            if (!all_of(phone.begin(), phone.end(), ::isdigit)) {
                throw invalid_argument("Invalid phone number format.");
            }

            // Kiểm tra tính hợp lệ của email
            const regex emailPattern(R"((\w+)(\.\w+)*@(\w+\.)+\w+)");
            if (!regex_match(email, emailPattern)) {
                throw invalid_argument("Invalid email format.");
            }
            obj.push_back(new Employee(id, name, phone, email, role));
        } 
        catch (const invalid_argument&) {
            return 0;  // Trả về 0 nếu có lỗi trong dữ liệu
        } 
        catch (const out_of_range&) {
            return 0;  // Trả về 0 nếu dữ liệu nằm ngoài phạm vi
        }
    }

    file.close();
    return 1;  // Trả về 1 nếu thành công
}

string Employee::getRole() const {
    return role;
}

// Các chức năng quản lý khách hàng và nhân viên, chỉ khả dụng nếu role là  "MANAGER"
//sửa lại role "adimin" thêm câu lệnh if(this->role() == "admin"){thì làm trong này}else{cout<<" không được phép...."}


    // rồi đã kiểm tra nếu nó là role "sale chưa? "
    void Employee::manageCustomers() {
    // Kiểm tra vai trò
    if (this->role!= "admin") {
        cout << "no access\n";
        return; // Kết thúc hàm nếu không phải là admin
    }

    int option;
    while (true) {
        cout << "\n--- Customer managent ---\n";
        cout << "1. View customers\n2. Search customer\n3. Add new customer\n4. Delete customer\n5. Edit customer\n0. Exit\nChoose: ";
        cin >> option;
        cin.ignore();

        if (option == 0) {
           cout << "Exiting customer management.\n";
            break;
        }

        switch (option) {
        case 1:
            person::printTableHeader();
            for (person* p : obj) {
                Customer* cust = dynamic_cast<Customer*>(p); // Chỉ hiển thị khách hàng
                if (cust) {
                    cust->display();
                }
            }
            break;
        case 2:
            searchCustomerByID();
            break;
        case 3:
            addCustomer();
            break;
        case 4:
            deleteCustomer(); 
            break;
        case 5:
            editCustomer();
            break;
        default:
            cout << "Invalid option. Please choose a valid option.\n";
        }
    }
}
    //nên xây dựng while nhập vào 0 nếu muốn thoát chế độ quản lí cus, còn lại cứ nhập vào những số khác thì cứ để làm rồi quay lại bắt chọn tính năng

// tương tự phải kiểm tra role

void Employee::manageEmployees() {
    // Kiểm tra vai trò
    if (this->role!= "admin") {
        cout << "no access\n";
        return; // Kết thúc hàm nếu không phải là admin
    }

    int option;
    while (true) {
         cout << "\n--- Employee Management ---\n";
        cout << "1. View employees\n2. Search employee\n3. Add new employee\n4. Delete employee\n5. Edit employee\n0. Exit\nChoose: ";
        cin >> option;
        cin.ignore();

        if (option == 0) {
            cout << "exiting.\n";
            break; 
             }

        switch (option) {
        case 1:
            person::printTableHeader();
            for (person* p : obj) {
                Employee* emp = dynamic_cast<Employee*>(p); // Chỉ hiển thị nhân viên
                if (emp) {
                    emp->display();
                }
            }
            break;
        case 2:
            searchEmployeeByID(); // Sửa lại thành hàm tìm kiếm
            break;
        case 3:
            addEmployee(); 
            break;
        case 4:
            deleteEmployee(); 
            break;
        case 5:
            editEmployee();
            break;
        default:
            cout << "invalid\n";
        }
    }
}

int Employee::searchCustomerByID() {
    string searchID;
    cout << "Enter customer ID to search: ";
    cin >> searchID;
    cin.ignore();
    bool found = false;

    for (person* p : obj) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ tìm kiếm trong đối tượng Customer
        if (cust && cust->getID() == searchID) {
            cust->display();
            found = true;
            break;
        }
    }
    return found ? 1 : 0;
     // không xử lí in ra thông báo ở đây, trả về 0 hoặc 1 để làm việc đó ở ngoài. ở đâyc chỉ tìm kiếm nếu có thì in ra trả về 1, không có thì trả về 0
}

// Hàm chuyển đổi chuỗi thành chữ thường
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int Employee::searchCustomerByName() {
    string searchKeyword;
    cout << "Enter name keyword to search: ";
    getline(cin, searchKeyword);

    searchKeyword = toLowerCase(searchKeyword);
    bool found = false;

    for (person* p : obj) {
        Customer* cust = dynamic_cast<Customer*>(p);
        if (cust) {
            string customerName = toLowerCase(cust->getName());
            if (customerName.find(searchKeyword) != string::npos) { // Kiểm tra nếu tên chứa từ khóa
                cust->display();
                found = true;
            }
        }
    }

    return found ? 1 : 0;
}


int Employee::addCustomer() {
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
        string Nname, Nphone, Nemail, Npassword, confirmPass;

        cout << "Enter details for the new customer:" << endl;

        cout << "Enter name: ";
        getline(cin, Nname);

        cout << "Enter phone: ";
        getline(cin, Nphone);

        cout << "Enter email: ";
        getline(cin, Nemail);

        // Nhập và xác nhận mật khẩu
        do {
            cout << "Enter password: ";
            Npassword = hidenPass();

            cout << "Confirm password: ";
            confirmPass = hidenPass();

            if (Npassword != confirmPass) {
                cout << "Passwords do not match. Please try again." << endl;
            }
        } while (Npassword != confirmPass);

        // Thêm khách hàng vào danh sách
        string address = "";
       obj.push_back(new Customer( Nname, Nphone, Nemail, Npassword,address));
       cout << "Customer " << name << " added successfully.\n";

        break;
    }
    case 2: {
        // Thêm khách hàng từ file
        string fileName;
        cout << "Enter the filename: ";
        getline(cin, fileName);
        addCustomersFromFile(fileName);
        break;
    }
    default:
        cout << "Invalid option. Please choose 1 or 2.\n";
        break;
    }
}

//trả về 0 hoặc 1
int Employee::addCustomersFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return 0;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email, password;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password); 

        // Thêm khách hàng vào danh sách
        string address="";
        obj.push_back(new Customer(address,name, phone, email, password));
    }

    file.close();
    return 1;
}


   int Employee::deleteCustomer() {
    string id;
    cout << "Enter customer ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(obj.begin(), obj.end(), [&](person* p) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ xóa đối tượng là Customer
        return cust && cust->getID() == id;
        });

    if (it != obj.end()) {
        delete* it;
       obj.erase(it, obj.end());
        return 1;
    }
    else {
        return 0;
    }
}


int Employee::editCustomer() {
    string id;
    cout << "Enter customer ID to edit: ";
    cin >> id;
    cin.ignore();

    for (person* p : obj) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ chỉnh sửa đối tượng Customer
        if (cust && cust->getID() == id) {
            cust->updateInfo();
            return 1;
        }
    }
    cout << "Customer not found.\n";
}


int Employee::addEmployee() {
    string Nname, Nphone, Nemail, role, Npassword;

    // Nhập thông tin của nhân viên mới
    cout << "Enter Name: ";
    getline(cin, Nname);
    cout << "Enter Phone: ";
    getline(cin, Nphone);
    cout << "Enter Email: ";
    getline(cin, Nemail);
    cout << "Enter Password: ";
    Npassword = hidenPass();  

    cout << "Enter Role: ";
    getline(cin, role);

    // Tạo đối tượng Employee mới và thêm vào danh sách
    obj.push_back(new Employee(name, phone, email, Npassword, role));

    cout << "Employee " << name << " added successfully.\n";
}

int Employee::updateEmployee() {
    string id;
    cout << "Enter employee ID to update: ";
    cin >> id;
    cin.ignore();

    for (person* p : obj) {
        Employee* emp = dynamic_cast<Employee*>(p);  // Chỉ cập nhật đối tượng Employee
        if (emp && emp->getID() == id) {
            emp->updateInfo();
            cout << "Employee info updated successfully.\n";
            return;
        }
    }
    cout << "Employee not found.\n";
}

int Employee::deleteEmployee() {
    string id;
    cout << "Enter employee ID to delete: ";
    cin >> id;
    cin.ignore();

    auto it = remove_if(obj.begin(), obj.end(), [&](person* p) {
        Employee* emp = dynamic_cast<Employee*>(p);  // Chỉ xóa đối tượng là Employee
        return emp && emp->getID() == id;
        });

    if (it != obj.end()) {
        delete* it;
        obj.erase(it, obj.end());
        cout << "Employee deleted successfully.\n";
    }
    else {
        cout << "Employee not found.\n";
    }
}


int Employee::editEmployee() {
    string id;
    cout << "Enter employee ID to edit: ";
    cin >> id;
    cin.ignore();

    for (person* p : obj) {
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
    Employee& emp = dynamic_cast<Employee&>(a);
    string name,phone,email,pass;
     cout<<"enter the name";
     getline(cin,name);
     emp.setName(name);
     cout<<"enter the phone";
     getline(cin,phone);
     emp.setPhone(phone);
     cout<<"enter the email";
     getline(cin,email);
     emp.setEmail(email);
     emp.setPass();
}

// xoá hàm này vì chỉ có 1 quản lý nếu một nhân viên được thay đổi role tự ý lên quản lí thì bài toán thực tế không có cái này

void Employee::handleManagerMenu(Employee& manager) {
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
            manager.manageCustomers();  // Gọi phương thức quản lý khách hàng
            break;
        case 2:
            manager.manageEmployees();  // Gọi phương thức quản lý nhân viên
            break;
        case 3:
            cout << "Exiting...\n";
            // Giải phóng bộ nhớ trước khi thoát
            for (person* p : obj) {
                delete p;
            }
            obj.clear();

            return;  // Thoát khỏi hàm
        default:
            cout << "Invalid option. Please select again.\n";
        }
    }
}

// tên hàm này là sao hiển thị bán hàng và khách hàng?
void Employee::displayCustomers() {
    cout << "\n--- Customer List ---\n";
    person::printTableHeader();  
    for (person* p : obj) {
        Customer* cust = dynamic_cast<Customer*>(p);  // Chỉ hiển thị nếu là Customer
        if (cust) {
            cust->display();  // Hiển thị thông tin khách hàng
        }
    }
}


// Hàm xử lý theo vai trò người dùng
// đối tượng admin không tạo ở đây. Nếu tạo mới thì sẽ có personID bởi vì này kế thừa từ person và id của person thì tăng đều. Như vậy đâu biết được id để đăng nhập đâu
void Employee::handleUserRole(string role) {
    if (role == "MANAGER") {
        // Yêu cầu ID để tìm kiếm nhân viên
        string empID;
        cout << "Enter your employee ID  ";
        cin >> empID;

        Employee* manager = getEmpById(empID);
        if (manager && manager->getRole() == "MANAGER") {
            handleManagerMenu(*manager);  
        } else {
            cout << "Access is not allowed\n";
        }
    }
    else if (role == "SALES") {
        displayCustomers();
    }
}

