#include "Customer.h"
#include "person.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>  // Thêm thư viện regex để kiểm tra email
#include <iomanip>
using namespace std;
static int nextCusID = 1;

Customer::Customer( const string& _name, const string& _phone, const string& _email, const string& _password, const string& _address)
    : person(_name, _phone, _email, _password, "CUSTOMER"),  address(_address) {
        this->ID= generateID();
    };

void Customer::updateInfo() {
    int choice;
    cout << "Choose update option:" << endl;
    cout << "1. Update all information" << endl;
    cout << "2. Update part of information" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        cout << "Update all information" << endl;
        this->setInfor();
        break;

    case 2: {
        bool continueUpdating = true; // Biến để kiểm soát vòng lặp

        while (continueUpdating) {
            int partChoice;
            cout << "Choose part to update:" << endl;
            cout << "1. Update phone" << endl;
            cout << "2. Update email" << endl;
            cout << "3. Update password" << endl;
            cout << "4. Finish updating" << endl; // Thêm lựa chọn để kết thúc cập nhật
            cout << "Enter your choice: ";
            cin >> partChoice;
            cin.ignore();

            switch (partChoice) {
            case 1: {
                string newPhone;
                cout << "Enter new phone number: ";
                getline(cin, newPhone);
                setPhone(newPhone);
                break;
            }

            case 2: {
                string newEmail;
                cout << "Enter new email: ";
                getline(cin, newEmail);
                setEmail(newEmail);
                break;
            }

            case 3: {
                string password, confirmPass;  
                cout<< "Enter old password:\t";
                password = hidenPass();
                if(this->pass == password){
                    cout << "Enter new password:\t";
                    password = hidenPass();
                    int todo = 1,maxTry = 3;

                    while (todo < maxTry) {
                        cout << "Confirm new password: ";
                        confirmPass = hidenPass();
                        if (password == confirmPass) {
                            setPass(password);
                            cout << "Password set successfully!" << endl;
                            break;
                        } else {
                            todo++;
                            if (todo < maxTry) {
                                cout << "Passwords do not match. Please try again!" << endl;
                            } else {
                                cout << "Maximum attempts reached. Password not set." << endl;
                            }   

                            }
                    }
                }else{
                    cout<<"Wrong old password, so you can't reset password!"<<endl;
                }
            }

            case 4: {
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


string Customer::getAddress() {
    return address;
}

Customer* Customer::getCusById(const string& cusID) {
    for (person *p : obj) {
     Customer* cus = dynamic_cast<Customer*>(p);
     if(cus){
        if (cus->getID() == cusID) {
            return cus; // Trả về con trỏ đến đối tượng Customer nếu tìm thấy
        }
     }
        
    }
return nullptr; // Trả về nullptr nếu không tìm thấy
}
string Customer::generateID() {
        
        stringstream ss;
        ss <<"CS"<< setw(5) << setfill('0') << nextCusID++; 
        return ss.str();
    }


void Customer::saveToFile(const string& fileName)  {
    ofstream file(fileName); // Mở file
    if (!file) { // Kiểm tra xem file có mở thành công không
        cerr << "Can not open file !\n";
        return;
    }
    // hàm này thiếu những trường khác của cus so với person. nên override lại từ person.h
   for (person* p : obj) {
    // Chuyển đổi đối tượng thành Customer* nếu có thể
    Customer* customer = dynamic_cast<Customer*>(p);
    if (customer) {
        // Nếu chuyển đổi thành công, nghĩa là person là đối tượng Customer
        file << customer->getID() << ", "
             << customer->getName() << ", "
             << customer->getPhone() << ", "
             << customer->getEmail() << ", "
             << customer->getPass() << ", "
             << customer->getRole() << ", "
             << customer->getAddress() << ", "<<endl;
    }
    }
file.close();
}
    
int Customer::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        return 0; // Trả về 0 nếu không mở được file
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string _customerID, _address, _name, _phone, _email, _password,_role;

        getline(ss, _customerID, ',');
        getline(ss, _name, ',');
        getline(ss, _phone, ',');
        getline(ss, _email, ',');
        getline(ss, _password,',');
        getline(ss, _role, ',');
        getline(ss, _address);

        try {
            // Kiểm tra tính hợp lệ của tên (chỉ chứa chữ cái và khoảng trắng)
            if (!all_of(_name.begin(), _name.end(), [](char c) { return isalpha(c) || isspace(c); })) {
                return 0; 
            }

            // Kiểm tra tính hợp lệ của số điện thoại (chỉ chứa số)
            if (!all_of(_phone.begin(), _phone.end(), ::isdigit)) {
                return 0; 
            }

            // Kiểm tra tính hợp lệ của email
            const regex emailPattern(R"((\w+)(\.\w+)*@(\w+\.)+\w+)");
            if (!regex_match(_email, emailPattern)) {
                return 0; 
            }

            Customer* newCustomer = new Customer( _name, _phone, _email, _password, _address);
        } 
        catch (const out_of_range&) {
            return 0; // Trả về 0 nếu gặp lỗi ngoài phạm vi
        }
    }

    file.close();
    return 1; // Trả về 1 nếu thành công
}



void Customer::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(15) << getPhone()
        << setw(20) << getAddress() << endl; // Thêm địa chỉ
}
void Customer::setAddress(const string& add){
    this->address = add;
}

void Customer::setInfor() {
    string t_address, t_name, t_phone, t_email;

    cout << "Enter the full name: ";
    getline(cin, t_name);
    setName(t_name); 

    cout << "Enter the phone number: ";
    getline(cin, t_phone);
    setPhone(t_phone);
    cout << "Enter the email: ";
    getline(cin, t_email);
    setEmail(t_email); 
    cout << "Enter the address: ";
    getline(cin, t_address);
    setAddress(t_address); 
}
int Customer::deleteCustomer(){
     auto it = find(obj.begin(), obj.end(), this);
    if (it != obj.end()) {
        obj.erase(it);
        delete this;// giai phong bo nho cho this
    }
    return 1;
}

