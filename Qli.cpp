#include "Employee.h"
#include "Customer.h"
#include <iostream>
#include <vector>

using namespace std;
// bên person.h đã có 1 vector để chứa cho cả cuss và employee rồi thì ở đây sử dụng nó.
// ngoài ra không nên khai báo những vector chứa ở trong hàm main, khai báo trên hàm main. 
int main() {
    vector<person*> persons;  // Dùng cho cả Customer và Employee

    // Tải dữ liệu từ file CSV cho khách hàng
    Customer::loadFromFile("customers.csv");

    // Tải dữ liệu từ file CSV cho nhân viên
    Employee::loadFromFile("employees.csv");
    // Chuyển đổi kiểu nếu cần

    // Lấy vai trò người dùng
    string role = Employee::getUserRole();

    // Xử lý theo vai trò (Manager hoặc Sales)
    Employee::handleUserRole(role); // Điều chỉnh lại để chỉ cần 2 tham số nếu cần

    // Giải phóng bộ nhớ cho danh sách khách hàng
    for (person* p : persons) {
        delete p;
    }
    persons.clear();

    return 0;
}
