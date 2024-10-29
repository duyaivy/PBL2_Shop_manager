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

Customer::Customer( const string& _address, const string& _name, const string& _phone, const string& _email, const string& _password)
    : person(_name, _phone, _email, _password, "unknown"),  address(_address) {};

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
        setInfor(*this);
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
                setPass();
            }

            case 4: {
                continueUpdating = false; // Kết thúc vòng lặp cập nhật
                cout << "Finished updating" << endl;
                break;
            }

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
        break; // Kết thúc case 2
        // xử lí thêm nếu sau khi họ đã sửa xong name, thì nếu họ muốn sửa thêm 1 cái khác nữa, ví dụ êmail thì sao?
        // chả lẽ phải bấm lại từ đầu là chọn sửa 1 phần hay sửa hết, rồi vô từ từ... như vậy phần UX không tốt. refactor lại.
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
    for (Customer* customer : list) {
        if (customer->getIDcus() == cusID) {
            return customer; // Trả về con trỏ đến đối tượng Customer nếu tìm thấy
        }
    }
    return nullptr; // Trả về nullptr nếu không tìm thấy
}
string Customer::generateCusID() {
        
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
    for (Customer* customer : list) {
        file << customer->address << ", "
            << customer->getID() << ", "
            << customer->getName() << ", "
            << customer->getPhone() << ", "
            << customer->getEmail() << ", "
            << customer->getPass() << ", "
            << customer->getRole() << endl;
        file.close();
    }
}


    // chưa thấy tham khảo hàm t viết, phải có những try và catch để bắt lỗi nếu có lỗi về dữ liệu từ file chứ. 
    // vidu dữ liệu từ file là chữ mà nhập vô trong này cần số thì sao?
    
int Customer::loadFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        return 0; // Trả về 0 nếu không mở được file
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string _customerID, _address, _name, _phone, _email, _password;

        getline(ss, _customerID, ',');
        getline(ss, _address, ',');
        getline(ss, _name, ',');
        getline(ss, _phone, ',');
        getline(ss, _email, ',');
        getline(ss, _password);

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

            Customer* newCustomer = new Customer( _address, _name, _phone, _email, _password);
            obj.push_back(newCustomer);
        } 
        catch (const out_of_range&) {
            return 0; // Trả về 0 nếu gặp lỗi ngoài phạm vi
        }
    }

    file.close();
    return 1; // Trả về 1 nếu thành công
}


// chưa overide lại
void Customer::display() {
    cout << setw(10) << getIDcus()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(15) << getPhone()
        << setw(20) << address << endl; // Thêm địa chỉ
}



void Customer::setInfor(person& a) {
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
    address = t_address; 
}


