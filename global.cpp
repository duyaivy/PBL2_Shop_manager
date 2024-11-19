#include "./header/global.h"

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