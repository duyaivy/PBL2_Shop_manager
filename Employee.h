#ifndef EMPLOYEE_H 
#define EMPLOYEE_H
#include "product.h"
#include "person.h"
#include "Customer.h"
#include <vector>
#include <string>
using namespace std;

class Employee : public person {
protected:// ở đây không có role nữa, đã có role ở person ròi thì đây có thêm làm gì?
// đã nói từhoom trước và thống nhất rồi mà?
    string generateEmpID();
    static int nextEmpID;
public:
// Phải xây dựng hàm tạo theo cấu trúc tạo của person, những giá trị khác có mới ở employee thì để ở phía sau
    Employee(const string& name, const string& phone, const string& email, const string& role, const string& password);

    void display() override;
    void updateInfo();
    // lỗi tương tự cus.h
    static void saveToFile( const string& filename); 
    static int loadFromFile(const string& filename) ; 
    string getRole() const;
    string getEmpID();
    //ở đây chỉ có một vector để lưu person thôi. Trong đó đã khai báo ở persion.h rồi thì ở đây lấy tham số truyền vào là vector để làm gì?
    // nó chỉ truyền vào khi có nhiều vector giống nhau, hạn chế code truyền vào như thế này. Sửa lại nhé
    void manageCustomers();
    void manageEmployees();
    void manageProduct();
    
    static void handleManagerMenu(Employee& manager); 
    static void displayCustomers(); 
    static void handleUserRole(string role); 
    void setInfor(person& a) override;
    static Employee*getEmpById(const string id);

private:
// tương tự trên sửa hết lại tham số truyền vào!
// những hàm như searchbyID thì tham số truyền vào là ID , trả về kiểu int 0 nếu không tìm thấy và 1 nếu tìm thấy. Tham khảo code của t.
    int searchCustomerByID();
    int searchCustomerByName();
    int searchEmployeeByID();

    
// tương tự những hàm add, delete,... cũng phải truyền vào là 1 string id của đối tượng đó. từ string đó get..ById để trả về con trỏ rồi lấy con trỏ đó mà làm việc!
// kiểu trả vê là 0 hoặc 1 
    int addCustomer();
    int deleteCustomer();
    int editCustomer();
    int addEmployee();
    int updateEmployee();
    int deleteEmployee();
    int editEmployee();
    
    int addCustomersFromFile(const string& fileName);
    // đã có class product nên ở đây xây dựng thêm để quản lí product nữa, tạo, thêm, sửa, xoá.
    int createProduct(const string& name, const string& brand, const string& detail, long long unitPrice, int quantity);
    int deleteProduct(const string productID);
    int editProduct(string newName, string newBrand, string newDetail, long long newunitPrice, int newQuanlity);
    void displayProduct();
    int updateProduct(const string& productID, const string& newName, const string& newBrand, const string& newDetail, long long newUnitPrice, int newQuantity);

    
};


#endif
