#include "./header/Product.h"
#include"./header/global.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
vector<Product*> Product::prd;

string Product::generatePrdID() {
        
        stringstream ss;
        ss <<"PD"<< setw(5) << setfill('0') << nextPrdID++; 
        return ss.str();
    }
// format VND cho price
// static string formatCurrency(long long number) {
//     stringstream ss;
//     string result;
//     ss << number; 
//     string strNumber = ss.str();
//     int len = strNumber.length();
//     int count = 0;
//     for (int i = len - 1; i >= 0; --i) {
//         result.insert(0, 1, strNumber[i]);
//         count++;
//         if (count == 3 && i != 0) {
//             result.insert(0, 1, '.'); 
//             count = 0;
//         }
//     }
//     result += "VND";    
//     return result;
// }
// chuyen prdID string -> int
int convertStringToInt(const string& str) {
    string numberPart = str.substr(2);
    return stoi(numberPart);
}
Product::Product(const string name ,const string brand ,const string detail,const long long unitPrice,const long long importPrice , const int quantity,const int qntSell, const bool isDelete){
    productID = generatePrdID();
    prdBrand = brand; prdName = name;
    prdDetail = detail;
    this->quantity = quantity; 
    this->qntSell = qntSell;
    this->unitPrice = unitPrice;
    this->importPrice = importPrice;
    this->isDelete = isDelete;    
}
void Product::getInfor(const Product *p){
        // cout << left << setw(15) << "ID:" << setw(15) << p->productID << endl;
        if(p->isDelete) return;
        cout<< left << setw(18) << "Name:" << setw(20) << p->prdName << endl
             << left << setw(18) << "Brand:" << setw(30) << p->prdBrand << endl
             << left << setw(18) << "Detail:" << setw(50) << p->prdDetail << endl
             << left << setw(18) << "Price:" << formatCurrency(p->unitPrice)  <<endl
             << left << setw(18) << "Quantity remain:" << setw(20) << p->quantity - p->qntSell << endl
             << "----------------------------------------" << endl;
}

void Product::getInforToManager(const Product *p){
        if(p->isDelete) return;
        cout << left << setw(18) << "ID:" << setw(18) << p->productID << endl
             << left << setw(18) << "Name:" << setw(20) << p->prdName << endl
             << left << setw(18) << "Brand:" << setw(30) << p->prdBrand << endl
             << left << setw(18) << "Detail:" << setw(50) << p->prdDetail << endl
             << left << setw(18) << "UnitPrice:" << formatCurrency(p->unitPrice)  <<endl
             << left << setw(18) << "ImportPrice:" << formatCurrency(p->importPrice)  <<endl
             << left << setw(18) << "Quantity sold:" << setw(20) << p->qntSell << endl
             << left << setw(18) << "Quantity remain:" << setw(20) << (p->quantity) - (p->qntSell) << endl
             << "----------------------------------------" << endl;
}
void Product::setInfor(Product *p){
    cout<<"Enter Name Product:";
    getline(cin,p->prdName);
    cout<<"Enter Brand:";
    getline(cin,p->prdBrand);
    cout<<"Enter Details:";
    getline(cin,p->prdDetail);
    cout<<"Enter unitPrice:";
    cin>>p->unitPrice;
    cout<<"Enter InportPrice:";
    cin>>p->importPrice;
    cout<<"Enter quantity sold:";
    cin>>p->qntSell;
    cout<<"Enter Quantity:";
    cin>>p->quantity;
    }
void Product::setQuantity( const int count){
    this->quantity = count;
}
void Product::setUnitPrice(const long long price){
    this->unitPrice = price;
}
// tim kiem nhi phan
int Product::searchByID(string ID){
    // int id = convertStringToInt(ID);
    //  int left = 0;
    // int right = prd.getSize() - 1;
    
    // while (left <= right) {
    //     int mid = left + (right - left) / 2;
    //     int currentID = convertStringToInt(prd[mid]->productID);  // Lấy ID của Product tại vị trí giữa
        
    //     if (currentID == id) {
    //         // In ra thông tin sản phẩm khi tìm thấy
    //         cout<<"Found!!"<<endl;
    //         prd[mid]->getInfor(prd[mid]);
    //         return 1;  // Tìm thấy
    //     }
        
    //     if (currentID < id) {
    //         left = mid + 1; 
    //     } else {
    //         right = mid - 1; 
    //     }
    // }
    for(Product *p : prd){
        if(p->getPrdID() == ID){
            p->getInfor(p);
            return 1;
        }
    }
    return 0;
}


bool Product::deletePrd(){
    // auto it = find(prd.begin(), prd.end(), this);
    // if (it != prd.end()) {
    //     prd.erase(it);
    //     delete this;// giai phong bo nho cho this
    // }
    this->isDelete = 1;
    return 1;
}


void Product:: displayAllPrd(){
    for (Product* Product : prd) {
            Product->getInfor(Product);
        }
}
void Product:: displayAllPrdToManager(){
    for (Product* Product : prd) {
            Product->getInforToManager(Product);
        }
}



// Hàm chuyển chuỗi về chữ thường

