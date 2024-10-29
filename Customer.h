
#ifndef CUSTOMER_H
#define CUSTOMER_H
// lỗi phần khai báo tương tự person.h
#include <vector>
#include <string>
#include <fstream>
#include "person.h"
// ở đây nếu muốn sử dụng thành phần trong class khác thì nên khai báo nguyên mẫu class, như sau:
// class person; sau đó qua file.cpp để include class đó vào. Không nên include các file .h với nhau dễ gây bug xung đột
using namespace std;
// phần protected ở đâu? Phải bám vào phần cơ sở dũ liệu dã thiết kế để làm chứ?
class Customer : public person {
protected:
    
    string generateCusID();
    string address;
    static int nextCusID;
public:
    Customer( const string& _address, const string& name, const string& phone, const string& email, const string& password);
    void updateInfo();
    string getIDcus();
    string getAddress();
    // đổi lại vị trí tham chiếu để 2 hàm save và load tương tự nhau,string file name rồi tới vector.
    // hàm save, load, display nên override từ person.h
    static void saveToFile(const string& filename)    ;
    static int loadFromFile(const string& fileName) ; // Thay đổi vector thành vector<person*>);
    void display() override;
    void setInfor(person& a) override;
    static Customer*getCusById(const string&);
    // thiếu hàm getCusById() tham số truyền vào là string id của cus đó, trả về nullptr nếu không có, nếu có trả về con trỏ trỏ tới cus đó
    // hàm này t đã gửi mẫu qua zalo và có nói rồi sao vẫn chưa làm?
};
static vector<Customer*> list;
#endif