#include<iostream>
#include"invoiceDetail.h"
#include"product.h"
using namespace std;
int product::nextPrdID = 1;
int invoiceDetail::nextDetailID = 1;

int main(){
  product* p1 = new product("Laptopgl A", "Brand A", "Detail A", 1000, 10);
  product* p2 = new product("Laptop c", "Brand A", "Detail B", 1500, 5);
  product* p3 = new product("Gaming Laptop", "Brand A", "Detail B", 2500, 5);
 invoiceDetail *i  = new invoiceDetail("IV00009",5,"PD00001");

invoiceDetail::loadFromFile("detail.csv");
// OK invoiceDetail::getDetailByID("DE00003")->setQuantity(10);

i->deleteDetail();
invoiceDetail::saveToFile("detail.csv");
invoiceDetail::displayDetail();
//  product::displayPrd();
    // cout << "Product Information:" << endl;
    // product::getInfor(p1);
    // p2->setUnitPrice(28767863647);
    // product::getInfor(p2);
    // product::setInfor(*p2);
    // cout<<"nhap ten di thawngf l"<<endl;
    // string ten;
    // getline(cin, ten);

    // product::searchByName(ten);
    // cout<<p2->searchByName("Laptop A");      
   

    return 0;
}