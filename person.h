#include <string>
#include<iostream>
#include <iomanip>
#include<vector>
using namespace std;



class person{
    private:
    string personID, name, phone, email, pass;
    static int nextID;
    string generateID(); 
    static vector<person*> obj;
    public:
    person(const string _name,const string _phone ,const string _email,const string _pass);
    // ~person();
    
    void display();
    string getName(person& a); void setName(); 
    string getID(person& a);  
    string getPhone(person& a); void setPhone(person& a); 
    string getEmail(person& a); void setEmail(person& a); 
    string getPass(person& a); void setPass(person& a); 
    void printInfor(const person* person);


};
string person::generateID() {
        // Chuyển nextID thành chuỗi có 7 chữ số, thêm số 0 ở phía trước
        stringstream ss;
        ss << setw(7) << setfill('0') << nextID;
        nextID++; // Tăng nextID lên 1 cho người kế tiếp
        return ss.str();// trả về giá trị
    }

// people.push_back(this);
person::person(const string _name,const string _phone ,const string _email,const string _pass){
    setName();
    personID = generateID();
    obj.push_back(this); 
    
}
string person::getName(person& a){
    return a.name;
}
void person::setName(){
    cout<<"Enter Fullname:"<<endl;
    getline(cin,name);
}; 
string person::getID(person& a){
    return a.personID;
}
string person::getPhone(person& a){
    return a.phone;
}
void person::setPhone(person& a){
    cout<<"Enter Phone number:"<<endl;
    getline(cin,a.phone);
}; 
string person::getEmail(person& a){
    return a.email;
}
void person::setEmail(person& a){
    cout<<"Enter Fullname:"<<endl;
    getline(cin,a.email);
}; 
string person::getPass(person& a){
    return a.pass;
}
void person::setPass(person& a){
    cout<<"Enter your password:"<<endl;
    getline(cin,a.pass);
};
void person::display(){
    for (person* person : obj) {
            printInfor(person);
        }
}
void person::printInfor(const person* a)  {
        cout << left << setw(10) << "ID:" << setw(10) << a->personID << endl
             << left << setw(10) << "FullName:" << setw(20) << a->name << endl
             << left << setw(10) << "Email:" << setw(30) << a->email << endl
             << left << setw(10) << "Phone:" << setw(15) << a->phone << endl
             << "----------------------------------------" << endl;
    }