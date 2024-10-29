#ifndef PERSON_H
#define PERSON_H
// chỉ nên include những thư viện cần thiết để tạo 1 class. Những thư viện khi viết code mới dùng thì nên include bên file .cpp
#include <string>
#include <vector>

using namespace std;


class person {
protected:
    string personID, name, phone, email, pass, role;
    static int nextID;
    string generateID();
public:

    person(const string& _name, const string& _phone, const string& _email, const string& _pass, const string& _role);

    static void clearPerson();
    virtual void display() = 0;//ham ao
    // phải sửa lại các hàm setName, set.... để tái sử dụng lại khi làm giao diện. 
    // Những hàm này phải có tham số truyền vào là một string, trong hàm chỉ làm việc set từ string truyền vào thôi. 
    string getName(); void setName(const string&);
    string getID(); string getRole();
    string getPhone(); void setPhone(const string& );
    string getEmail(); void setEmail(const string&);
    string getPass(); void setPass(); string hidenPass();
    virtual void setInfor(person& a) = 0;  static void printTableHeader();// ham ao
    static void printInfor(const person* person);
    static int login(string id, string pw, person* p);
    // thêm hàm ảo load/ save từ file.
    virtual int loadFromFile(const string& filename) ;
    virtual void saveToFile(const string& filename) ;
};
static vector<person*> obj;
static person *currPs;
#endif