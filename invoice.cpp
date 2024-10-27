#include"invoice.h"
#include"invoiceDetail.h"
#include"product.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

long long invoice::calcTotalPrice(){
    long long total = 0;
    for(string* dt : this->detailID) {
        total+= invoiceDetail::getDetailByID(*dt)->getPrice();
    }
   
    return total;
}

invoice::invoice( const string staffID , const string customerID , const string time, const string detailID){
this->invoiceID = generateInvoiceID(); 
this->staffID = staffID;
this->customerID = customerID; 
this->time = time;
this->detailID.push_back(new string(detailID));//chuyen thanh con tro
this->totalPrice = calcTotalPrice();
inv.push_back(this);
}
string invoice::generateInvoiceID(){
        stringstream ss;
        ss <<"IN"<< setw(5) << setfill('0') << nextInvoiceID++; 
        return ss.str();
    }
int invoice::addDetailID(string dtID){
    if(invoiceDetail::getDetailByID(dtID)){
        this->detailID.push_back(new string(dtID));// them vao vecto detailID 
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


void invoice::getInfor(const invoice *inv){
    
     cout << left << setw(15) << "Invoice ID:" << setw(15) << inv->invoiceID << endl
        // << left << setw(15) << "Detail ID:" << setw(30) << inv->detailID << endl
        << left << setw(15) << "Staff ID:" << setw(15) << inv->staffID << endl
        << left << setw(15) << "Customer ID:" << setw(15) << inv->customerID << endl
        << left << setw(20) << "Time of purchase:" << setw(15) << inv->time << endl
        << left << setw(15) << "Invoice Detail:"<<endl
        << left << setw(30) << "Product Name" << setw(10)<<"Quantity" << setw(20)<<"Price" << endl;
        // duyet qua tung detail id de lay ten san pham, so luong va gia tien tung detail invoice
        for(string* dt : inv->detailID) {
            string name = product::getPrdByID(invoiceDetail::getDetailByID(*dt)->getPrdID())->getPrdName();
            int number = invoiceDetail::getDetailByID(*dt)->getQuantity();
            long long money = invoiceDetail::getDetailByID(*dt)->getPrice();
            cout<<setw(30) << name << setw(10)<<number << setw(20)<<formatCurrency(money)<< endl;
        }
        cout<<endl<<setw(40)<<"Total Price:"<<formatCurrency(inv->totalPrice)<< endl
        << "----------------------------------------" << endl;

}

void invoice::setQuantityInvoice(string dtID, int number){
    invoiceDetail::getDetailByID(dtID)->setQuantity(number);
    this->totalPrice = this->calcTotalPrice();
}
invoice* invoice::getInvoiceByID(const string id ){
    for (invoice *invoice : inv){
        if (invoice->getInvoiceID() == id){   
            return invoice;
        }
    }
}
void invoice::deleteInvoice(){
    auto it = find(inv.begin(), inv.end(), this);
    if (it != inv.end()) {
        inv.erase(it);
        delete this;// giai phong bo nho cho this
    }

}
void invoice::display(){
for(invoice *invoice: inv){
    invoice::getInfor(invoice);
    }
}
int invoice::saveToFile(string fileName){
     ofstream file(fileName);
        if (!file) {
            cerr << "Error opening file for writing.\n";
            return 0;
        }
        for (invoice *invoiced : inv) {
            if (!invoiced) {
                continue; // Bỏ qua nếu là nullptr
            }
            file << invoiced->invoiceID << "," << invoiced->staffID << ","<< invoiced->customerID<<"," << invoiced->time << "," << invoiced->totalPrice;
            // duyet qua tung phan tu cua hoa fon
            for(string *hDon: invoiced->detailID){
             file<<","<<*hDon;
            }
            file <<endl;
        }
        
        file.close();
        return 1;

}
int invoice::loadFromFile(string fileName){
ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return 0;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string invoiceId, staffId, customerId, time, money, detailId;
        getline(ss, invoiceId, ',');
        getline(ss, staffId, ',');
        getline(ss, customerId, ',');
        getline(ss, time, ',');
        getline(ss, money, ',');
        getline(ss, detailId,',');

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
        invoice *iv = new invoice(staffId, customerId, time,detailId);
        // them cac detail id con lai vao mang
        while(getline(ss, detailId,',')){
            iv->addDetailID(detailId);
        }
    }
    file.close();
    return 1;
}

//get
string invoice::getInvoiceID(){
return invoiceID;
}
string invoice::getStaffID(){
return staffID;

}
string invoice::getCustomerID(){
return customerID;

}
string invoice::getTime(){
return time;
}
vector<string*> invoice::getDetailID(){
return detailID;

}
long long invoice::getTotalPrice(){
return totalPrice;

}
