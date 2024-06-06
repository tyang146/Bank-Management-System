#include "Manager.h"

//constructor and deconstructor
Manager::Manager() { managerMenu = true; }
Manager::~Manager() {}

//function for manager login
int Manager::login(string userName, string passWord) {
    ManagerTextFile.open("Managers.txt");
    if (!ManagerTextFile) {
        cout << "No such file found.\n" << endl;
        return 0;
    }
    else {
        while (getline(ManagerTextFile, User::userName, ';'), getline(ManagerTextFile, User::passWord)) {
            if (User::userName == userName && User::passWord == passWord) {
                cout << "Manager successfully login.\n" << endl;
                matches = true;
                ManagerTextFile.close();
            }
        }
        if (matches == false) {
            cout << "Manager login fail.\n" << endl;
            ManagerTextFile.close();
            return 0;
        }
    }

    //prompt manager login welcome page
    do {
        cout << "Welcome Manager: " << userName << endl;
        cout << "1. Close Bank Account" << endl;
        cout << "2. Load Bank Account" << endl;
        cout << "3. Show Number of Active Bank Accounts" << endl;
        cout << "4. Show All Bank Accounts" << endl;
        cout << "5. Remove User" << endl;
        cout << "6. Exit\n" << endl;
        cin >> BankAccount::ans;

        switch (BankAccount::ans) {
            //remove account case
        case 1:
            cout << "Enter Account Username: " << endl;
            cin >> User::userName;
            cout << "Enter Account Number: " << endl;
            cin >> BankAccount::accNum;
            removeBankAccount(User::userName, BankAccount::accNum);
            break;
            //load user account case
        case 2:
            cout << "Enter Account Username: " << endl;
            cin >> User::userName;
            if (userExist(User::userName) == 1) {
                cout << "Access user account succesfully.\n" << endl;
                loadBankAccount(User::userName);
            }
            else {
                cout << "User doesn't exist.\n" << endl;
            }
            break;
            //show number of active accounts case
        case 3:
            cout << "Number of Active Accounts: " << getActiveAccounts() << "\n" << endl;
            break;
            //show all bank accounts case
        case 4:
            showAll();
            break;
            //remove user account case
        case 5:
            cout << "Enter Account Username: " << endl;
            cin >> User::userName;
            removeUser(User::userName);
            break;
            //exit case
        case 6:
            cout << "Returning to menu.\n" << endl;
            return 1;
            //default case
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4.\n" << endl;
        }
    } while (managerMenu == true);
    return 1;
}