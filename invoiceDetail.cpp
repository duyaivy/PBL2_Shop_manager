#include "invoiceDetail.h"
#include "product.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

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
invoiceDetail::invoiceDetail(const string invoiceID, const int quantity,const string prdID){
        this->detailID = generateDetailID();
        this->invoiceID = invoiceID; 
        this->quantity = quantity;
        this->prdID = prdID;
        long long money = 0;
        if(product::getPrdByID(prdID)){
        money = product::getPrdByID(prdID)->getUnitPrice();
        }
        this->price = quantity*money;
        detail.push_back(this);
    }

string invoiceDetail::generateDetailID(){
        stringstream ss;
        ss <<"DE"<< setw(5) << setfill('0') << nextDetailID++; 
        return ss.str();
    }
void invoiceDetail:: getInfor(const invoiceDetail *detail){
     cout << left << setw(15) << "Detail ID:" << setw(15) << detail->detailID << endl
        << left << setw(15) << "Invoice ID:" << setw(15) << detail->invoiceID << endl
        << left << setw(15) << "Product ID" << setw(15) << detail->prdID << endl
        << left << setw(15) << "Quantity:" << setw(15) << detail->quantity << endl
        << left << setw(15) << "Price:" << formatCurrency(detail->price)  <<endl
        << "----------------------------------------" << endl;
    }
void invoiceDetail:: setQuantity(int number){
    quantity = number;
    price = quantity* product::getPrdByID(prdID)->getUnitPrice();// sua lai tong gia tien 
}
invoiceDetail* invoiceDetail:: getDetailByID(string id ){
    for (invoiceDetail *dt : detail){
        if (dt->getDetailID() == id){   
            return dt;
        }
    }
return nullptr; 
}
void invoiceDetail:: deleteDetail(){
 auto it = find(detail.begin(), detail.end(), this);
    if (it != detail.end()) {
        detail.erase(it);
        delete this;// giai phong bo nho cho this
    }
}
void invoiceDetail:: displayDetail(){
    for(invoiceDetail *dt: detail){
        invoiceDetail::getInfor(dt);
    }
}
int invoiceDetail:: saveToFile(string fileName){
     ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return 0;
        }
        for (invoiceDetail *dt : detail) {
            file << dt->detailID << "," << dt->invoiceID << ","<< dt->prdID<<"," << dt->quantity << "," << dt->price<< endl;
        }
        file.close();
        return 1;
}
int invoiceDetail:: loadFromFile(string fileName){
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
            new invoiceDetail(invoiceId,quantityValue,prdId);
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
string invoiceDetail::getDetailID(){
    return detailID;
}
string invoiceDetail::getInvoiceID(){
    return invoiceID;
}
string invoiceDetail::getPrdID(){
    return prdID;
}
int invoiceDetail::getQuantity(){
    return quantity;
}
long long invoiceDetail::getPrice(){
    return price;
}