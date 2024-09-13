#include<iostream>
#include"product.h"
using namespace std;
int product::nextPrdID = 1;
vector<product*> product::prd;
int main(){
  product* p1 = new product("Laptop A", "Brand A", "Detail A", 1000, 10);
    product* p2 = new product("Laptop B", "Brand A", "Detail B", 1500, 5);
    // product p3;
    // product::setInfor( p3);
    // Hiển thị thông tin các sản phẩm
    cout << "Product Information:" << endl;
    // product::getInfor(p1);
    // p2->setUnitPrice(28767863647);
    // product::getInfor(p2);
    // cout<<p2->searchByName("Laptop A");      
    product::displayPrd();

    return 0;
}