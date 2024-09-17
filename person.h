#include <string>
#include<iostream>
#include <iomanip>
#include<vector>
#include<conio.h>
using namespace std;



class person{
    private:
    string personID, name, phone, email, pass;
    static int nextID;
    string generateID(); 
    static vector<person*> obj;
    public:
    person(const string _name ="unknown",const string _phone ="unknown",const string _email="unknown",const string _pass="unknown");
    
    static void clearPerson();
    
    static void display();
    string getName(); void setName(); 
    string getID();  
    string getPhone(); void setPhone(); 
    string getEmail(); void setEmail(); 
    string getPass(); void setPass(); string hidenPass();
    static void setInfor(person &a);
    static void printInfor(const person* person);


};
string person::generateID() {
        // Chuy?n nextID thành chu?i có 7 ch? s?, thêm s? 0 ? phía tru?c
        stringstream ss;
        ss << setw(7) << setfill('0') << nextID;
        nextID++; // Tang nextID lên 1 cho ngu?i k? ti?p
        return ss.str();// tr? v? giá tr?
    }

// ham dung constructor
person::person(const string _name,const string _phone ,const string _email,const string _pass){
    name= _name; phone = _phone;
    email = _email; pass = _pass;
    personID = generateID();
    obj.push_back(this); 
    
}
//  ham dung destructor
void person::clearPerson() {
    
    for (person* p : obj) {
        delete p;  // Delete 
    }
    obj.clear();  // Clear the vector
    obj.shrink_to_fit();  
    
}
// name
string person::getName(){
    return name;
}
void person::setName(){
    cout<<"Enter Fullname:";
    getline(cin,name);
}; 

// ID
string person::getID(){
    return personID;
}
// phone
string person::getPhone(){
    return phone;
}
void person::setPhone(){
    cout<<"Enter Phone number:";
    getline(cin,phone);
}; 
// email
string person::getEmail(){
    return email;
}
void person::setEmail(){
    cout<<"Enter your Email:";
    getline(cin,email);
}; 
// pass
// ham hien thi dau * cho pass
string person::hidenPass() {
    string password = "";
    char ch;
    // Ð?c t?ng ký t? cho d?n khi g?p Enter (13)
    while ((ch = _getch()) != 13) {
        if (ch == 8) {  // N?u ngu?i dùng nh?n phím Backspace
            if (!password.empty()) {
                cout << "\b \b";  
                password.pop_back();  
            }
        } else {
            password.push_back(ch);  
            cout << '*';  
        }
    }
    cout << endl;
    return password;
}
string person::getPass(){
    return pass;
}
// void person::setPass(){
//     cout<<"Enter your password:";
//     getline(cin,pass);
// };
void person::setPass(){
    string password, confirmPass;  
    cout << "Enter password:\t";
    password = hidenPass();
    int todo = 1,maxTry = 3;

    while (todo < maxTry) {
        cout << "Confirm password: ";
        confirmPass = hidenPass();
    if (password == confirmPass) {
            pass = password; // Gán m?t kh?u
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
}
 void person::setInfor(person &a){
    a.setName(); 
    a.setPhone();
    a.setEmail();
 }
void person::display() {
    if(obj.empty()){
        cout<<"The program is NULL"<<endl;
    }else{
    for (person* person : obj) {
            printInfor(person);
        }
    }
    
}
void person::printInfor(const person* a)  {
        cout << left << setw(10) << "ID:" << setw(10) << a->personID << endl
             << left << setw(10) << "FullName:" << setw(20) << a->name << endl
             << left << setw(10) << "Email:" << setw(30) << a->email << endl
             << left << setw(10) << "Phone:" << setw(15) << a->phone << endl
             << "----------------------------------------" << endl;
    }