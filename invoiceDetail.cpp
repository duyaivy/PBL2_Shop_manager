#include "./header/InvoiceDetail.h"
#include "./header/Product.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
cvector<InvoiceDetail*> InvoiceDetail::detail;

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
InvoiceDetail::InvoiceDetail(const string invoiceID, const int quantity,const string prdID){
        this->detailID = generateDetailID();
        this->invoiceID = invoiceID; 
        this->quantity = quantity;
        this->prdID = prdID;
        long long money = 0;
        
        if(Product::getPrdByID(prdID)!= nullptr){
        money = Product::getPrdByID(prdID)->getUnitPrice();
        }else{
           money = 0;
        }
        this->price = quantity*money;
    }

string InvoiceDetail::generateDetailID(){
        stringstream ss;
        ss <<"DE"<< setw(5) << setfill('0') << nextDetailID++; 
        return ss.str();
    }
void InvoiceDetail:: getInfor(const InvoiceDetail *detail){
     cout << left << setw(15) << "Detail ID:" << setw(15) << detail->detailID << endl
        << left << setw(15) << "Invoice ID:" << setw(15) << detail->invoiceID << endl
        << left << setw(15) << "Product ID" << setw(15) << detail->prdID << endl
        << left << setw(15) << "Quantity:" << setw(15) << detail->quantity << endl
        << left << setw(15) << "Price:" << formatCurrency(detail->price)  <<endl
        << "----------------------------------------" << endl;
    }
void InvoiceDetail:: setQuantity(int number){
    quantity = number;
    price = quantity* Product::getPrdByID(prdID)->getUnitPrice();// sua lai tong gia tien 
}
InvoiceDetail* InvoiceDetail:: getDetailByID(string id){
    for (InvoiceDetail *dt : InvoiceDetail::detail){
        if (dt->getDetailID() == id){   
            return dt;
        }
    }
return nullptr; 
}
void InvoiceDetail:: deleteDetail(){
 auto it = find(detail.begin(), detail.end(), this);
    if (it != detail.end()) {
        detail.erase(it);
        delete this;// giai phong bo nho cho this
    }
}
void InvoiceDetail:: displayDetail(){
    for(InvoiceDetail *dt: InvoiceDetail::detail){
        InvoiceDetail::getInfor(dt);
    }
}
int InvoiceDetail:: saveToFile(string fileName){
     ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return 0;
        }
        for (InvoiceDetail *dt : InvoiceDetail::detail) {
            file << dt->detailID << "," << dt->invoiceID << ","<< dt->prdID<<"," << dt->quantity << "," << dt->price<< endl;
        }
        file.close();
        return 1;
}
int InvoiceDetail:: loadFromFile(string fileName){
    ifstream file(fileName);
        if (!file) {
            cerr << "Error opening file for reading.\n";
            return 0;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string detailId, invoiceId, prdId, quantity, price;
            getline(ss, detailId, ',');
            getline(ss, invoiceId, ',');
            getline(ss, prdId, ',');
            getline(ss, quantity, ',');
            getline(ss,price);

        // kiem tra gia tri co hop le hay khong
         try {
            int quantityValue = stoi(quantity);        
            if (quantityValue < 0) {
                return 0; 
            }
            InvoiceDetail *dt = new InvoiceDetail(invoiceId, quantityValue, prdId);
            detail.push_back(dt);
        }    catch (const std::invalid_argument& e) {
             return 0; // Trả về 0 nếu gặp lỗi khi chuyển đổi
            }catch (const std::out_of_range& e) {
            return 0; 
            }
        }
        
        file.close();
return 1;
}
//get
string InvoiceDetail::getDetailID(){
    return detailID;
}
string InvoiceDetail::getInvoiceID(){
    return invoiceID;
}
string InvoiceDetail::getPrdID(){
    return prdID;
}
int InvoiceDetail::getQuantity(){
    return quantity;
}
long long InvoiceDetail::getPrice(){
    return price;
}