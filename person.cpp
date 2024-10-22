#include "person.h"
static vector<person*> obj;
string person::generateID() {
    // Chuy?n nextID th�nh chu?i c� 7 ch? s?, th�m s? 0 ? ph�a tru?c
    stringstream ss;
    ss << setw(7) << setfill('0') << nextID;
    nextID++; // Tang nextID l�n 1 cho ngu?i k? ti?p
    return ss.str();// tr? v? gi� tr?
}

// ham dung constructor
person::person(const string _name, const string _phone, const string _email, const string _pass, string _role) {
    name = _name; phone = _phone;
    email = _email; pass = _pass;
    role = _role;
    personID = generateID();
    obj.push_back(this);

}
//  ham dung destructor
void person::clearPerson() {

    for (person* p : obj) {
        delete p;  // Delete 
    }
    obj.clear();  // Clear the vector
    obj.shrink_to_fit();

}

// name
string person::getName() {
    return name;
}
void person::setName() {
    cout << "Enter Fullname:";
    getline(cin, name);
};

// ID
string person::getID() {
    return personID;
}
// phone
string person::getPhone() {
    return phone;
}
void person::setPhone() {
    cout << "Enter Phone number:";
    getline(cin, phone);
};
// email
string person::getEmail() {
    return email;
}
void person::setEmail() {
    cout << "Enter your Email:";
    getline(cin, email);
};
// pass
// ham hien thi dau * cho pass
string person::hidenPass() {
    string password = "";
    char ch;
    // �?c t?ng k� t? cho d?n khi g?p Enter (13)
    while ((ch = _getch()) != 13) {
        if (ch == 8) {  // N?u ngu?i d�ng nh?n ph�m Backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
string person::getPass() {
    return pass;
}
string person::getRole() {
    return role;
}
// void person::setPass(){
//     cout<<"Enter your password:";
//     getline(cin,pass);
// };
void person::setPass() {
    string password, confirmPass;
    cout << "Enter password:\t";
    password = hidenPass();
    int todo = 1, maxTry = 3;

    while (todo < maxTry) {
        cout << "Confirm password: ";
        confirmPass = hidenPass();
        if (password == confirmPass) {
            pass = password; // G�n m?t kh?u
            cout << "Password set successfully!" << endl;
            break;
        }
        else {
            todo++;
            if (todo < maxTry) {
                cout << "Passwords do not match. Please try again!" << endl;
            }
            else {
                cout << "Maximum attempts reached. Password not set." << endl;
            }

        }
    }
}
void person::setInfor(person& a) {
    a.setName();
    a.setPhone();
    a.setEmail();
}
void person::display() {
    if (obj.empty()) {
        cout << "The program is NULL" << endl;
    }
    else {
        for (person* person : obj) {
            printInfor(person);
        }
    }

}
void person::printInfor(const person* a) {
    cout << left << setw(10) << "ID:" << setw(10) << a->personID << endl
        << left << setw(10) << "FullName:" << setw(20) << a->name << endl
        << left << setw(10) << "Email:" << setw(30) << a->email << endl
        << left << setw(10) << "Phone:" << setw(15) << a->phone << endl
        << "----------------------------------------" << endl;
}

int person::login(string id, string pw, person* p) {
    for (person* person : obj) {
        if ((person->getID()) == id) {
            if (person->getPass() == pw) {
                *p = *person;
                return 1;
            }
            else return 0;
        }
    }
    return 0;
}

void person::printTableHeader() {
    cout << left << setw(10) << "ID"
        << setw(20) << "Full Name"
        << setw(30) << "Email"
        << setw(15) << "Phone"
        << endl;
    cout << "-----------------------------------------------------------------------" << endl;
}
int person::nextID = 0;  // Định nghĩa biến tĩnh
