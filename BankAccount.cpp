#include "BankAccount.h"

//initialize static integers
int BankAccount::accountNumber = 0;
int BankAccount::activeAccounts = 0;

//constructor and deconstructor
BankAccount::BankAccount() {
    // initialize account number and active account from file
    AccNumActAccTextFile.open("AccNumActAcc.txt");
    if (!AccNumActAccTextFile) {
    }
    else {
        AccNumActAccTextFile >> accountNumber;
        AccNumActAccTextFile >> activeAccounts;
    }
    AccNumActAccTextFile.close();

    bankAccountMenu = true;
    currentUserAccounts = 0;
    ans = 0;
    accountExist = false;
    balance = 0;
}
BankAccount::~BankAccount() {}

//function for loading bank info 
void BankAccount::loadBankAccount(string userName) {
    do {
        currentUserAccounts = 0;//use for determining how many bank accounts the user have open
        BankAccountsTextFile.open("BankAccounts.txt");
        if (!BankAccountsTextFile) {
            cout << "Error: No such file found.\n" << endl;
            return;
        }
        //validate Username with Username in bank account text file and display account accordingly
        else {
            //display bank account info according to the numbers of bank accounts the user have open
            cout << userName << "'s Bank Account" << endl;
            cout << "---------------------------" << endl;
            while (getline(BankAccountsTextFile, userID, ';'), getline(BankAccountsTextFile, Name, ';'), getline(BankAccountsTextFile, accNum, ';'), getline(BankAccountsTextFile, accountType, ';'), getline(BankAccountsTextFile, bal)) {
                if (currentUserAccounts == 0 && userID == userName) {
                    storedName = Name;
                    currentUserAccounts++;
                    cout << "Name: " << Name << endl;
                    cout << "Account Number: " << accNum << endl;
                    cout << "Account Type: " << accountType << endl;
                    cout << "Balance: $" << bal << endl;
                }
                else if (currentUserAccounts == 1 && userID == userName) {
                    storedName = Name;
                    currentUserAccounts++;
                    cout << "Account Number: " << accNum << endl;
                    cout << "Account Type: " << accountType << endl;
                    cout << "Balance: $" << bal << endl;
                }
            }
            BankAccountsTextFile.close();
            if (currentUserAccounts == 0) {
                cout << "No accounts exist for this user." << endl;
            }
        }
        
        cout << "---------------------------" << endl;
        cout << "1. Add Account" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Account Summary" << endl;
        cout << "5. Exit\n" << endl;
        cin >> ans;

        switch (ans) {
        //add account case
        case 1:
            if (currentUserAccounts == 2) {
                cout << "User already have both a checking and saving accounts.\n" << endl;
            }
            else { addAccount(userName); }
            break;
        //withdraw account case
        case 2:
            do {
                cout << "Which account would you like to withdraw from?" << endl;
                cin >> accountType;
                if (accountType != "Checking" && accountType != "Saving") {
                    cout << "Enter only Checking or Saving. Try again.\n" << endl;
                }
            } while (accountType != "Checking" && accountType != "Saving");
            do {
                cout << "Enter the amount you want to withdraw: ";
                cin >> Transaction::amount;
            } while (!isTwoDecimalPlaces(Transaction::amount));
            withdraw(userName, Transaction::amount, accountType);
            cout << endl;
            break;
        //deposit account case
        case 3:
            do {
                cout << "Which account would you like to deposit from?" << endl;               
                cin >> accountType;
                if (accountType != "Checking" && accountType != "Saving") {
                    cout << "Enter only Checking or Saving. Try again.\n" << endl;
                }
            } while (accountType != "Checking" && accountType != "Saving");
            do {
                cout << "Enter the amount you want to deposit: ";
                cin >> Transaction::amount;
            } while (!isTwoDecimalPlaces(Transaction::amount));
            deposit(userName, Transaction::amount, accountType);
            cout << endl;
            break;
        //account summary case
        case 4:
            displayHistory(userName);
            cout << endl;
            break;
        //exit case
        case 5:
            cout << "Returning to previous menu.\n" << endl;
            return;
        //default case
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4.\n" << endl;
        }
    } while (bankAccountMenu == true);
}

