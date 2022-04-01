#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <cstdbool>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

bool mainLoop = 0;
string full_name;
//Library system management 

typedef struct NewUser {
    string firstName, lastName, password;
    int age = 0, salary = 0, id = 0;
}NewUser;

typedef struct NewBook {
    string name, auther;
    int id = 0, storage = 0, price = 0;
}NewBook;

void clear();
void userMenu(int *);

string fullName();
bool checkPassword();

//user
void isNew_user();
void new_user();

//main work
void newBook();
void getBook();
void changePassword();
void sellBook();
void buyBook();
void bookList();

int main() {
    mainLoop = 1;
    int choice = 0;
    srand(time(0));

    while (mainLoop) {
        userMenu(&choice);

        switch (choice) {
            case 0:
            {
                mainLoop = 0;
                clear();
                break;
            }
            case 1:
            {
                new_user();
                clear();
                break;
            }
            case 2:
            {
                newBook();
                clear();
                break;
            }
            case 3:
            {
                getBook();
                break;
            }
            case 4:
            {
                changePassword();
                clear();
                break;
            }
            case 5:
            {
                sellBook();
                clear();
                break;
            }
            case 6:
            {
                buyBook();
                clear();
                break;
            }
            case 7:
            {
                bookList();
                break;
            }
            default:
            {
                clear();
                cout << "check your choice!!!" << endl;
            }
        }
    }
    return 0;
}

void userMenu(int* x) {
    cout << "1.Create a new account\n";
    cout << "2.Add a new book\n";
    cout << "3.Get book informations\n";
    cout << "4.Change password\n";
    cout << "5.Sell Book\n";
    cout << "6.Buy book\n";
    cout << "7.Get book list\n";
    cout << "0.Exit\n";
    cout << "Enter your choice: "; cin >> *x;
}

string fullName() {
    NewUser checkUser;
    cout << "Enter your first name: "; cin >> checkUser.firstName;
    cout << "Enter your last name: "; cin >> checkUser.lastName;
    return (checkUser.firstName + ' ' + checkUser.lastName);
}

//user
void isNew_user() {
    fstream isExist;
    full_name = fullName();
    isExist.open(full_name);

    if (isExist) {
        if (checkPassword()) {
            cout << "check your password or your name!!!" << endl;
            isNew_user();
            //return;
        }
    }
    else {
        cout << "New user, right ?\n";
        int yes_no = 0;
        do {
            cout << "1.Yes" << endl;
            cout << "2.No" << endl;
            cout << "enter your choice: "; cin >> yes_no;
        } while (!(yes_no == 1 || yes_no == 2));
        (yes_no == 1) ? new_user() : isNew_user();
    }
}
void new_user() {
    NewUser user;

    cout << "enter your first name: "; cin >> user.firstName;
    cout << "enter your last name: "; cin >> user.lastName;
    cout << "enter a password: "; cin >> user.password;
    cout << "set your salary: "; cin >> user.salary;
    cout << "Warning age must be greater than 13\n";
    do {
        cout << "enter your age: "; cin >> user.age;
    } while (!(user.age > 13 and user.age < 70));

    fstream file;
    file.open((user.firstName + ' ' + user.lastName));

    if (file) {
        cout << "\nThe user is already exist!!!" << endl;
        cout << "\nEnter an anothers inforamtions!!" << endl;
        new_user();
    }

    file.close();

    file.open((user.firstName + ' ' + user.lastName), ios::out);

    file << "Type: User";
    file << "\nID: " << rand();
    file << "\nFirst Name: " << user.firstName;
    file << "\nLast Name: " << user.lastName;
    file << "\nPassword: " << user.password;
    file << "\nSalary: " << user.salary;
    file << "\nAge: " << user.age;

    file.close();
}

