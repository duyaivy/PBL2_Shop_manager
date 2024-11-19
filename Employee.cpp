#include "./header/Employee.h"
#include "./header/Product.h"
#include "./header/Person.h"
#include "./header/Customer.h"
#include "./header/global.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

Employee::Employee(const string &name, const string &phone, const string &email, const string &password, const string &role,const bool & _isDelete, const string &dayToWork)
    : Person(name, phone, email, password, role,_isDelete)
{
    this->ID = generateID();
    this->dayToWork = dayToWork;
}

void Employee::display()
{
    if(this->isDelete) return;
    cout << setw(10) << getID()
         << setw(30) << getName()
         << setw(30) << getEmail()
         << setw(15) << getPhone()
         << setw(20) << getDayToWork()
         << endl;
}
void Employee::viewAllInfor()
{
    if(this->isDelete) return;

    cout << setw(20) << "ID: " << getID() << endl
         << setw(20) << "Full name: " << getName() << endl
         << setw(20) << "Email: " << getEmail() << endl
         << setw(25) << "Phone: " << getPhone() << endl
         << setw(20) << "Day to work: " << getDayToWork() << endl
         << setw(20) << "Password: " << getPass() << endl;
}
string Employee::generateID()
{

    stringstream ss;
    ss << "EP" << setw(5) << setfill('0') << nextEmpID++;
    return ss.str();
}
string getTimeNow()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int year = now->tm_year + 1900; // tm_year tính từ năm 1900
    int month = now->tm_mon + 1;    // tm_mon từ 0 đến 11
    int day = now->tm_mday;

    ostringstream oss;
    oss << setfill('0') << setw(2) << day << "/" << setw(2) << month << "/" << year;
    string currentDate = oss.str();
    return currentDate;
}
Employee *Employee::getEmpById(const string id)
{
    for (Person *p : Person::Person::obj)
    {
        if (p->getID() == id)
        {
            Employee *emp = dynamic_cast<Employee *>(p);
            return emp;
        }
    }
    return nullptr;
}
int Employee::setDayToWork(string day)
{
    this->dayToWork = day;
}
string Employee::getDayToWork()
{
    return dayToWork;
}
void Employee::updateInfo()
{
    int choice;
    cout << "Choose update option:" << endl;
    cout << "1. Update all information" << endl;
    cout << "2. Update part of information" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Update all information" << endl;
        this->setInfor();
        break;

    case 2:
    {
        system("cls");
        bool continueUpdating = true; // Biến để kiểm soát vòng lặp

        while (continueUpdating)
        {
            int partChoice;
            cout << "Choose part to update:" << endl;
            cout << "1. Update phone" << endl;
            cout << "2. Update email" << endl;
            cout << "3. Update password" << endl;
            cout << "4. Finish updating" << endl; // Thêm lựa chọn để kết thúc cập nhật
            cout << "Enter your choice: ";
            cin >> partChoice;
            cin.ignore();

            switch (partChoice)
            {
            case 1:
            {

                string newPhone;
                cout << "Enter new phone number: ";
                getline(cin, newPhone);
                setPhone(newPhone);
                break;
            }

            case 2:
            {
                string newEmail;
                cout << "Enter new email: ";
                getline(cin, newEmail);
                setEmail(newEmail);
                break;
            }

            case 3:
            {
                string password, confirmPass;
                cout << "Enter old password:\t";
                password = hidenPass();
                if (this->pass == password)
                {
                    cout << "Enter new password:\t";
                    password = hidenPass();
                    int todo = 1, maxTry = 3;

                    while (todo < maxTry)
                    {
                        cout << "Confirm new password: ";
                        confirmPass = hidenPass();
                        if (password == confirmPass)
                        {
                            setPass(password);
                            cout << "Password set successfully!" << endl;
                            break;
                        }
                        else
                        {
                            todo++;
                            if (todo < maxTry)
                            {
                                cout << "Passwords do not match. Please try again!" << endl;
                            }
                            else
                            {
                                cout << "Maximum attempts reached. Password not set." << endl;
                            }
                        }
                    }
                }
                else
                {
                    cout << "Wrong old password, so you can't reset password!" << endl;
                }
                break;
            }

            case 4:
            {
                continueUpdating = false;
                cout << "Finished updating" << endl;
                break;
            }

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
        break;
    }

    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

void Employee::saveToFile(const string &filename)
{
    ofstream file(filename, ios::trunc);
    if (!file)
    {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (Person *p : Person::obj)
    {
        Employee *emp = dynamic_cast<Employee *>(p); // Chỉ lưu thông tin nhân viên
        if (emp)
        {
            file << emp->getID() << "," << emp->getName() << "," << emp->getPhone() << "," << emp->getEmail() << "," << emp->getPass() << "," << emp->getRole()<< "," << emp->getDelete() << "," << emp->getDayToWork();
            // save invoice
            for (string invoice : emp->idInvoice)
            {
                file << "," << invoice;
            }
            file << endl;
        }
    }

    file.close();
}
// lỗi tương tự cus.h

int Employee::loadFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        return 0; // Không mở được file
    }

    string line;
    while (getline(file, line))
    {
        string id, name, phone, email, pass, role, isDel,day, invoice;

        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, pass, ',');
        getline(ss, role, ',');
        getline(ss, isDel, ',');
        getline(ss, day, ',');
        getline(ss, invoice, ',');

        try
        {
            // Kiểm tra tính hợp lệ của tên (chỉ chứa chữ cái và khoảng trắng)
            if (!all_of(name.begin(), name.end(), [](char c)
                        { return isalpha(c) || isspace(c); }))
            {
                throw invalid_argument("Invalid name format.");
            }

            // Kiểm tra tính hợp lệ của số điện thoại (chỉ chứa số)
            if (!all_of(phone.begin(), phone.end(), ::isdigit))
            {
                throw invalid_argument("Invalid phone number format.");
            }
            bool del;
            (isDel == "1") ? del = true: del = false;
            Employee *newEmp = new Employee(name, phone, email, pass, role, del, day);
            Person::obj.push_back(newEmp);
            if (invoice != "")
                newEmp->addInvoice(invoice);
            // add het invoice cua person
            while (getline(ss, invoice, ','))
            {
                newEmp->addInvoice(invoice);
            }
        }
        catch (const invalid_argument &)
        {
            return 0; // Trả về 0 nếu có lỗi trong dữ liệu
        }
        catch (const out_of_range &)
        {
            return 0; // Trả về 0 nếu dữ liệu nằm ngoài phạm vi
        }
    }

    file.close();
    return 1; // Trả về 1 nếu thành công
}

// Các chức năng quản lý khách hàng và nhân viên, chỉ khả dụng nếu role là  "MANAGER"
// sửa lại role "adimin" thêm câu lệnh if(this->role() == "admin"){thì làm trong này}else{cout<<" không được phép...."}

// rồi đã kiểm tra nếu nó là role "sale chưa? "
void Employee::manageCustomers()
{
    // Kiểm tra vai trò
    if (this->role == "CUSTOMER")
    {
        cout << "No access\n";
        return; // Kết thúc hàm nếu không phải là admin
    }

    int option;
    while (true)
    {
        system("cls");

        cout << "\n--- Customer management ---\n";
        cout << "1. View customers\n2. Search customer\n3. Add new customer\n4. Delete customer\n5. Edit customer\n0. Exit\nChoose: ";
        cin >> option;
        cin.ignore();

        if (option == 0)
        {
            cout << "Exiting....\n";
            break;
        }

        switch (option)
        {
        case 1:
            system("cls");
            Customer::printTableHeader();
            for (Person *p : Person::obj)
            {
                Customer *cust = dynamic_cast<Customer *>(p); // Chỉ hiển thị khách hàng
                if (cust)
                {
                    cust->display();
                }
            }
            Employee::handleOneCus();
            break;
        case 2:
        {
            system("cls");
            // string searchID;
            // cout << "Enter customer ID to search (0 to cancel): ";
            // cin >> searchID;
            // cin.ignore();
            // if (searchID == "0")
            // {
            //     cout << "Canceled searching.\n";
            //     break;
            // }
            // bool found = false;
            // Customer::printTableHeader();
            // for (Person *p : Person::obj)
            // {
            //     Customer *cust = dynamic_cast<Customer *>(p); // Chỉ tìm kiếm trong đối tượng Customer
            //     if (cust && cust->getID() == searchID)
            //     {
            //         cust->display();
            //         found = true;
            //         break;
            //     }
            // }
            // if (!found)
            // {
            //     cout << "Not Found " << searchID << endl;
            //     system("pause");
            //     break;
            // }
            Customer::searchCustomerByName();
            // xuly sau neu search thanh cong
            Employee::handleOneCus();

            break;
        }
        case 3:
        {
            system("cls");
            int choice;
            cout << "Choose how to add a customer:\n";
            cout << "1. Add customer manually\n";
            cout << "2. Add customers from file\n";
            cout << "Choose an option (0 to cancel): ";
            cin >> choice;
            cin.ignore(); // Clear input buffer

            if (choice == 0)
            {
                cout << "Canceled adding customer.\n";
                break;
            }

            switch (choice)
            {
            case 1:
            {
                system("cls");
                string Nname, Nphone, Nemail, Npassword, confirmPass, Naddress;

                cout << "Enter details for the new customer:" << endl;

                cout << "Enter name: ";
                getline(cin, Nname);

                cout << "Enter phone: ";
                getline(cin, Nphone);

                cout << "Enter email: ";
                getline(cin, Nemail);

                cout << "Enter address: ";
                getline(cin, Naddress);

                // Nhập và xác nhận mật khẩu
                do
                {
                    cout << "Enter password: ";
                    Npassword = hidenPass();

                    cout << "Confirm password: ";
                    confirmPass = hidenPass();

                    if (Npassword != confirmPass)
                    {
                        cout << "Passwords do not match. Please try again." << endl;
                    }
                } while (Npassword != confirmPass);

                // Thêm khách hàng vào danh sách
                Customer *newCustomer = new Customer(Nname, Nphone, Nemail, Npassword,false, Naddress);
                Person::obj.push_back(newCustomer);
                cout << "Customer " << Nname << " added successfully.\n";
                system("pause");

                break;
            }
            case 2:
            {
                // Thêm khách hàng từ file
                system("cls");
                string fileName;
                cout << "Enter the filename (0 to cancel): ";
                getline(cin, fileName);
                if (fileName == "0")
                {
                    cout << "Canceled loading from file.\n";
                    break;
                }
                Customer::loadFromFile(fileName);
                break;
            }
            default:
                cout << "Invalid option. .\n";
                break;
            }
            system("pause");

            break;
        }
        case 4:
        {
            system("cls");
            string id;
            cout << "Enter customer ID to delete (0 to cancel): ";
            cin >> id;
            cin.ignore();
            if (id == "0")
            {
                cout << "Canceled deleting customer.\n";
                break;
            }
            if (Customer::getCusById(id) != nullptr)
            {
                Customer::getCusById(id)->deleteCustomer();
                // Customer::saveToFile("customers.csv");
            }
            else
            {
                cout << "Don't have id: " << id << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            string id;
            cout << "Enter customer ID to edit (0 to cancel): ";
            cin >> id;
            cin.ignore();
            if (id == "0")
            {
                cout << "Canceled editing customer.\n";
                system("pause");
                break;
            }
            if (Customer::getCusById(id))
            {
                Customer::getCusById(id)->updateInfo();
            }
            else
            {
                cout << "Don't have id: " << id << endl;
            }
            break;
        }
        default:
            cout << "Invalid option.\n";
        }
    }
}

// nên xây dựng while nhập vào 0 nếu muốn thoát chế độ quản lí cus, còn lại cứ nhập vào những số khác thì cứ để làm rồi quay lại bắt chọn tính năng

// tương tự phải kiểm tra role

void Employee::manageEmployees()
{
    // Kiểm tra vai trò
    if (this->role != "MANAGER")
    {
        cout << "no access\n";
        return; // Kết thúc hàm nếu không phải là admin
    }

    int option;
    while (true)
    {
        system("cls");
        cout << "\n--- Employee Management ---\n";
        cout << "1. View employees\n2. Search employee\n3. Add new employee\n4. Delete employee\n5. Edit employee\n0. Exit\nChoose: ";
        cin >> option;
        cin.ignore();

        if (option == 0)
        {
            cout << "exiting.\n";
            break;
        }

        switch (option)
        {
        case 1:
            system("cls");
            Employee::printTableHeader();
            for (Person *p : Person::obj)
            {
                Employee *emp = dynamic_cast<Employee *>(p); // Chỉ hiển thị nhân viên
                if (emp)
                {
                    emp->display();
                }
            }
            Employee::handleOneEmp();
            system("pause");
            break;
        case 2:
            system("cls");
            searchEmployeeByID();
            Employee::handleOneEmp();
            // Sửa lại thành hàm tìm kiếm
            system("pause");
            break;
        case 3:
        {
            system("cls");
            string Nname, Nphone, Nemail, Npassword, confirmPass;
            string day = getTimeNow();
            // Nhập thông tin của nhân viên mới
            cout << "Enter Name: ";
            getline(cin, Nname);
            if (Nname == "0")
            {
                break;
            }
            cout << "Enter Phone: ";
            getline(cin, Nphone);
            if (Nphone == "0")
            {
                break;
            }
            cout << "Enter Email: ";
            getline(cin, Nemail);
            if (Nname == "0")
            {
                break;
            }

            do
            {
                cout << "Enter password: ";
                Npassword = hidenPass();
                if (Npassword == "0")
                {
                    break;
                }

                cout << "Confirm password: ";
                confirmPass = hidenPass();

                if (Npassword != confirmPass)
                {
                    cout << "Passwords do not match. Please try again." << endl;
                }
            } while (Npassword != confirmPass);
            // Tạo đối tượng Employee mới và thêm vào danh sách
            Employee *newEmployee = new Employee(Nname, Nphone, Nemail, Npassword, "SALES",true, day);
            Person::obj.push_back(newEmployee);
            cout << "Employee " << Nname << " added successfully.\n";
            system("pause");
            break;
        }

        case 4:
        {
            system("cls");
            string id;
            cout << "Enter Employee ID to delete: ";
            cin >> id;
            cin.ignore();
            if (id == "0")
            {
                break;
            }
            if (Employee::getEmpById(id))
            {
                Employee::getEmpById(id)->deleteEmployee();
            }
            else
            {
                cout << "Don't have id: " << id << endl;
            }
            system("pause");
            break;
        }

        case 5:
        {
            system("cls");
            string id;
            cout << "Enter Employee ID to edit: ";
            cin >> id;
            cin.ignore();
            if (id == "0")
            {
                break;
            }
            if (Employee::getEmpById(id))
            {
                Employee::getEmpById(id)->updateInfo();
            }
            else
            {
                cout << "Don't have id: " << id << endl;
            }
            system("pause");
            break;
        }
        default:
            cout << "invalid\n";
            system("pause");
            break;
        }
    }
}
void Employee::manageProduct()
{
    // Kiểm tra vai trò
    if (this->role == "CUSTOMER")
    {
        cout << "No access\n";
        return; // Kết thúc hàm nếu không phải là admin
    }

    int option;
    while (true)
    {
        system("cls");
        cout << "\n--- Product Management ---\n";
        cout << "1. View Products\n2. Search Product\n3. Add new Product\n4. Delete Product\n5. Edit Product\n0. Exit\nChoose: ";
        cin >> option;
        cin.ignore();

        if (option == 0)
        {
            cout << "exiting.\n";
            break;
        }

        switch (option)
        {
        case 1:
            system("cls");
            Product::displayAllPrd();
            system("pause");
            break;
        case 2:
        {
            system("cls");
            string namee;
            cout << "Enter Name of Product to search (0 to exit): ";
            getline(cin, namee);
            if (namee == "0")
            {
                break;
            }
            if (!Product::searchByName(namee))
            {
                cout << "Not Found Product name " << namee << endl;
            }
            system("pause");
            break;
        }
        case 3:
        {
            //  chinh sua
            system("cls");
            Product *pd = new Product;
            Product::setInfor(pd);
            Product::prd.push_back(pd);
            cout << "Product " << pd->getPrdName() << " added successfully.\n";
        }
            system("pause");
            break;
        case 4:
        {
            system("cls");
            string _id;
            cout << "Enter id of Product to delete: ";
            getline(cin, _id);
            if (Product::getPrdByID(_id))
            {
                Product::getPrdByID(_id)->deletePrd();
                cout << "Delete Product successfully!" << endl;
            }
            else
            {
                cout << "Not Found Product has id" << _id << endl;
            }
            system("pause");
            break;
        }
        case 5:
        {
            system("cls");
            string _id;
            cout << "Enter id of Product to edit: ";
            getline(cin, _id);
            if (Product::getPrdByID(_id))
            {
                Product::setInfor(Product::getPrdByID(_id));
                cout << "Edit Product successfully!" << endl;
            }
            else
            {
                cout << "Not Found Product has id" << _id << endl;
            }
            system("pause");
            break;
        }

        default:
            cout << "invalid\n";
            system("pause");
            break;
        }
    }
}

// xoá hàm này vì chỉ có 1 quản lý nếu một nhân viên được thay đổi role tự ý lên quản lí thì bài toán thực tế không có cái này

void Employee::handleManagerMenu(Employee &manager)
{
    while (true)
    {
        system("cls");
        int choice;
        cout << "\n--- Manager Menu ---\n";
        cout << "1. Manage Customers\n";
        cout << "2. Manage Employees\n";
        cout << "3. Manage Product\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore(); // Xóa bộ đệm

        switch (choice)
        {
        case 1:
            manager.manageCustomers(); // Gọi phương thức quản lý khách hàng
            break;
        case 2:
            manager.manageEmployees(); // Gọi phương thức quản lý nhân viên
            break;
        case 3:
            manager.manageProduct(); // Gọi phương thức quản lý nhân viên
            break;
        case 0:
            cout << "Exiting...\n";
            return; // Thoát khỏi hàm
        default:
            cout << "Invalid option. Please select again.\n";
            system("pause");
            break;
        }
    }
}
void Employee::handleEmployeeMenu(Employee &sale)
{
    if (sale.role != "SALES")
    {
        cout << "no access\n";
        return;
    }
    while (true)
    {
        int choice;
        cout << "1.View Customer\n";
        cout << "2.View Product\n";
        cout << "3.Exit\n";
        cout << "Choose:\n";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            system("cls");
            if (Person::obj.empty())
            {
                cout << "No customers found.\n";
            }
            else
            {
                cout << "\n--- Customer List ---\n";
                Person::printTableHeader();
                for (Person *p : Person::obj)
                {
                    Customer *cust = dynamic_cast<Customer *>(p); // Chỉ hiển thị khách hàng
                    if (cust)
                    {
                        cust->display();
                    }
                }
            }
            break;
        case 2:
            system("cls");
            if (Product::prd.empty())
            {
                cout << "No Product found.\n";
            }
            cout << "\n--- Product List ---\n";
            Product::displayAllPrdToManager();
            break;
        case 3:
            cout << "Exiting...\n";
            // Giải phóng bộ nhớ trước khi thoát
            return; // Thoát khỏi hàm
        default:
            cout << "Invalid option. Please select again.\n";

            break;
        }
    }
}

void Employee::displayCustomers()
{
    system("cls");
    cout << "\n--- Customer List ---\n";
    Person::printTableHeader();
    for (Person *p : Person::obj)
    {
        Customer *cust = dynamic_cast<Customer *>(p); // Chỉ hiển thị nếu là Customer
        if (cust)
        {
            cust->display(); // Hiển thị thông tin khách hàng
        }
    }
}

int Employee::searchEmployeeByID()
{
    // string searchID;
    // cout << "Enter Employee ID to search: ";
    // cin >> searchID;
    // cin.ignore();
    // if (searchID == "0")
    // {
    //     return 0;
    // }
    // bool found = false;

    // for (Person *p : Person::obj)
    // {
    //     Employee *cust = dynamic_cast<Employee *>(p);
    //     if (cust && cust->getID() == searchID)
    //     {
    //         cust->display();
    //         found = true;
    //         break;
    //     }
    // }
    // return found ? 1 : 0;
    system("cls");
    string searchID;
    cout << "Enter employee ID to search (0 to cancel): ";
    cin >> searchID;
    cin.ignore();
    if (searchID == "0")
    {
        cout << "Canceled searching.\n";
        return 0;
    }
    bool found = false;
    Employee::printTableHeader();
    for (Person *p : Person::obj)
    {
        Employee *emp = dynamic_cast<Employee *>(p); // Chỉ tìm kiếm trong đối tượng Customer
        if (emp && emp->getID() == searchID)
        {
            emp->display();
            found = true;
            return 0;
        }
    }
    if (!found)
    {
        cout << "Not Found " << searchID << endl;
        system("pause");
        return 0;
    }
    return 1;
}
void Employee::setInfor()
{
    string t_name, t_phone, t_email;
    cout << "Enter the full name: ";
    getline(cin, t_name);
    setName(t_name);
    cout << "Enter the phone number: ";
    getline(cin, t_phone);
    setPhone(t_phone);
    cout << "Enter the email: ";
    getline(cin, t_email);
    setEmail(t_email);
    string password, confirmPass;
    cout << "Enter old password:\t";
    password = hidenPass();
    if (this->pass == password)
    {
        cout << "Enter new password:\t";
        password = hidenPass();
        int todo = 1, maxTry = 3;
        while (todo < maxTry)
        {
            cout << "Confirm new password: ";
            confirmPass = hidenPass();
            if (password == confirmPass)
            {
                setPass(password);
                cout << "Password set successfully!" << endl;
                break;
            }
            else
            {
                todo++;
                if (todo < maxTry)
                {
                    cout << "Passwords do not match. Please try again!" << endl;
                }
                else
                {
                    cout << "Maximum attempts reached. Password not set." << endl;
                }
            }
        }
    }
    else
    {
        cout << "Wrong old password, so you can't reset password!" << endl;
    }
}

int Employee::deleteEmployee()
{
    //  auto it = find(Person::obj.begin(), Person::obj.end(), this);
    // if (it != Person::obj.end()) {
    //     Person::obj.erase(it);
    //     delete this;
    // }
    this->isDelete = 1;
    return 1;
}
long long Employee::calcRevenue()
{
    long long total = 0;
    for (string inv : this->idInvoice)
    {
        if (Invoice::getInvoiceByID(inv) != nullptr)
        {
            total += Invoice::getInvoiceByID(inv)->getTotalPrice();
        }
        else
        {
            total += 0;
        }
    }
    return total;
}

Employee *Employee::getMaxRevenue()
{
    Employee *maxEmp = nullptr;
    long long max = 0;
    for (Person *p : Person::obj)
    {
        Employee *emp = dynamic_cast<Employee *>(p);
        if (emp)
        {
            if (!max)
            {
                max = emp->calcRevenue();
                maxEmp = emp;
            }
            if (max < emp->calcRevenue())
            {
                max = emp->calcRevenue();
                maxEmp = emp;
            }
        }
    }
    return maxEmp;
}
int Employee::regisEmployee()
{
    if (this->getRole() == "MANAGER")
    {
        string t_name, t_phone, t_email, t_address;
        string dateToWork = getTimeNow();
        cout << "Enter the full name: ";
        getline(cin, t_name);

        cout << "Enter the phone number: ";
        getline(cin, t_phone);

        cout << "Enter the email: ";
        getline(cin, t_email);

        string password, confirmPass;
        cout << "Enter your password:\t";
        password = Person::hidenPass();
        while (1)
        {
            cout << "Confirm your password: ";
            confirmPass = hidenPass();
            if (password == confirmPass)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        // Customer( const string& _password, const string& _address)
        Employee *e = new Employee(t_name, t_phone, t_email, password, "SALES", true,dayToWork);
        Person::obj.push_back(e);
        cout << "Register Employee Sucessfully!\nHere is your infor to Login\n";
        cout << left << setw(15) << "Phone:" << setw(10) << e->getPhone() << endl
             << left << setw(10) << "Password:" << setw(20) << e->getPass() << endl;
        system("pause");
        return 1;
    }
    return 0;
}
int Employee::deleteEmployee(string empID)
{
    if (this->getRole() == "MANAGER")
    {
        if (Employee::getEmpById(empID) != nullptr)
        {
            Employee::getEmpById(empID)->setDelete(1);
            return 1;
        }
        else
            return 0;
    }
    return 0;
}
int Employee::deleteCustomer(string cusID)
{
    if (Customer::getCusById(cusID) != nullptr)
    {
        Customer::getCusById(cusID)->setDelete(1);
        return 1;
    }
    else
        return 0;
}
void Employee::printTableHeader()
{
    cout << left << setw(10) << "ID"
         << setw(30) << "Full Name"
         << setw(30) << "Email"
         << setw(15) << "Phone"
         << setw(20) << "Day to work"
         << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;
}
void Employee::handleOneEmp()
{
    while (1)
    {
        int chosse;
        cout << "Select 1 action:\n";
        cout << "1. Choose 1 Employee to handle.\n";
        cout << "2. Continue to search another Employee.\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> chosse;
        cin.ignore();
        if (chosse == 0)
        {
            cout << "Exit searching...\n";
            system("pause");
            break;
        }

        switch (chosse)
        {
        case 1:
        {
            string ID;
            cout << "Enter employee ID to handle (0 to cancel): ";
            cin >> ID;
            cin.ignore();
            if (ID == "0")
            {
                cout << "Canceled handling.\n";
                break;
            }
            if (Employee::getEmpById(ID) != nullptr)
            {
                Employee::getEmpById(ID)->handleThisEmployee();
            }
            else
            {
                cout << "Don't have Employee has id: " << ID << endl;
                system("pause");
                break;
            }
            break;
        }
        case 2:
        {
            cout << "Continue to search another Employee \n";
            Employee::searchEmployeeByName();
            system("pause");
            break;
        }
        default:
        {
            cout << "invalid";
            system("pause");
            break;
        }
        }
    }
}
void Employee::handleOnePrd()
{
    while (1)
    {
        int chosse;
        cout << "Select 1 action:\n";
        cout << "1. Choose 1 Product to handle.\n";
        cout << "2. Continue to search another Product.\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> chosse;
        cin.ignore();
        if (chosse == 0)
        {

            system("pause");
            break;
        }

        switch (chosse)
        {
        case 1:
        {
            string ID;
            cout << "Enter product ID to handle (0 to cancel): ";
            cin >> ID;
            cin.ignore();
            if (ID == "0")
            {
                cout << "Canceled handling.\n";
                break;
            }
            if (Product::getPrdByID(ID) != nullptr)
            {
                Product::getPrdByID(ID)->handleThisProduct();
            }
            else
            {
                cout << "\nDon't have product has id: " << ID << endl;
                system("pause");
                break;
            }
            break;
        }
        case 2:
        {
            cout << "\nContinue to search another product";
            cout << "\nEnter Name of Product: ";
            string name;
            getline(cin, name);
            if (!Product::searchByName(name))
            {
                cout << "Don't have product has name " << name << "." << endl;
            }
            system("pause");
            break;
        }
        default:
        {
            cout << "Invalid";
            system("pause");
            break;
        }
        }
    }
}
void Employee::handleOneCus()
{
    while (1)
    {
        int chosse;
        cout << "Select 1 action after searching:\n";
        cout << "1. Choose 1 Customer to handle.\n";
        cout << "2. Continue to search another Customer.\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> chosse;
        cin.ignore();
        if (chosse == 0)
        {
            cout << "Exit searching...\n";
            system("pause");
            break;
        }

        switch (chosse)
        {
        case 1:
        {
            string ID;
            cout << "Enter Customer ID to handle (0 to cancel): ";
            cin >> ID;
            cin.ignore();
            if (ID == "0")
            {
                cout << "Canceled handling.\n";
                break;
            }
            if (Customer::getCusById(ID) != nullptr)
            {
                Customer::getCusById(ID)->handleThisCustomer();
            }
            else
            {
                cout << "Don't have Customer has id: " << ID << endl;
                system("pause");
                break;
            }
            break;
        }
        case 2:
        {
            cout << "Continue to search another Customer";
            Customer::searchCustomerByName();
            system("pause");
            break;
        }
        default:
        {
            cout << "Invalid";
            system("pause");
            break;
        }
        }
    }
}

void Employee::handleThisEmployee()
{
    while (1)
    {
        system("cls");
        cout << "--- Handle Employee " << this->getName() << " ---\n\n";
        int chosse;
        cout << "Select 1 action:\n";
        cout << "1. View all information.\n";
        cout << "2. View this Employee's revenue.\n";
        cout << "3. View this Employee's invoice.\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> chosse;
        cin.ignore();
        if (chosse == 0)
        {
            system("pause");
            return;
        }
        switch (chosse)
        {
        case 1:
        {
            cout << "Employee " << this->getName() << "'s all infor.\n";
            this->viewAllInfor();
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Employee " << this->getName() << "'s revenue.\n";
            cout << "\nRevenue of Employee in month is: " << formatCurrency(this->calcRevenue());
            cout << "\nAll product have sold:\n";
            this->getInforInvoice();
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Employee " << this->getName() << "'s invoice.\n";
            this->getInforInvoice();
            system("pause");
            break;
        }
        default:
        {
            cout << "Invalid\n";
            system("pause");

            break;
        }
        }
    }
}
int Employee::searchEmployeeByName()
{   
    string word;
    cout << "\nEnter employee name to search (0 to cancel): ";
    cin >> word;
    cin.ignore();
    if (word == "0")
    {
        cout << "Canceled searching.\n";
        return 0;
    }
    string lowerWord = toLowerCase(word);
    bool found = false;
    Employee::printTableHeader();
    for (Person *p : Person::obj)
    {
        Employee *emp = dynamic_cast<Employee *>(p); 

        string lowerName = toLowerCase(p->getName());
      
        if (emp && lowerName.find(lowerWord) != std::string::npos)
        {
            emp->display();
            found = true;
        }
     
    }
    if (!found)
    {
        cout << "Not Found Employee name: " << word << endl;
        system("pause");
        return 0;
    }
    return 1;
}
