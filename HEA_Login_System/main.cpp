//
//  main.cpp
//  HEA_Login_System
//
//  Created by 세광 on 2021/07/07.
//

#include <iostream>
#include <fstream>
#define max_length 30
#define array_size 1024

using namespace std;

struct Key {
    char *id;
    char *pw;
    char *domain;
    char *comp;
    char *temp;
};

struct Index {
    unsigned int id;
    unsigned int pw;
    unsigned int domain;
    unsigned int length;
    unsigned int comp;
};

struct Count {
    bool atsigh;
    bool point;
    bool domain;
    bool end;
};

class Login_System {
public:
    Login_System();
    ~Login_System();
    
    void Validate_Email();
    void Make_Passward();
    void Print();
    void Try_Again();
    
private:
    int Check();
    
    void Set_Null();
    void Set_Alloc();
    void Set_Delete();
    void Set_Count_False();
    
    Key key;
    Index index;
    Count count;
    int position;
    int point;
    char y_n;
};

int main() {
    while (true) {
        Login_System *login = new Login_System();
        login->Validate_Email();
        cout << '\n' << "------------ CHECKING ------------" << endl;
        login->Print();
        delete login;
    }
}

Login_System::Login_System() : position(0), point(0) {
    index.length = 0;
    index.comp = 0;
    Set_Count_False();
    Set_Null();
    Set_Alloc();
    cout << "--- LOGIN TO ACCESS HEA SYSTEM ---" << '\n' << endl;
    cout << "email: "; cin >> key.id;
    cout << "passward: "; cin >> key.pw;
}

Login_System::~Login_System() {
    Set_Delete();
    Set_Null();
}

void Login_System::Validate_Email() {
    for (unsigned int i = 0; i < strlen(key.id); i++) {
        if (key.id[i] == '@') {
            index.id = i;
            count.atsigh = true;
            break;
        }
    }
    
    for (unsigned int i = index.id; i < strlen(key.id); i++) {
        if (key.id[index.id + 1] == '.' || key.id[index.id + 1] == '@') {
            count.point = false;
            break;
        }
        else {
            if (key.id[i] == '.') {
                if (i == strlen(key.id) - 1) {
                    count.point = false;
                    break;
                }
                else {
                    index.id = i;
                    count.point = true;
                }
            }
        }
    }

    ifstream Fileopen;
    Fileopen.open("allowed_domain.txt");
    if (Fileopen.is_open()) {
        while (!Fileopen.eof() && position < array_size) {
            Fileopen.get(key.comp[position]);
            position++;
        }
        key.comp[position - 1] = '\0';
    }
    Fileopen.close();
    
    for (unsigned int i = 0; i < max_length; i++) {
        if (key.id[i] == '@') {
            index.domain = i;
        }
    }
    for (size_t i = index.domain + 1; i < strlen(key.id); i++) {
        key.domain[i - index.domain - 1] = key.id[i];
        index.length++;
    }

    while (true) {
        for (unsigned int i = index.comp; key.comp[i] != '\n'; i++) {
            if (key.comp[i + 1] == '\n' || key.comp[i + 1] == '\0') {
                if (index.length == i + 1 - index.comp) {
                    count.domain = true;
                    for (size_t j = index.comp; key.comp[j] != '\n'; j++) {
                        if (key.domain[j - index.comp] != key.comp[j]) count.domain = false;
                        if (key.comp[j + 1] == '\n') {
                            if (count.domain == true) {
                                count.end = true;
                                break;
                            }
                            else break;
                        }
                        if (key.comp[j + 1] == '\0') {
                            count.end = true;
                            break;
                        }
                    }
                }
                if (key.comp[i + 1] == '\0') {
                    count.end = true;
                    break;
                }
                else index.comp = i + 2;
            }
        }
        if (count.end == true) break;
    }
    
    if (count.atsigh == false) return;
    if (count.point == false) return;
    if (count.domain == false) return;

    Make_Passward();
}