//main work
void newBook() {
    NewBook book;

    cout << "Enter Book's name: ";
    cin >> book.name;

    cout << "Enter auther's name: ";
    cin >> book.auther;

    cout << "Enter the price: "; cin >> book.price;
    cout << "Enter the storage: "; cin >> book.storage;

    fstream file;
    file.open(book.name, ios::out);

    if (file) {
        cout << "\nThe book is already exist!!!" << endl;
        cout << "\nEnter an others informations!!!" << endl;
        newBook();
    }

    file << "ID: " << rand();
    file << "\nBook: " << book.name;
    file << "\nAuther: " << book.auther;
    file << "\nPrice: " << book.price << endl;
    file << "Storage: " << book.storage << endl;

    file.close();

    file.open("Book Storage", ios::app);

    file << "--" << book.name << "--" << endl;

    file.close();
}
void getBook() {
    NewBook book;

    cout << "Enter the book name: "; cin >> book.name;

    fstream file;
    file.open(book.name, ios::in);

    if (!file) {
        cout << "\ncheck the book name!!!" << endl;
        getBook();
    }

    clear();

    string info;
    int counter = 0;

    while (file >> info) {
        counter++;
       (counter % 2 != 0) ? cout << info << ' ' : cout << info << endl;
    }

    cout << endl;
}
void changePassword() {
    NewUser user;

    fstream file;
    full_name = fullName();
    file.open(full_name);

    while (checkPassword())
        cout << "\nCheck your password or your name" << endl;
    file.close();

    file.open(full_name, ios::in);

    int counter = 0;
    string info;

    cout << "enter your new password: "; cin >> user.password;

    while (file >> info) {
        counter++;
        if (counter == 4) {
            user.id = stoi(info);
        }
        else if (counter == 7) {
            user.firstName = info;
        }
        else if (counter == 10) {
            user.lastName = info;
        }
        else if (counter == 14) {
            user.salary = stoi(info);
        }
        else if (counter == 16) {
            user.age = stoi(info);
        }
    }

    file.close();

    file.open(full_name, ios::out);

    file << "Type: User" << endl;
    file << "ID: " << user.id << endl;
    file << "First Name: " << user.firstName << endl;
    file << "Last Name: " << user.lastName << endl;
    file << "Password: " << user.password << endl;
    file << "Salary: " << user.salary << endl;
    file << "Age: " << user.age;

    file.close();
}
void sellBook() {
    int bookNumber;

    cout << "\nCheck that your number is greater than 0!!!\nAnd the book must be exist in the storage!!!" << endl;

    do {
        cout << "How many book do you have: "; cin >> bookNumber;
    } while (bookNumber <= 0);

    NewBook book;
    fstream file;

    do {
        cout << "Enter the book name: "; cin >> book.name;
        file.open(book.name);

    } while (!file);
    file.close();

    file.open(book.name, ios::in);

    int counter = 0;
    string info;

    while (file>> info) {
        counter++;

        if (counter == 2) book.id = stoi(info);
        else if (counter == 4) book.name = info;
        else if (counter == 6) book.auther = info;
        else if (counter == 8) book.price = stoi(info);
        else if (counter == 10) book.storage = stoi(info) + bookNumber;
    }

    file.close();
    file.open(book.name, ios::out);

    file << "ID: " << book.id;
    file << "\nBook: " << book.name;
    file << "\nAuther: " << book.auther;
    file << "\nPrice: " << book.price << endl;
    file << "Storage: " << book.storage << endl;

    file.close();

    do {
        full_name = fullName();
        file.open(full_name);
      
    } while (!file);

    file.close();
    file.open(full_name, ios::in);

    counter = 0;
    NewUser user;

    while (file>> info) {
        counter++;

        if (counter == 4) user.id = stoi(info);
        else if (counter == 7) user.firstName = info;
        else if (counter == 10) user.lastName = info;
        else if (counter == 12) user.password = info;
        else if (counter == 14) user.salary = stoi(info) + (floor(book.price / 2) * bookNumber);
        else if (counter == 16) user.age = stoi(info);
    }

    file.close();
    file.open(full_name, ios::out);

    file << "Type: User";
    file << "\nID: " << user.id;
    file << "\nFirst Name: " << user.firstName;
    file << "\nLast Name: " << user.lastName;
    file << "\nPassword: " << user.password;
    file << "\nSalary: " << user.salary;
    file << "\nAge: " << user.age;

    file.close();
}
void buyBook() {
    NewBook book;
    NewUser user;

    int counter = 0;
    string info;

    fstream file;

    do {
        full_name = fullName();
        file.open(full_name);
    } while (!file);

    file.close();
    file.open(full_name, ios::in);

    while (file >> info) {
        counter++;

        if (counter == 4) user.id = stoi(info);
        else if (counter == 7) user.firstName = info;
        else if (counter == 10) user.lastName = info;
        else if (counter == 12) user.password = info;
        else if (counter == 14) user.salary = stoi(info);
        else if (counter == 16) user.age = stoi(info);
    }

    file.close();

    do {
        cout << "Enter the book name: "; cin >> book.name;
        file.open(book.name);

    } while (!file);

    file.close();

    file.open(book.name, ios::in);
    counter = 0;

    while (file >> info) {
        counter++;

        if (counter == 2) book.id = stoi(info);
        else if (counter == 4) book.name = info;
        else if (counter == 6) book.auther = info;
        else if (counter == 8) book.price = stoi(info);
        else if (counter == 10) book.storage = stoi(info);
    }

    file.close();

    int bookNumber, result;

    do {
        cout << "The available is " << book.storage << endl;
        cout << "Enter how many book do you want: "; cin >> bookNumber;
        result = bookNumber * book.price;

    } while (!(bookNumber <= book.storage && result <= user.salary));

    file.open(book.name, ios::out);

    file << "ID: " << book.id;
    file << "\nBook: " << book.name;
    file << "\nAuther: " << book.auther;
    file << "\nPrice: " << book.price << endl;
    file << "Storage: " << book.storage-bookNumber << endl;

    file.close();

    file.open(full_name, ios::out);

    file << "Type: User";
    file << "\nID: " << user.id;
    file << "\nFirst Name: " << user.firstName;
    file << "\nLast Name: " << user.lastName;
    file << "\nPassword: " << user.password;
    file << "\nSalary: " << user.salary-result;
    file << "\nAge: " << user.age;

    file.close();
}
void bookList() {  
    fstream file;
    file.open("Book Storage", ios::in);

    string info;

    clear();

    while(file >> info) {
        cout << info << endl;
    }

    cout << endl;
    file.close();
}

bool checkPassword() {
    int counter = 0;
    //pw == password
    string pw1, pw2;

    fstream file;
    file.open(full_name, ios::in);

    while (file >> pw1) {
        counter++;
        if (counter == 12) {
            cout << "Enter your password: "; cin >> pw2;
            if (pw1 == pw2) return 0;
            else return 1;
        }
    }
}
void clear() {
    for (int i = 0; i < 10; i++)
        cout << "\n\n\n\n\n\n\n\n\n\n";
}