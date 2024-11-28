#include "./header/global.h"
#include <algorithm>
#include <sstream>
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
string formatCurrency(long long number)
{
    stringstream ss;
    string result;
    ss << number;
    string strNumber = ss.str();
    int len = strNumber.length();
    int count = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        result.insert(0, 1, strNumber[i]);
        count++;
        if (count == 3 && i != 0)
        {
            result.insert(0, 1, '.');
            count = 0;
        }
    }
    result += "VND";
    return result;
}
int setUpDataBase(){
    if (!Product::loadFromFile(".\\csv\\products.csv") ) {
        cerr << "Failed to load product data.\n";
        return 0;
    }
    if (!InvoiceDetail::loadFromFile(".\\csv\\detail.csv")) {
        cerr << "Failed to load invoice detail data.\n";
        return 0;
    }
    if (!Invoice::loadFromFile(".\\csv\\invoice.csv")) {
        cerr << "Failed to load invoice data.\n";
        return 0;
    }
    if (!Employee::loadFromFile(".\\csv\\employees.csv") ) {
        cerr << "Failed to load employee data.\n";
        return 0;
    }
    if (!Customer::loadFromFile(".\\csv\\customers.csv") ) {
        cerr << "Failed to load customer data.\n";
        return 0;
    }
    return 1;
}
int saveDataBase(){
    Product::saveToFile(".\\csv\\products.csv");
    InvoiceDetail::saveToFile(".\\csv\\detail.csv");
    Invoice::saveToFile(".\\csv\\Invoice.csv");
    Employee::saveToFile(".\\csv\\employees.csv");
    Customer::saveToFile(".\\csv\\customers.csv");
}