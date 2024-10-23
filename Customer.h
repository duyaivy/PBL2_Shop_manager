#ifndef CUSTOMER_H
#define CUSTOMER_H
// lỗi phần khai báo tương tự person.h
#include "person.h"
#include <vector>
#include <string>
#include <fstream>
// ở đây nếu muốn sử dụng thành phần trong class khác thì nên khai báo nguyên mẫu class, như sau:
// class person; sau đó qua file.cpp để include class đó vào. Không nên include các file .h với nhau dễ gây bug xung đột
using namespace std;
// phần protected ở đâu? Phải bám vào phần cơ sở dũ liệu dã thiết kế để làm chứ?
class Customer : public person {
public:
    Customer(const string& name, const string& phone, const string& email, const string& password);

    void updateInfo();
    // đổi lại vị trí tham chiếu để 2 hàm save và load tương tự nhau,string file name rồi tới vector.
    // hàm save, load, display nên override từ person.h
    static void saveToFile(const vector<person*>& persons, const string& filename);
    static void loadFromFile(const string& fileName, vector<person*>& persons); // Thay đổi vector thành vector<person*>);
    void display();// thiếu từ khoá override
    void setInfor(person& a) override;
    // thiếu hàm getCusById() tham số truyền vào là string id của cus đó, trả về nullptr nếu không có, nếu có trả về con trỏ trỏ tới cus đó
    // hàm này t đã gửi mẫu qua zalo và có nói rồi sao vẫn chưa làm?
};

#endif
