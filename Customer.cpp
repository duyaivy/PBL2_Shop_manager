
#include "./header/Customer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "./header/vector.h"
#include <algorithm>
#include <iomanip>
#include "./header/InvoiceDetail.h"
using namespace std;
static int nextCusID = 1;

Customer::Customer(const string& _name, const string& _phone, const string& _email, const string& _password, const string& _address)
    : Person(_name, _phone, _email, _password, "CUSTOMER"),  address(_address) {
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
    for (Person *p : Person::obj) {
        if (p->getID() == cusID) {
            Customer* cus = dynamic_cast<Customer*>(p);
            return cus; // Trả về con trỏ đến đối tượng Customer nếu tìm thấy
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
    ofstream file(fileName, ios::trunc);
    if (!file) { 
        cerr << "Can not open file !\n";
        return;
    }
   
   for (Person* p : Person::obj) {
    Customer* customer = dynamic_cast<Customer*>(p);
    if (customer) {
        // Nếu chuyển đổi thành công, nghĩa là Person là đối tượng Customer
        file << customer->getID() << ", "
             << customer->getName() << ", "
             << customer->getPhone() << ", "
             << customer->getEmail() << ", "
             << customer->getPass() << ", "
             << customer->getAddress();

             for(string invoice: customer->idInvoice){
             file<<","<<invoice;
            }
            for(string cart: customer->idCart){
             file<<","<<cart;
            }
            file<<endl;
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
        string _customerID, _name, _phone, _email, _password, _address, _id;

        getline(ss, _customerID, ',');
        getline(ss, _name, ',');
        getline(ss, _phone, ',');
        getline(ss, _email, ',');
        getline(ss, _password,',');
        getline(ss, _address,',');
        getline(ss, _id,',');


        try {
            Customer* newCustomer = new Customer( _name, _phone, _email, _password, _address);
            Person::obj.push_back(newCustomer);
            if(_id!= "") {
                if(_id.find("DE") != string::npos){
                 newCustomer->addCaft(_id);    
                }else{
                    newCustomer->addInvoice(_id);
                }
            
            }
            // add het _id cua person
            while(getline(ss,_id,',')){
                if(_id.find("DE") != string::npos){
                 newCustomer->addCaft(_id);    
                }else{
                    newCustomer->addInvoice(_id);
                }
            }

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
    auto it = find(Person::obj.begin(), Person::obj.end(), this);
    if (it != Person::obj.end()) {
        Person::obj.erase(it);
        delete this;// giai phong bo nho cho this
    }
    return 1;
}
void Customer::printTableHeader() { 
    cout << left << setw(10) << "ID"
         << setw(20) << "Full Name"
         << setw(30) << "Email"
         << setw(15) << "Phone"
         << setw(20) << "Address" // Thêm cột "Address"
         << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
}

int Customer:: regis(){
    string t_name, t_phone, t_email, t_address;
    cout << "Enter the full name: ";
    getline(cin, t_name);
    
    cout << "Enter the phone number: ";
    getline(cin, t_phone);
   
    cout << "Enter the email: ";
    getline(cin, t_email);
   
    cout << "Enter the address: ";
    getline(cin, t_address);
    
    string password, confirmPass;  
                
               
    cout << "Enter your password:\t";
    password = Person::hidenPass();
    while (1) {
        cout << "Confirm your password: ";
            confirmPass = hidenPass();
            if (password == confirmPass) {
                    break;
            } else {
                continue;
            }
                    
    }
    //Customer( const string& _password, const string& _address)
    Customer *c = new Customer(t_name, t_phone, t_email, password, t_address);
    Person::obj.push_back(c);
    cout<<"Register Sucessfully!\nHere is your infor to Login\n";
    cout << left << setw(15) << "Phone:" << setw(10) << c->getPhone() << endl
        << left << setw(10) << "Password:" << setw(20) << c->getPass() << endl;
     system("pause");
    return 1;
    
}

int Customer::addCaft(string cart){
    this->idCart.push_back(cart);
    return 1;
}
int Customer::getInforCart(){
    for(string cart: this->idCart){
        InvoiceDetail *dt = InvoiceDetail::getDetailByID(cart);
        if(dt!= nullptr){
            dt->getInfor(dt);
        }
    }
    return 1;
}
int Customer::getInforInvoice(){
    for(string invoice: this->idInvoice){
        Invoice *inv = Invoice::getInvoiceByID(invoice);
        if(inv!= nullptr){
            inv->getInfor(inv);
        }
    }
    return 1;
}