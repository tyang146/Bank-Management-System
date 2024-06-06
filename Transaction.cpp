#include "Transaction.h"

string line;
bool userFound = false;
string userID, Name, accNum, accType, bal;

void Transaction::deposit(const string& userName, double amount, const string& accountType) {
    userFound = false;
    ifstream bankAccountsFile("BankAccounts.txt");
    ofstream tempFile("temp.txt");
    ofstream outFile("Transactions.txt", ios::app);
    if (!bankAccountsFile || !tempFile || !outFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }
    else {
        while (getline(bankAccountsFile, line)) {
            istringstream iss(line);
            getline(iss, userID, ';');
            getline(iss, Name, ';');
            getline(iss, accNum, ';');
            getline(iss, accType, ';');
            getline(iss, bal);
            if (userID == userName && accType == accountType) {
                userFound = true;
                tempFile << userID << ";" << Name << ";" << accNum << ";" << accType << ";" << fixed << setprecision(2) << stod(bal) + amount << endl;
                outFile << "(Name: " << Name << ", Account Number: " << accNum << ") Initial balance: $" << bal << ". Deposit amount: $" << amount << "." << " After deposit balance: $" << fixed << setprecision(2) << stod(bal) + amount << endl;
            }
            else {
                tempFile << userID << ";" << Name << ";" << accNum << ";" << accType << ";" << bal << endl;
            }
        }
        outFile.close();
        bankAccountsFile.close();
        tempFile.close();
        if (userFound) {
            if (remove("BankAccounts.txt") != 0) {
                cout << "Error: Unable to remove file." << endl;
                return;
            }
            if (rename("temp.txt", "BankAccounts.txt") != 0) {
                cout << "Error: Unable to rename file." << endl;
                return;
            }
        }
        else {
            cout << "Error: User or account type not found." << endl;
            remove("temp.txt");
        }
    }
}
        

void Transaction::withdraw(const string& userName, double amount, const string& accountType) {
    userFound = false;
    ifstream bankAccountsFile("BankAccounts.txt");
    ofstream tempFile("temp.txt");
    ofstream outFile("Transactions.txt", ios::app);
    if (!bankAccountsFile || !tempFile || !outFile) {
        cout << "Error: Unable to open file." << endl;
        return;
    }
    else {
        while (getline(bankAccountsFile, line)) {
            istringstream iss(line);
            getline(iss, userID, ';');
            getline(iss, Name, ';');
            getline(iss, accNum, ';');
            getline(iss, accType, ';');
            getline(iss, bal);
            if (userID == userName && accType == accountType) {
                if (amount > stod(bal)) {
                    cout << "Error: Withdraw amount is greater than the current account balance.\n" << endl;
                    outFile.close();
                    bankAccountsFile.close();
                    tempFile.close();
                    return;
                }
                else {
                    userFound = true;
                    tempFile << userID << ";" << Name << ";" << accNum << ";" << accType << ";" << fixed << setprecision(2) << stod(bal) - amount << endl;
                    outFile << "(Name: " << Name << ", Account Number: " << accNum << ") Initial balance: $" << bal << ". Withdraw amount: $" << amount << "." << " After withdraw balance: $" << fixed << setprecision(2) << stod(bal) - amount << endl;
                }
            }
            else {
                tempFile << userID << ";" << Name << ";" << accNum << ";" << accType << ";" << bal << endl;
            }
        }
        outFile.close();
        bankAccountsFile.close();
        tempFile.close();
        if (userFound) {
            if (remove("BankAccounts.txt") != 0) {
                cout << "Error: Unable to remove file." << endl;
                return;
            }
            if (rename("temp.txt", "BankAccounts.txt") != 0) {
                cout << "Error: Unable to rename file." << endl;
                return;
            }
        }
        else {
            cout << "Error: User or account type not found." << endl;
            remove("temp.txt");
        }
    }
}


void Transaction::displayHistory(const string& userName) {
    ifstream inFile("Transactions.txt");

    if (inFile.is_open()) {
        cout << "Transaction History for Account " << userName << ":" << endl;
        while (getline(inFile, line)) {
            if (line.find("(Name: " + userName) != string::npos) {
                cout << line << endl;
            }
        }
        inFile.close();
    }
    else {
        cout << "Error: Unable to open transaction file for reading." << endl;
    }
}