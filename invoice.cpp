#include"./header/Invoice.h"
#include"./header/InvoiceDetail.h"
#include"./header/Product.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
   
cvector<Invoice*> Invoice::inv;

long long Invoice::calcTotalPrice(){
    long long total = 0;
    for(string dt : this->detailID) {
        if(InvoiceDetail::getDetailByID(dt)){
        total+= InvoiceDetail::getDetailByID(dt)->getPrice();
        }else{
            return -1;
        }
    }
    return total;
}
    
    // return 123456644;


Invoice::Invoice( const string staffID , const string customerID , const string time, const string _detailID){
this->InvoiceID = generateInvoiceID(); 
this->staffID = staffID;
this->customerID = customerID; 
this->time = time;
this->detailID.push_back(_detailID);
this->totalPrice =this->calcTotalPrice();
}
string Invoice::generateInvoiceID(){
        stringstream ss;
        ss <<"IN"<< setw(5) << setfill('0') << nextInvoiceID++; 
        return ss.str();
    }
int Invoice::addDetailID(string dtID){
    if(InvoiceDetail::getDetailByID(dtID)){
        this->detailID.push_back((dtID));// them vao vecto detailID 
        this->totalPrice = calcTotalPrice();//tinh lai tong so tien
        return 1;
    }
return 0;
}
//format VND
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


void Invoice::getInfor(const Invoice *inv){
    
    //  cout << left << setw(15) << "Invoice ID:" << setw(15) << inv->InvoiceID << endl
     cout << left << setw(15) << "Invoice ID:" << setw(15) << inv->InvoiceID<< endl

        << left << setw(15) << "Staff ID:" << setw(15) << inv->staffID << endl
        << left << setw(15) << "Customer ID:" << setw(15) << inv->customerID << endl
        << left << setw(20) << "Time of purchase:" << setw(15) << inv->time << endl
        << left << setw(15) << "Invoice Detail:"<<endl
        << left << setw(30) << "Product Name" << setw(10)<<"Quantity" << setw(20)<<"Price" << endl;
        // duyet qua tung InvoiceDetail::detail id de lay ten san pham, so luong va gia tien tung InvoiceDetail::detail Invoice
        for(string dt : inv->detailID) {
            string name = Product::getPrdByID((InvoiceDetail::getDetailByID(dt)->getPrdID()))->getPrdName();
            int number = InvoiceDetail::getDetailByID(dt)->getQuantity();
            long long money = InvoiceDetail::getDetailByID(dt)->getPrice();
            cout<<setw(30) << name << setw(10)<<number << setw(20)<<formatCurrency(money)<< endl;
        }
        cout<<endl<<setw(40)<<"Total Price:"<<formatCurrency(inv->totalPrice)<< endl
        << "----------------------------------------" << endl;

}

void Invoice::setQuantityInvoice(string dtID, int number){
    InvoiceDetail::getDetailByID(dtID)->setQuantity(number);
    this->totalPrice = this->calcTotalPrice();
}
Invoice* Invoice::getInvoiceByID(const string id){
    for (Invoice *Invoice : Invoice::inv){
        if (Invoice->getInvoiceID() == id){   
            return Invoice;
        }
    }
return nullptr;
}
void Invoice::deleteInvoice(){
    auto it = find(inv.begin(), inv.end(), this);
    if (it != inv.end()) {
        inv.erase(it);
        delete this; // giai phong bo nho cho this
    }

}
void Invoice::display(){
for(Invoice *Invoice: inv){
    Invoice::getInfor(Invoice);
    }
}

int Invoice::saveToFile(string fileName){
    ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return 0;
        }
        for (Invoice *Invoiced : inv) {
            if (!Invoiced) {
                continue; // Bỏ qua nếu là nullptr
            }
            file << Invoiced->InvoiceID << "," << Invoiced->staffID << ","<< Invoiced->customerID<<"," << Invoiced->time << "," << Invoiced->totalPrice;
            // duyet qua tung phan tu cua hoa fon
            for(string hDon: Invoiced->detailID){
             file<<","<<hDon;
            }
            file <<endl;
        }
        
        file.close();
        return 1;
}
int Invoice::loadFromFile(string fileName){
ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return 0;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string InvoiceId, staffId, customerId, time, money, detailId;
        getline(ss, InvoiceId, ',');
        getline(ss, staffId, ',');
        getline(ss, customerId, ',');
        getline(ss, time, ',');
        getline(ss, money, ',');
        getline(ss,detailId,',');

    // kiem tra gia tri co hop le hay khong
    
       long long moneyValue;
        try {
            moneyValue = std::stoll(money);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid money value: " << money << "\n";
            return 0; 
        } catch (const std::out_of_range& e) {
            std::cerr << "Money value out of range: " << money << "\n";
            return 0; 
        }    
            
        if (moneyValue < 0) {
            return 0; 
        }
        Invoice *iv = new Invoice(staffId, customerId, time,detailId);
        Invoice::inv.push_back(iv);
        // them cac detail id con lai vao mang
        while(getline(ss, detailId,',')){
            iv->addDetailID(detailId);
        }
    }
    file.close();
    return 1;
}

//get
string Invoice::getInvoiceID(){
return InvoiceID;
}
string Invoice::getStaffID(){
return staffID;

}
string Invoice::getCustomerID(){
return customerID;

}
string Invoice::getTime(){
return time;
}
cvector<string> Invoice::getDetailID(){
return detailID;
}
long long Invoice::getTotalPrice(){
return totalPrice;

}
 int Invoice::getInvoiceQuantity(){
    return Invoice::inv.getSize();
 }
long long  Invoice::getRevenue(){
    long long  money = 0;
    for(Invoice *i : Invoice::inv){
        money += i->getTotalPrice();
    }
    return money;
}

long long Invoice::calcProfit() {
    long long moneyImport = 0;
    for (Invoice* i : Invoice::inv) {
        for (const std::string& de : i->getDetailID()) {
            InvoiceDetail* detail = InvoiceDetail::getDetailByID(de);
            if (detail) {
                moneyImport += detail->getImportPrice();
            }
        }
    }
    return Invoice::getRevenue() - moneyImport;
}
// long long Invoice::calcProfit(){
//     long long moneyImport = 0;
//     for(Invoice *i : Invoice::inv){
//         for(string de : i->getDetailID()){
//             if(InvoiceDetail::getDetailByID(de)){

//             moneyImport += InvoiceDetail::getDetailByID(de)->getImportPrice();
//             }
//         }
//     }

//     return Invoice::getRevenue() - moneyImport;
//   }