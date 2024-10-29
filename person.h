#ifndef PERSON_H
#define PERSON_H

class person {
protected:
    string ID, name, phone, email, pass, role;
    virtual string generateID() = 0;
public:

    person(const string& _name, const string& _phone, const string& _email, const string& _pass, const string& _role = "CUSTOMER");

    static void clearPerson();
    virtual void display() = 0;//ham ao
    // phải sửa lại các hàm setName, set.... để tái sử dụng lại khi làm giao diện. 
    // Những hàm này phải có tham số truyền vào là một string, trong hàm chỉ làm việc set từ string truyền vào thôi. 
    string getName(); void setName(const string&);
    string getID(); string getRole();
    string getPhone(); void setPhone(const string& );
    string getEmail(); void setEmail(const string&);
    string getPass(); void setPass(const string&); string hidenPass();
    virtual void setInfor() = 0;  static void printTableHeader(); // ham ao
    static void printInfor(const person* person);
    static int login(string id, string pw, person* p);
    
    // virtual int loadFromFile(const string& filename)=0;
    // virtual void saveToFile(const string& filename)=0;
};
static vector<person*> obj;
#endif