// hàm tìm kiếm bằng từ khoá nếu tên là "nguyen van a" nếu tham số truyền vào là "van a" thì vẫn tìm được và in ra
int Product::searchByName(string word) {
    string lowerWord = toLowerCase(word); 
    int cnt=0;//dung bien cnt de luu ket qua tra ve 1 neu tim thay va 0 neu khong tim thay;
        for (Product* p : prd) {
            string lowerName = toLowerCase(p->prdName);
           if (lowerName.find(lowerWord) != std::string::npos) {
           // xuli sau khi tim thay
           cnt++; 
           Product::getInfor(p);
            }
        }
return (cnt!= 0 ) ? 1:0;
}
int Product::searchByBrand(string brand ){
   string lowerBrand = toLowerCase(brand); 
    int cnt=0;//dung bien cnt de luu ket qua tra ve 1 neu tim thay va 0 neu khong tim thay;
        for (Product* p : prd) {
            string lowerName = toLowerCase(p->prdBrand);
           if (lowerName.find(lowerBrand) != std::string::npos) {
           // xuli sau khi tim thay
           cnt++; 
           Product::getInfor(p);
            }
        }
return (cnt!= 0 ) ? 1:0;
}

int Product::saveToFile(string fileName) {
        ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file product for writing.\n";
            return 0;
        }
        for (Product *p: prd) {
            file << p->productID << "," << p->prdName << ","<< p->prdBrand<<"," << p->prdDetail << "," << p->unitPrice << "," << p->importPrice << "," << p->quantity<< "," << p->qntSell <<"," << p->isDelete<< endl;
        }
        file.close();
        return 1;
}

int Product::loadFromFile(string fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error opening file for reading.\n";
            return 0;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, brand, detail, price, importPrice,quantity,qntSell,isDelete;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, brand, ',');
            getline(ss, detail, ',');
            getline(ss, price, ',');
            getline(ss, importPrice, ',');
            getline(ss, quantity, ',');
            getline(ss, qntSell, ',');
            getline(ss, isDelete);

        // kiem tra gia tri co hop le hay khong
         try {
            long long priceValue = stoll(price);
            int quantityValue = stoi(quantity);
            long long importPriceValue = stoll(importPrice);
            int qntSellValue = stoi(qntSell);        
            if (priceValue < 0 || quantityValue < 0) {
                return 0; 
            }
             if (importPriceValue < 0 || qntSellValue < 0) {
                return 0; 
            }
            bool del = (isDelete == "1")?  true: false;
            Product *p = new  Product(name, brand, detail, priceValue,importPriceValue,quantityValue,qntSellValue, del);
            prd.push_back(p);
        }    catch (const std::invalid_argument& e) {
             return 0; // Trả về 0 nếu gặp lỗi khi chuyển đổi
            }catch (const std::out_of_range& e) {
            return 0; 
            }
        }
        
        file.close();
return 1;
}
Product* Product::getPrdByID(const string id){
    for (Product *p : prd){
        if (p->getPrdID() == id){   
            return p;
        }
    }
return nullptr; 
}
void Product::printInfor(){
    if(this->isDelete) return;
 cout << left << setw(10) << "ID:" << setw(10) << productID << endl
    << left << setw(10) << "Name:" << setw(20) << prdName << endl
    << left << setw(10) << "Brand:" << setw(30) << prdBrand << endl
    << left << setw(10) << "Detail:" << setw(50) << prdDetail << endl
    << left << setw(10) << "Price:" << formatCurrency(unitPrice)  <<endl
    << left << setw(10) << "Quantity:" << setw(10) << quantity << endl
    << "----------------------------------------" << endl;
}
void Product::handleThisProduct(){
    while (1)
    {
        system("cls");
        cout << "--- Handle Product " << this->getPrdName() << " ---\n\n";
        int chosse;
        cout << "Select 1 action:\n";
        cout << "1. View all information.\n";
        cout << "2. Edit this product.\n";
        cout << "3. Delete this product.\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> chosse;
        cin.ignore();
        if (chosse == 0)
        {
            system("pause");
            return;
        }
        switch (chosse)
        {
        case 1:
        {
            cout << "Product " << this->getPrdName() << "'s all infor.\n";
            this->getInforToManager(this);
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Edit Product " << this->getPrdName() << "\n";
            Product::setInfor(this);
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Delete Product " << this->getPrdName() << "'s invoice.\n";
            this->deletePrd();
            system("pause");
            break;
        }
        default:
        {
            cout << "Invalid\n";
            system("pause");
            break;
        }
        }
    }
}

// get 
string Product::getPrdID(){
    return productID;
    }
string Product::getPrdName(){
    return prdName;
    }
string Product::getPrdBranch(){
    return prdBrand;
    }
string Product::getPrdDetail(){
    return prdDetail;
    }
long long Product::getUnitPrice(){
    return unitPrice;
    }
int Product::getQuantity(){
    return quantity;
    }
    
void Product::setImportPrice(long long price){
    this->importPrice = price;
}
void Product::setQuantitySell(int qnt){
    this->qntSell = qnt;

}
void Product::setDelete(bool del){
    this->isDelete = del;

}
long long Product::getImportPrice(){
    return importPrice;
}
int Product::getQuantitySell(){
    return qntSell;
}
bool Product::getDelete(){
    return isDelete;
}

static vector<Product*> getProducts(){
    return Product::prd;
}