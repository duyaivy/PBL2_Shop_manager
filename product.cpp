#include "product.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

string product::generatePrdID() {
        
        stringstream ss;
        ss <<"PD"<< setw(5) << setfill('0') << nextPrdID++; 
        return ss.str();
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
        cout << left << setw(15) << "ID:" << setw(15) << p->productID << endl
             << left << setw(15) << "Name:" << setw(20) << p->prdName << endl
             << left << setw(15) << "Brand:" << setw(30) << p->prdBrand << endl
             << left << setw(15) << "Detail:" << setw(50) << p->prdDetail << endl
             << left << setw(15) << "Price:" << formatCurrency(p->unitPrice)  <<endl
             << left << setw(15) << "Quantity:" << setw(15) << p->quantity << endl
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
    int right = prd.getSize() - 1;
    
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


int product::deletePrd(){
    auto it = find(prd.begin(), prd.end(), this);
    if (it != prd.end()) {
        prd.erase(it);
        delete this;// giai phong bo nho cho this
    }
    return 1;
}


void product:: displayPrd(){
    for (product* product : prd) {
            product->getInfor(product);
        }
}

// Hàm chuyển chuỗi về chữ thường
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
// hàm tìm kiếm bằng từ khoá nếu tên là "nguyen van a" nếu tham số truyền vào là "van a" thì vẫn tìm được và in ra
int product::searchByName(string word) {
    string lowerWord = toLowerCase(word); 
    int cnt=0;//dung bien cnt de luu ket qua tra ve 1 neu tim thay va 0 neu khong tim thay;
        for (product* p : prd) {
            string lowerName = toLowerCase(p->prdName);
           if (lowerName.find(lowerWord) != std::string::npos) {
           // xuli sau khi tim thay
           cnt++; 
           product::getInfor(p);
            }
        }
return (cnt!= 0 ) ? 1:0;
}
int product::searchByBrand(string brand ){
   string lowerBrand = toLowerCase(brand); 
    int cnt=0;//dung bien cnt de luu ket qua tra ve 1 neu tim thay va 0 neu khong tim thay;
        for (product* p : prd) {
            string lowerName = toLowerCase(p->prdBrand);
           if (lowerName.find(lowerBrand) != std::string::npos) {
           // xuli sau khi tim thay
           cnt++; 
           product::getInfor(p);
            }
        }
return (cnt!= 0 ) ? 1:0;
}

int product::saveToFile(string fileName) {
        ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return 0;
        }
        for (product *p: prd) {
            file << p->productID << "," << p->prdName << ","<< p->prdBrand<<"," << p->prdDetail << "," << p->unitPrice << "," << p->quantity << endl;
        }
        file.close();
        return 1;
}

int product::loadFromFile(string fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error opening file for reading.\n";
            return 0;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, brand, detail, price,quantity;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, brand, ',');
            getline(ss, detail, ',');
            getline(ss, price, ',');
            getline(ss, quantity);

        // kiem tra gia tri co hop le hay khong
         try {
            long long priceValue = stoll(price);
            int quantityValue = stoi(quantity);        
            if (priceValue < 0 || quantityValue < 0) {
                return 0; 
            }
            new product(name, brand, detail, priceValue,quantityValue);
        }    catch (const std::invalid_argument& e) {
             return 0; // Trả về 0 nếu gặp lỗi khi chuyển đổi
            }catch (const std::out_of_range& e) {
            return 0; 
            }
        }
        
        file.close();
return 1;
}
product* product::getPrdByID(const string id){
    for (product *p : prd){
        if (p->getPrdID() == id){   
            return p;
        }
    }
return nullptr; 
}
void product::printInfor(){
 cout << left << setw(10) << "ID:" << setw(10) << productID << endl
    << left << setw(10) << "Name:" << setw(20) << prdName << endl
    << left << setw(10) << "Brand:" << setw(30) << prdBrand << endl
    << left << setw(10) << "Detail:" << setw(50) << prdDetail << endl
    << left << setw(10) << "Price:" << formatCurrency(unitPrice)  <<endl
    << left << setw(10) << "Quantity:" << setw(10) << quantity << endl
    << "----------------------------------------" << endl;
}

// get 
string product::getPrdID(){
    return productID;
    }
string product::getPrdName(){
    return prdName;
    }
string product::getPrdBranch(){
    return prdBrand;
    }
string product::getPrdDetail(){
    return prdDetail;
    }
long long product::getUnitPrice(){
    return unitPrice;
    }
int product::getQuantity(){
    return quantity;
    }