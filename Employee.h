#ifndef EMPLOYEE_H 
#define EMPLOYEE_H

#include "person.h"
#include "Customer.h"
#include <vector>
#include <string>
using namespace std;

class Employee : public person {
protected:// ở đây không có role nữa, đã có role ở person ròi thì đây có thêm làm gì?
// đã nói từhoom trước và thống nhất rồi mà?
    string role;
public:
// Phải xây dựng hàm tạo theo cấu trúc tạo của person, những giá trị khác có mới ở employee thì để ở phía sau
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password);

    void display() override;
    void updateInfo();
    // lỗi tương tự cus.h
    static void saveToFile(const vector<person*>& persons, const string& filename); 
    static void loadFromFile(const string& filename, vector<person*>& persons); 
    string getRole() const;
    //ở đây chỉ có một vector để lưu person thôi. Trong đó đã khai báo ở persion.h rồi thì ở đây lấy tham số truyền vào là vector để làm gì?
    // nó chỉ truyền vào khi có nhiều vector giống nhau, hạn chế code truyền vào như thế này. Sửa lại nhé
    void manageCustomers(vector<person*>& persons);
    void manageEmployees(vector<person*>& persons);
    static std::string getUserRole();
    static void handleManagerMenu(Employee& manager, vector<person*>& persons); 
    static void displaySalesCustomers(const vector<person*>& persons); 
    static void handleUserRole(string role, vector<person*>& persons); 
    void setInfor(person& a) override;

private:
// tương tự trên sửa hết lại tham số truyền vào!
// những hàm như searchbyID thì tham số truyền vào là ID , trả về kiểu int 0 nếu không tìm thấy và 1 nếu tìm thấy. Tham khảo code của t.
    void searchCustomerByID(const vector<person*>& persons);
// tương tự những hàm add, delete,... cũng phải truyền vào là 1 string id của đối tượng đó. từ string đó get..ById để trả về con trỏ rồi lấy con trỏ đó mà làm việc!
// kiểu trả vê là 0 hoặc 1 
    void addCustomer(vector<person*>& persons);
    void deleteCustomer(vector<person*>& persons);
    void editCustomer(vector<person*>& persons);
    void addEmployee(vector<person*>& persons);
    void updateEmployee(vector<person*>& persons);
    void deleteEmployee(vector<person*>& persons);
    void editEmployee(vector<person*>& persons);
    
    void addCustomersFromFile(const string& fileName, vector<person*>& persons);
    // đã có class product nên ở đây xây dựng thêm để quản lí product nữa, tạo, thêm, sửa, xoá.
    
};

#endif