//function to add bank account
void BankAccount::addAccount(string userName) {
    //ask for account type
    do {
        //valid input check
        do {
            cout << "Enter Account Type:" << endl;
            cin >> accountType;
            if (accountType != "Checking" && accountType != "Saving") {
                cout << "Enter only Checking or Saving. Try again.\n" << endl;
            }
        } while (accountType != "Checking" && accountType != "Saving");

        //check to see if accountType already exist
        accountExist = false;
        BankAccountsTextFile.open("BankAccounts.txt");
        if (!BankAccountsTextFile) {
            cout << "No such file found.\n" << endl;
            return;
        }
        else {
            while (getline(BankAccountsTextFile, userID, ';'), getline(BankAccountsTextFile, Name, ';'), getline(BankAccountsTextFile, accNum, ';'), getline(BankAccountsTextFile, accType, ';'), getline(BankAccountsTextFile, bal)) {
                if (userID == userName && accType == accountType) {
                    cout << "Account type already exist. Try again.\n" << endl;
                    BankAccountsTextFile.close();
                    accountExist = true;
                    break;
                }
            }
            BankAccountsTextFile.close();
        }
    } while (accountExist == true);

    //ask for name
    if (currentUserAccounts == 0) {
        do {
            cout << "Enter Name:" << endl;
            cin >> Name;
        } while (!isAlphaNumeric(Name));
    }
    else {
        Name = storedName;
    }

    //ask for balance
    do {
        cout << "Enter Balance:" << endl;
        cin >> balance;
    } while (!isTwoDecimalPlaces(balance));

    //give a bank account number and increase active account
    accountNumber++;
    activeAccounts++;
    cout << "Account Number: " << accountNumber << endl;

    //append all info to bank account text file
    BankAccountsTextFile.open("BankAccounts.txt", ios::app);
    AccNumActAccTextFile.open("AccNumActAcc.txt", ios::out);
    if (!BankAccountsTextFile && !AccNumActAccTextFile) {
        cout << "No such file found.\n" << endl;
    }
    else {
        BankAccountsTextFile << userName << ";" << Name << ";" << accountNumber << ";" << accountType << ";" << fixed << setprecision(2) << balance << endl;
        AccNumActAccTextFile << accountNumber << endl << activeAccounts << endl;
        cout << "Bank account successfully created.\n" << endl;
    }
    BankAccountsTextFile.close();
    AccNumActAccTextFile.close();
}

//getter function for activeAccounts
int BankAccount::getActiveAccounts() {
    return activeAccounts;
}

//function for manager to remove bank account
void BankAccount::removeBankAccount(string userName, string accountNumber) {
    accountExist = false;//use to determine if bank account is remove or not
    BankAccountsTextFile.open("BankAccounts.txt");
    AccNumActAccTextFile.open("AccNumActAcc.txt", ios::out);
    temp.open("temp.txt");
    if (!BankAccountsTextFile && !temp && !AccNumActAccTextFile) {
        cout << "No such file found.\n" << endl;
        return;
    }
    //validate Username and accountNumber input with Username and accountNumber in bank account text file and remove account accordingly
    else {
        while (getline(BankAccountsTextFile, userID, ';'), getline(BankAccountsTextFile, Name, ';'), getline(BankAccountsTextFile, accNum, ';'), getline(BankAccountsTextFile, accType)) {
            if (userID == userName && accNum == accountNumber) {//if account match, don't write to temp text file and decrease activeAccounts
                activeAccounts--;
                cout << "Remove account successfully.\n" << "Numbers of Active Accounts: " << activeAccounts << "\n" << endl;
                accountExist = true;
                //update active account in text file
                AccNumActAccTextFile << this->accountNumber << endl;
                AccNumActAccTextFile << activeAccounts << endl;
            }
            else {//write any accounts that doesn't match to temp text file
                temp << userID << ';' << Name << ';' << accNum << ';' << accType << endl;
            }
        }
   
        if (accountExist == false) {//no account remove
            cout << "Remove account fail.\n" << endl;
        }
        BankAccountsTextFile.close();
        AccNumActAccTextFile.close();
        temp.close();
        remove("BankAccounts.txt");
        if (rename("temp.txt", "BankAccounts.txt") == -1) {
            cout << "Rename file failed." << endl;
        }
        return;
    }
}

//function to show all bank accounts
void BankAccount::showAll() {
    cout << "---------------------------" << endl;
    BankAccountsTextFile.open("BankAccounts.txt");
    if (!BankAccountsTextFile) {
        cout << "No such file found.\n" << endl;
        return;
    }
    else {
        while (getline(BankAccountsTextFile, userID, ';'), getline(BankAccountsTextFile, Name, ';'), getline(BankAccountsTextFile, accNum, ';'), getline(BankAccountsTextFile, accountType, ';'), getline(BankAccountsTextFile, bal)) {
            cout << "Username: " << userID << endl;
            cout << "Name: " << Name << endl;
            cout << "Account Number: " << accNum << endl;
            cout << "Account Type: " << accountType << endl;
            cout << "Balance: $" << bal << endl;
            cout << "---------------------------\n" << endl;
        }
        BankAccountsTextFile.close();
    }
}