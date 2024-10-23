#include "Customer.h"
#include "person.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

Customer::Customer(const string& name, const string& phone, const string& email, const string& password)
    : person(name, phone, email, password) {}

void Customer::updateInfo() {
    int choice;
    cout << "Choose update option:" << endl;
    cout << "1. Update all information" << endl;
    cout << "2. Update part of information" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();// cái này để làm chi
    switch (choice) {
    case 1:
        cout << "Update all information" << endl;
        setInfor(*this);
        break;
    case 2: {
        int partChoice;
        cout << "Choose part to update" << endl;
        cout << "1. Update phone" << endl;
        cout << "2. Update email" << endl;
        cout << "3. Update pass" << endl;
        cout << "Enter your choice: ";
        cin >> partChoice;
        cin.ignore();

        switch (partChoice) {
        case 1:
            setPhone();
            break;
        case 2:
            setEmail();
            break;
        case 3:
            setPass();
            break;
        }
        break;
        // xử lí thêm nếu sau khi họ đã sửa xong name, thì nếu họ muốn sửa thêm 1 cái khác nữa, ví dụ êmail thì sao?
        // chả lẽ phải bấm lại từ đầu là chọn sửa 1 phần hay sửa hết, rồi vô từ từ... như vậy phần UX không tốt. refactor lại. 
    }
    default:
        cout << "Invalid choice!" << endl; // Thông báo khi nhập không hợp lệ
        break;
    }
}

void Customer::saveToFile(const vector<person*>& persons, const string& fileName) {
    ofstream file(fileName); // Mở file
    if (!file.is_open()) { // Kiểm tra xem file có mở thành công không
        cerr << "Error opening file for writing.\n";
        return;
    }
// hàm này thiếu những trường khác của cus so với person. nên overide lại từ person.h
    for ( person* p : persons) {
         Customer* cust = dynamic_cast< Customer*>(p); // Chỉ lưu thông tin khách hàng
        if (cust) {
            // Ghi thông tin vào file
            file << cust->getID() << ","
                << cust->getName() << ","
                << cust->getPhone() << ","
                << cust->getEmail() << ","
                << cust->getPass() << endl;
        }
    }

    file.close(); // Đóng file
}


void Customer::loadFromFile(const string& fileName, vector<person*>& persons) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    string line;
    // chưa thấy tham khảo hàm t viết, phải có những try và catch để bắt lỗi nếu có lỗi về dữ liệu từ file chứ. vidu dữ liệu từ file là chữ mà nhập vô trong này cần số thì sao?
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, phone, email, password;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password);

        persons.push_back(new Customer(name, phone, email, password));
    }
    file.close();
}
// chưa overide lại
void Customer::display() {
    cout << setw(10) << getID()
        << setw(20) << getName()
        << setw(30) << getEmail()
        << setw(20) << getPhone() << endl;
}

void Customer::setInfor(person& a) {
   Customer& cust = dynamic_cast<Customer&>(a); 
   cust.setName();
   cust.setPhone();
   cust.setEmail();
   cust.setPass();
}

