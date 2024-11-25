#include "./header/Employee.h"
#include "./header/Product.h"
#include "./header/Person.h"
#include "./header/Customer.h"
#include"./header/InvoiceDetail.h"
#include"./header/Invoice.h"
#include <iostream>

using namespace std;
int setUpDataBase();
int run();
int saveDataBase();
int Product::nextPrdID = 1; 
int Employee::nextEmpID = 1;
int Customer::nextCusID = 1;
int InvoiceDetail::nextDetailID = 1;
int Invoice::nextInvoiceID = 1;

int main() {
    run();
    
    
       

    // for (Person *p : Person::obj){
    //     Employee* em = dynamic_cast< Employee*>(p);
    //     em->display();
    // }
    // for (product *p : prd){
    //     p->getInfor(p);
    // }
    
     
        // Employee* em = Employee::getEmpById(id,Person::obj);
        // if (!em) {
        //     cout << "Invalid ID. Please try again or enter '0' to exit.\n";
        //     continue; // Yêu cầu nhập lại ID
        // }
// g++ Qli.cpp Person.cpp Employee.cpp Customer.cpp product.cpp -o z
        // Kiểm tra nếu người dùng muốn thoát
       
        

        
       
       

        // // Kiểm tra mật khẩu
        // if (emp->getPass() == password) {
        //     // Đăng nhập thành công
        //     if (emp->getRole() == "MANAGER") {
        //         Employee::handleManagerMenu(*emp);
        //     } else if (emp->getRole() == "SALES") {
        //         Employee::handleEmployeeMenu(*emp);
        //     }
        //     break; // Thoát khỏi vòng lặp khi đăng nhập thành công
        // } else {
        //     cout << "Invalid password. Please try again or enter '0' to exit.\n";
        // }
    

    // Sau khi thực hiện các tác vụ, lưu dữ liệu lại vào các file CSV
    // Employee::saveToFile("employees.csv");
    // Customer::saveToFile("customers.csv");
    // product::saveToFile("products.csv");

    // Giải phóng bộ nhớ cho các đối tượng trong Person::obj và prd
    // for (auto p : Person::obj) {
    //     delete p;
    // }
    // for (auto p : prd) {
    //     delete p;
    // }

    return 0;
}
// khong xoa duowc customer



int run(){
// g++ Qli.cpp Person.cpp Employee.cpp Customer.cpp product.cpp -o z
//      g++ main.cpp Product.cpp InvoiceDetail.cpp Invoice.cpp Employee.cpp Person.cpp Customer.cpp global.cpp -o m

    setUpDataBase();
    int choose;
    while (1)
    {
        system("cls"); // xoa man hinh hien tai
        cout << "Shop Manager";
        cout << "\n1. Login";
        cout << "\n2. Sign up";
        cout << "\n0. Exit program";
        cout << "\nSelect: ";
        // for (Person *p : Person::obj){
        // cout<<p->getID()<<endl;
        //  }
        cin >> choose;
        cin.ignore();
        switch (choose)
        {
        case 0: 
            {
            cout << "Exiting...\n";
            saveDataBase();
            return 0;
            break;
            }
        case 1: 
            {
            system("cls"); 
            cout << "\nLogin\n";
            string phone,password;
           while (true) {
                cout << "Enter your phone: ";
                cin >> phone;
                cin.ignore();
                cout << "Enter your password: ";
                cin >> password;
                cin.ignore();
                Person *curP = nullptr;

                if(Person::login(phone, password,Person::obj, curP)){
                    cout<<"\nLogin Successfully!\n";
                    cout<<curP->getDelete();
                    {
                        // xu li sua dang nhap
                        if(curP->getRole() == "CUSTOMER"){
                            Customer *curCus = dynamic_cast<Customer*>(curP);
                            curCus->handleThisCustomer();
                        }else{
                            Employee *curEmp = dynamic_cast<Employee*>(curP);
                            if (curP->getRole() == "MANAGER") {
                                Employee::handleManagerMenu(*curEmp);
                            } else if (curEmp->getRole() == "SALES") {
                                Employee::handleEmployeeMenu(*curEmp);
                            }
                        }
                        break;
                    }

                    // out khoi dang nhap
                    break;
                }
                else{
                cout<<"Invalid Phone or Password. Please try again or enter '0' to return\n";
                }
                if (phone == "0") {
                    cout << "Return\n";
                    break; 
                }

            }
            break;
            }
        case 2: 
            {
            system("cls"); 
            cout << "\nRegister Customer\n";
            Customer::regis();
            break;
            }
        default:
        {
        cout<<"Please choose 1,2,0.\n";
            break;
        }
        }
        
    }
    return 0;
}
int setUpDataBase(){
    if (!Product::loadFromFile(".\\csv\\products.csv") ) {
        cerr << "Failed to load product data.\n";
        return 0;
    }
    if (!InvoiceDetail::loadFromFile(".\\csv\\detail.csv")) {
        cerr << "Failed to load invoice detail data.\n";
        return 0;
    }
    if (!Invoice::loadFromFile(".\\csv\\invoice.csv")) {
        cerr << "Failed to load invoice data.\n";
        return 0;
    }
    if (!Employee::loadFromFile(".\\csv\\employees.csv") ) {
        cerr << "Failed to load employee data.\n";
        return 0;
    }
    if (!Customer::loadFromFile(".\\csv\\customers.csv") ) {
        cerr << "Failed to load customer data.\n";
        return 0;
    }
    return 1;
}
int saveDataBase(){
    Product::saveToFile(".\\csv\\products.csv");
    InvoiceDetail::saveToFile(".\\csv\\detail.csv");
    Invoice::saveToFile(".\\csv\\Invoice.csv");
    Employee::saveToFile(".\\csv\\employees.csv");
    Customer::saveToFile(".\\csv\\customers.csv");
}