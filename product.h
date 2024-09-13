#include<iostream>
#include <string>
#include<vector>
#include <iomanip>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;


// get infor 1; create 1 prd; set(update) 1 prd, search by ID, search by name, 
// search by brand; show all; delete 1 prd ; input from csv; thay doi so luong 
// 
class product
{
private:
string productID, prdName,prdBrand,prdDetail;
long long unitPrice;
int quantity;
static int nextPrdID;
string generatePrdID(); 
static vector<product*> prd;
public:
    product(const string name ="unknown",const string brand ="unknown",const string detail="unknown",const long long unitPrice = 0, const int quantity= 0);
    static void getInfor(const product *p);static void setInfor(product&p); 
    void setQuantity( const int count);//thay doi so lương tuy theo tang hay giam
    int searchByID(string id = "" ); 
    int searchByBrand(string brand = "");  int searchByName(string name  = "");
    int deletePrd();static void displayPrd(); 
    void setUnitPrice(const long long price);static int inputFromCSV();
    
};
string product::generatePrdID() {
        // Chuyển nextID thành chuỗi có 7 chữ số, thêm số 0 and PD ở phía trước
        stringstream ss;
        ss <<"PD"<< setw(5) << setfill('0') << nextPrdID++; // Tăng nextID lên 1 -> kế tiếp
        return ss.str();// trả về giá trị
    }
// format VND cho price
static string formatCurrency(long long number) {
    stringstream ss;
    string result;
    ss << number;     
    string strNumber = ss.str();
    int len = strNumber.length();
    int count = 0;
    for (int i = len - 1; i >= 0; --i) {
        result.insert(0, 1, strNumber[i]);
        count++;
        if (count == 3 && i != 0) {
            result.insert(0, 1, '.'); 
            count = 0;
        }
    }
    result += "VND";    
    return result;
}
// chuyen prdID string -> int
int convertStringToInt(const string& str) {
    string numberPart = str.substr(2);
    return stoi(numberPart);
}
product::product(const string name ,const string brand ,const string detail,const long long unitPrice , const int quantity){
    productID = generatePrdID();
    prdBrand = brand; prdName = name;
    prdDetail = detail;this->quantity = quantity; this->unitPrice = unitPrice;
    prd.push_back(this);
}
void product::getInfor(const product *p){
        cout << left << setw(10) << "ID:" << setw(10) << p->productID << endl
             << left << setw(10) << "Name:" << setw(20) << p->prdName << endl
             << left << setw(10) << "Brand:" << setw(30) << p->prdBrand << endl
             << left << setw(10) << "Detail:" << setw(50) << p->prdDetail << endl
             << left << setw(10) << "Price:" << formatCurrency(p->unitPrice)  <<endl
             << left << setw(10) << "Quantity:" << setw(10) << p->quantity << endl
             << "----------------------------------------" << endl;

}
void product::setInfor(product &p){
    cout<<"Enter Name Product:";
    getline(cin,p.prdName);
    cout<<"Enter Brand:";
    getline(cin,p.prdBrand);
    cout<<"Enter Details:";
    getline(cin,p.prdDetail);
    cout<<"Enter Price:";
    cin>>p.unitPrice;
    cout<<"Enter Quantity:";
    cin>>p.quantity;
    }
void product::setQuantity( const int count){
    this->quantity = count;
}
void product::setUnitPrice(const long long price){
    this->unitPrice = price;
}
// tim kiem nhi phan
int product::searchByID(string ID ){
    int id = convertStringToInt(ID);
     int left = 0;
    int right = prd.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int currentID = convertStringToInt(prd[mid]->productID);  // Lấy ID của product tại vị trí giữa
        
        if (currentID == id) {
            // In ra thông tin sản phẩm khi tìm thấy
            cout<<"Found!!"<<endl;
            prd[mid]->getInfor(prd[mid]);
            return 1;  // Tìm thấy
        }
        
        if (currentID < id) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }
    
    return 0;

}
int product::searchByBrand(string brand ){
    int cnt = 0;
    for (product* product : prd) {
            if(product->prdBrand == brand){
                product->getInfor(product);
                cnt++;
            }
        }
   return (cnt!= 0 ) ? 1:0;

}
int product::searchByName(string name ){
     int cnt = 0;
    for (product* product : prd) {
            if(product->prdName == name){
                product->getInfor(product);
                cnt++;
            }
        }
   return (cnt!= 0 ) ? 1:0;

}
int product::deletePrd(){
    auto it = find(prd.begin(), prd.end(), this);

    
    if (it != prd.end()) {
        prd.erase(it);
        delete this;// giai phong bo nho cho this
    }
}


void product:: displayPrd(){
    for (product* product : prd) {
            product->getInfor(product);
        }
}
//
int product::inputFromCSV(){

}

