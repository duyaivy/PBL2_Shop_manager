
#include "./header/global.h"
#include <iostream>

using namespace std;

int run();
int Product::nextPrdID = 1; 
int Employee::nextEmpID = 1;
int Customer::nextCusID = 1;
int InvoiceDetail::nextDetailID = 1;
int Invoice::nextInvoiceID = 1;

int main() {
    // Employee(name, phone, email, pass, role, del, day);
    Employee *e = new Employee("admin","000000","admin@email.com","123456","MANAGER",false,"12/10/2024");
    Person::obj.push_back(e);
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
                            // chua xu li
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