void Login_System::Make_Passward() {
    for (unsigned int i = 0; i < max_length; i++) {
        if (key.id[i] == '@') {
            index.pw = i;
        }
    }
    
    if (strlen(key.id) < 10) {
        if (index.pw > strlen(key.id) - index.pw - 1) {
            for (size_t i = 0; i < strlen(key.id) - index.pw - 1; i++) {
                key.temp[2 * i] = key.id[i];
                key.temp[2 * i + 1] = key.id[index.pw + 1 + i];
            }
            for (size_t i = strlen(key.id) - index.pw - 1; i < index.pw; i++) {
                key.temp[i + strlen(key.id) - index.pw - 1] = key.id[i];
            }
            for (size_t i = strlen(key.id) - 1; i < 10; i++) {
                key.temp[i] = '0';
            }
        }
        else {
            for (size_t i = 0; i < index.pw; i++) {
                key.temp[2 * i] = key.id[i];
                key.temp[2 * i + 1] = key.id[index.pw + 1 + i];
            }
            for (size_t i = index.pw; i < strlen(key.id) - index.pw - 1; i++) {
                key.temp[i + index.pw] = key.id[index.pw + 1 + i];
            }
            for (size_t i = strlen(key.id) - 1; i < 10; i++) {
                key.temp[i] = '0';
            }
        }
    }
    
    else {
        if (index.pw > strlen(key.id) - index.pw - 1 && strlen(key.id) - index.pw - 1 < 5) {
            for (size_t i = 0; i < strlen(key.id) - index.pw - 1; i++) {
                key.temp[2 * i] = key.id[i];
                key.temp[2 * i + 1] = key.id[index.pw + 1 + i];
            }
            for (size_t i = strlen(key.id) - index.pw - 1; i < 10; i++) {
                key.temp[i + strlen(key.id) - index.pw - 1] = key.id[i];
            }
        }
        else if (index.pw < strlen(key.id) - index.pw - 1 && index.pw < 5) {
            for (size_t i = 0; i < index.pw; i++) {
                key.temp[2 * i] = key.id[i];
                key.temp[2 * i + 1] = key.id[index.pw + 1 + i];
            }
            for (size_t i = index.pw; i < 10; i++) {
                key.temp[i + index.pw] = key.id[index.pw + 1 + i];
            }
        }
        else {
            for (size_t i = 0; i < 5; i++) {
                key.temp[2 * i] = key.id[i];
                key.temp[2 * i + 1] = key.id[index.pw + 1 + i];
            }
        }
    }
    key.temp[10] = (char)NULL;
}

void Login_System::Print() {
    switch (Check()) {
        case 1:
            cout << "ERROR! invalid email format!" << '\n' << endl;
            Try_Again();
            break;

        case 2:
            cout << "ERROR! invalid domain format!" << '\n' << endl;
            Try_Again();
            break;

        case 3:
            cout << "ERROR! This domain is not allowed!" << '\n' << endl;
            cout << "The domains allowed are:" << endl;
            cout << key.comp << '\n' << endl;
            Try_Again();
            break;
            
        case 4:
            cout << "ERROR! invalid passward!" << '\n' << endl;
            Try_Again();
            break;

        default:
            cout << "SUCCESS! now you can access HEA system!" << '\n' << endl;
            exit(1);
            break;
    }
}

void Login_System::Try_Again() {
    cout << "Do you want try again? (y/n) "; cin >> y_n;
    if (y_n == 'y') {
        cout << endl;
    }
    else if (y_n == 'n') {
        cout << endl;
        exit(1);
    }
    else {
        Try_Again();
    }
}

int Login_System::Check() {
    if (count.atsigh == false) return 1;
    if (count.point == false) return 2;
    if (count.domain == false) return 3;
    if (strlen(key.pw) == strlen(key.temp)) {
        for (size_t i = 0; i < 10; i++) {
            if (key.pw[i] == key.temp[i]) {
                point++;
            }
        }
    }
    if (point == 10) return 0;
    else return 4;
}

void Login_System::Set_Null() {
    key.id = NULL;
    key.pw = NULL;
    key.domain = NULL;
    key.comp = NULL;
    key.temp = NULL;
}

void Login_System::Set_Alloc() {
    key.id = new char[max_length];
    key.pw = new char[max_length];
    key.domain = new char[max_length];
    key.comp = new char[array_size];
    key.temp = new char[10];
}

void Login_System::Set_Delete() {
    delete [] key.id;
    delete [] key.pw;
    delete [] key.domain;
    delete [] key.comp;
    delete [] key.temp;
}

void Login_System::Set_Count_False() {
    count.atsigh = false;
    count.point = false;
    count.domain = false;
    count.end = false;
}
